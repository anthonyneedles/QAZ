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

#include "core/gpio.hpp"
#include "core/time_slice.hpp"
#include "qaz/lighting.hpp"
#include "usb/usb_hid_usages.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"

namespace {

/// Task fuction will execute every 20ms
constexpr unsigned KEY_MATRIX_TASK_PERIOD_MS = 20;

/// Number of physical columns in matrix
constexpr unsigned NUM_COLS = N_ELEMENTS(bsp::COLS);

/// Number of physical rows in martrix
constexpr unsigned NUM_ROWS = N_ELEMENTS(bsp::ROWS);

/// Number of idle loops until lighting enters sleep mode
constexpr unsigned IDLE_LOOPS_SLEEP = lighting::IDLE_MS_SLEEP/KEY_MATRIX_TASK_PERIOD_MS;

enum CallbackState{
    KEYUP = 0,
    PRESSED,
    UP_CHECK,
};

/// Each physical key has 'base' key, and a 'fn' key. which is considered 'pressed' depends on if
/// the FN key is pressed
struct KeyLayer {
    keymatrix::Key base;
    keymatrix::Key fn;
};

/// The key buffer filled when when scanning
struct KeyBuf {
    KeyLayer buf[keymatrix::KEY_BUF_SIZE];
    bool is_fn;
    unsigned idx;
};

/// States for each of the callback keys
struct CallbackStates {
#define K(symbol) CallbackState symbol;
    CALLBACK_KEY_TABLE(K)
#undef K
};

/// Macro expand base key symbol array. this holds every KEY_* enumeration value corresponding to
/// every key, in order (for N columns and M rows):
///   col0_row0, col1_row0, ..., colN_row0, col0_row1, col1_row1, ... colN_rowM
constexpr keymatrix::Key base_keys[NUM_COLS*NUM_ROWS] = {
#define K(symbol) HID_USAGE_KEYBOARD_##symbol,
        BASE_TABLE(K)
#undef K
};

/// Macro expand fn key symbol array. this holds every KEY_* enumeration value corresponding to
/// every key, in order (for N columns and M rows):
///   col0_row0, col1_row0, ..., colN_row0, col0_row1, col1_row1, ... colN_rowM
constexpr keymatrix::Key fn_keys[NUM_COLS*NUM_ROWS] = {
#define K(symbol) HID_USAGE_KEYBOARD_##symbol,
        FN_TABLE(K)
#undef K
};

/// Index into key symbol array for corresponding base layer symbol
constexpr keymatrix::Key GET_BASE_KEY(unsigned ncol, unsigned nrow)
{
    return base_keys[nrow*NUM_COLS + ncol];
}

/// Index into key symbol array for corresponding fn layer symbol
constexpr keymatrix::Key GET_FN_KEY(unsigned ncol, unsigned nrow)
{
    return fn_keys[nrow*NUM_COLS + ncol];
}

/// Buffer for current validated key, after checking for FN
keymatrix::Key keys_in[keymatrix::KEY_BUF_SIZE];

/// callback key states for all callback keys
CallbackStates callback_states = { };

/// Counting consecutive task loops without a key press
unsigned idle_loops = 0;

}  // namespace

static void scan_matrix(KeyBuf *keybuf);

/// Default implementation of the callbacks does nothing
#define K(symbol) __WEAK void callback_##symbol(void) {}
CALLBACK_KEY_TABLE(K)
#undef K

/**
 * @brief Initializes columns/rows
 *
 * Takes the given row/columns gpio definitions and inits them as needed.
 * The inputs need a pullup or else they will float.
 */
void keymatrix::init(void)
{
    // init each col gpio as open drain output
    for (unsigned i = 0; i < NUM_COLS; ++i) {
        gpio::enable_port_clock(bsp::COLS[i]);
        gpio::set_mode(bsp::COLS[i], gpio::OUTPUT);
        gpio::set_output_type(bsp::COLS[i], gpio::OPEN_DRAIN);
    }

    // init each row gpio as pullup input
    for (unsigned i = 0; i < NUM_ROWS; ++i) {
        gpio::enable_port_clock(bsp::ROWS[i]);
        gpio::set_mode(bsp::ROWS[i], gpio::INPUT);
        gpio::set_pull(bsp::ROWS[i], gpio::PULL_UP);
    }

    auto status = timeslice::register_task(KEY_MATRIX_TASK_PERIOD_MS, keymatrix::task);
    DBG_ASSERT(status == timeslice::SUCCESS);

    debug::puts("Initialized: Key Matrix\r\n");
}

