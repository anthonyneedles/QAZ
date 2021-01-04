/**
 * @file      key_matrix.cpp
 * @brief     Implements key matrix scanning
 *
 * @author    Anthony Needles
 * @date      2020/10/04
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Used to detect keypress on a key matrix. The columns are set as outputs and rows set as inputs.
 * Each column is set high and each row is read.
 *
 * When a key press is detected a function (defined as __weak in the source file) is called.
 * This function is defined as:
 *     void KeyPressCallback_X(void)
 * where X is the symbol given in KEY_TABLE.
 */

#include "qaz/key_matrix.hpp"

#include <stdbool.h>

#include "usb/usb_hid_usages.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"

constexpr int NUM_COLS = N_ELEMENTS(bsp::COLS);
constexpr int NUM_ROWS = N_ELEMENTS(bsp::ROWS);

// index into key symbol array for corresponding symbol
#define BASE_KEY(col, row) (base_keys[row*NUM_COLS + col])
#define FN_KEY(col, row)   (fn_keys[row*NUM_COLS + col])

// SET/CLR does not mean driving the column 3.3V/GND, but rather (respectively)
// activating/deactivating it. Since the inputs are pulled HIGH, and the outputs
// are open drain, SET/CLR corresponds to (respectively) GND/HIGH-Z
#define ACTIVATE_COL(col)   GPIO_OUTPUT_CLR(col.port, col.pin)
#define DEACTIVATE_COL(col) GPIO_OUTPUT_SET(col.port, col.pin)

// Row inputs are pulled HIGH, and active LOW, this will evaulate to '1' if the
// row is active (LOW) and '0' if the row is inactive (HIGH)
#define READ_ROW(row) (!GPIO_READ_INPUT(row.port, row.pin))
#define ROW_SET (1)
#define ROW_CLR (0)

// state of callback keys, so we only call the callback function once per press
typedef enum {
    KEYUP = 0,
    PRESSED,
    UP_CHECK,
} callback_state_t;

// states for each of the callback keys
typedef struct {
#define K(symbol) callback_state_t symbol;
    CALLBACK_KEY_TABLE(K)
#undef K
} callback_states_t;

// the buffer when reading the keys when scanning
typedef struct {
    key_layer_t buf[KEY_BUF_SIZE];
    bool is_fn;
    int idx;
} key_buf_t;

// macro expand base key symbol array. this holds every KEY_* enumeration value corresponding to
// every key, in order (for N columns and M rows):
//   col0_row0, col1_row0, ..., colN_row0, col0_row1, col1_row1, ... colN_rowM
static const keys_t base_keys[NUM_COLS*NUM_ROWS] = {
#define K(symbol) HID_USAGE_KEYBOARD_##symbol,
        BASE_TABLE(K)
#undef K
};

static const keys_t fn_keys[NUM_COLS*NUM_ROWS] = {
#define K(symbol) HID_USAGE_KEYBOARD_##symbol,
        FN_TABLE(K)
#undef K
};

// buffer for current validated key, after checking for FN
static keys_t keys_in[KEY_BUF_SIZE];

// all callback key states
static callback_states_t callback_states = { };

void keyMatrixScan(key_buf_t *keybuf);

/**
 * @brief Initializes columns/rows
 *
 * Takes the given row/columns gpio definitions and inits them as needed.
 * The inputs need a pullup or else they will float.
 */
void KeyMatrixInit(void)
{
    // init each col gpio as open drain output
    for (int i = 0; i < NUM_COLS; ++i) {
        gpio::enable_port_clock(bsp::COLS[i]);
        gpio::set_mode(bsp::COLS[i], gpio::OUTPUT);
        gpio::set_output_type(bsp::COLS[i], gpio::OPEN_DRAIN);
    }

    // init each row gpio as pullup input
    for (int i = 0; i < NUM_ROWS; ++i) {
        gpio::enable_port_clock(bsp::ROWS[i]);
        gpio::set_mode(bsp::ROWS[i], gpio::INPUT);
        gpio::set_pull(bsp::ROWS[i], gpio::PULL_UP);
    }

    DbgPrintf("Initialized: Key Matrix\r\n");
}