/**
 * @brief Calls key scan routine, fills key code buffer, calls callbacks
 *
 * This task will scan the physical keys each task period. The output key_in buffer will hold the
 * actual keycodes for this set, either the base keys of fn keys (if FN key also pressed). If any
 * of the callback keys are newly pressed, the callbacks get called, otherwise their states get
 * updated accordingly.
 */
void keymatrix::task(void)
{
    KeyBuf keybuf;
    keymatrix::Key key;

    // clear our key buffer and key_in buffer
    for (unsigned i = 0; i < KEY_BUF_SIZE; ++i) {
        keys_in[i]         = KEY(NOEVT);
        keybuf.buf[i].base = KEY(NOEVT);
        keybuf.buf[i].fn   = KEY(NOEVT);
    }
    keybuf.idx   = 0;
    keybuf.is_fn = false;

    // fill buffer with pressed keys
    scan_matrix(&keybuf);

    // if there hasn't been any keypresses, we consider the keyboard idle
    if (keybuf.idx == 0) {
        // saturate counter
        if (idle_loops < IDLE_LOOPS_SLEEP) {
            idle_loops++;
        }
    } else {
        idle_loops = 0;
    }

    for (unsigned i = 0; i < keybuf.idx; ++i) {
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
                keymatrix::callback_##symbol();      \
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
 * @param[in,out] keybuf  buffer/info to fill into (assumed size = KEY_BUF_SIZE)
 */
void keymatrix::copy_key_buffer(keymatrix::Key *keybuf)
{
    DBG_ASSERT(keybuf);

    for (unsigned i = 0; i < KEY_BUF_SIZE; ++i) {
        keybuf[i] = keys_in[i];
    }
}

/**
 * @brief Returns whether the keyboard is idle
 *
 * If no key presses have occurred in `IDLE_MS_SLEEP`, the keyboard is considered idle.
 *
 * @return if keyboard is idle
 */
bool keymatrix::is_idle(void)
{
    return (idle_loops >= IDLE_LOOPS_SLEEP);
}

/**
 * @brief Scans the key matrix to detect key presses
 *
 * Will set each column and read each row for each column. This allows detection of individual
 * keys. If a key is found, its layer is pushed into the key buffer.
 *
 * @param[in,out] keybuf  buffer/info to fill
 */
void scan_matrix(KeyBuf *keybuf)
{
    DBG_ASSERT(keybuf);

    // ensure all columns are inactive
    for (unsigned ncol = 0; ncol < NUM_COLS; ++ncol) {
        // when set, the columns are open drain (i.e. high-z)
        gpio::set_output(bsp::COLS[ncol]);
    }

    // set columns, one by one
    for (unsigned ncol = 0; ncol < NUM_COLS; ++ncol) {
        // when cleared, the columns are GND
        gpio::clr_output(bsp::COLS[ncol]);

        // and read each row for each set column
        for (unsigned nrow = 0; nrow < NUM_ROWS; ++nrow) {
            // input is active low, since the active column is GND, and a button connects the input
            // to the column. if the button is not pressed, the input is pulled high via pullup
            gpio::PinState state = gpio::read_input(bsp::ROWS[nrow]);
            if (state == gpio::CLR) {
                keybuf->buf[keybuf->idx].base = GET_BASE_KEY(ncol, nrow);
                if (keybuf->buf[keybuf->idx].base == KEY(FN)) {
                    keybuf->is_fn = true;
                } else {
                    keybuf->buf[keybuf->idx].fn = GET_FN_KEY(ncol, nrow);
                    keybuf->idx++;
                    if (keybuf->idx >= keymatrix::KEY_BUF_SIZE) {
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