/**
 * @brief Calls key scan routine, fills key code buffer, calls callbacks
 *
 * This task will scan the physical keys each task period. The output key_in buffer will hold the
 * actual keycodes for this set, either the base keys of fn keys (if FN key also pressed). If any
 * of the callback keys are newly pressed, the callbacks get called, otherwise their states get
 * updated accordingly.
 */
void KeyMatrixTask(void)
{
    key_buf_t keybuf;
    keys_t key;

    // clear our key buffer and key_in buffer
    for (int i = 0; i < KEY_BUF_SIZE; ++i) {
        keys_in[i]         = KEY(NOEVT);
        keybuf.buf[i].base = KEY(NOEVT);
        keybuf.buf[i].fn   = KEY(NOEVT);
    }
    keybuf.idx   = 0;
    keybuf.is_fn = false;

    // fill buffer with pressed keys
    keyMatrixScan(&keybuf);

    for (int i = 0; i < keybuf.idx; ++i) {
        // find the keycode for the given key layer in buffer
        if (keybuf.is_fn) {
            key = keybuf.buf[i].fn;
        } else {
            key = keybuf.buf[i].base;
        }

        // call any callback functions only if key just pressed. update state as PRESSED
        switch (key) {
    #define K(symbol)                              \
        case KEY(symbol):                          \
            if (callback_states.symbol == KEYUP) { \
                KeyMatrixCallback_##symbol();      \
            }                                      \
            callback_states.symbol = PRESSED;      \
            break;
        CALLBACK_KEY_TABLE(K)
    #undef K
        default:
            break;
        }

        // non-user keys get put into the key_in buffer
        if ((int16_t)key >= 0) {
            keys_in[i] = key;
        }
    }

    // if the key is pressed, the next time through we check if its pressed again. if the state
    // is still UP_CHECK, then we know the key has been released
    #define K(symbol)                                    \
        if (callback_states.symbol == PRESSED) {         \
            callback_states.symbol = UP_CHECK;           \
        } else if (callback_states.symbol == UP_CHECK) { \
            callback_states.symbol = KEYUP;              \
        }
        CALLBACK_KEY_TABLE(K)
    #undef K
}

/**
 * @brief Fills input buffer with current key buffer
 *
 * @param[in,out] keybuf buffer/info to fill into (assumed size = KEY_BUF_SIZE)
 */
void KeyMatrixGetKeyBuffer(keys_t *keybuf)
{
    DBG_ASSERT(keybuf);

    for (int i = 0; i < KEY_BUF_SIZE; ++i) {
        keybuf[i] = keys_in[i];
    }
}

/**
 * @brief Scans the key matrix to detect key presses
 *
 * Will set each column and read each row for each column. This allows detection of individual
 * keys. If a key is found, its layer is pushed into the key buffer.
 *
 * @param[in,out] keybuf buffer/info to fill
 */
void keyMatrixScan(key_buf_t *keybuf)
{
    DBG_ASSERT(keybuf);

    // ensure all columns are off
    for (int ncol = 0; ncol < NUM_COLS; ++ncol) {
        gpio::set_output(bsp::COLS[ncol]);
    }

    // set columns, one by one
    for (int ncol = 0; ncol < NUM_COLS; ++ncol) {
        gpio::clr_output(bsp::COLS[ncol]);

        // and read each row for each set column
        for (int nrow = 0; nrow < NUM_ROWS; ++nrow) {
            gpio::PinState state = gpio::read_input(bsp::ROWS[nrow]);
            if (state == gpio::CLR) {
                // found pressed key...
                keybuf->buf[keybuf->idx].base = BASE_KEY(ncol, nrow);
                if (keybuf->buf[keybuf->idx].base == KEY(FN)) {
                    keybuf->is_fn = true;
                } else {
                    keybuf->buf[keybuf->idx].fn = FN_KEY(ncol, nrow);
                    keybuf->idx++;
                    if (keybuf->idx >= KEY_BUF_SIZE) {
                        break;
                    }
                }
            }
        }

        gpio::set_output(bsp::COLS[ncol]);

        // ~10us delay. allows row to pull back up to VCC
        LOOP_DELAY(40);
    }
}
