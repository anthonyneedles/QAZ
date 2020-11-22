/**
 * @file    key_matrix.c
 * @author  Anthony Needles
 * @date    2020/10/04
 * @brief   Implements key matrix scanning
 *
 * Used to detect keypress on a key matrix. The columns are set as outputs and rows set as inputs.
 * Each column is set high and each row is read.
 *
 * When a key press is detected a function (defined as __weak in the source file) is called.
 * This function is defined as:
 *     void KeyPressCallback_X(void)
 * where X is the symbol given in KEY_TABLE.
 */

#include "key_matrix.h"

#include <stdbool.h>

#include "debug.h"
#include "macros.h"
#include "stm32f0xx.h"
#include "usb_hid_usages.h"

#define NUM_COLS (sizeof(col)/sizeof(col[0]))
#define NUM_ROWS (sizeof(row)/sizeof(row[0]))

// index into key symbol array for corresponding symbol
#define BASE_KEY(col, row) (base_keys[row*NUM_COLS + col])
#define FN_KEY(col, row)   (fn_keys[row*NUM_COLS + col])

// SET/CLR does not mean driving the column 3.3V/GND, but rather (respectively)
// activating/deactivating it. Since the inputs are pulled HIGH, and the outputs
// are open drain, SET/CLR corresponds to (respectively) GND/HIGH-Z
#define ACTIVATE_COL(col)   ((col.port)->ODR &= ~(1UL << col.pin))
#define DEACTIVATE_COL(col) ((col.port)->ODR |=  (1UL << col.pin))

// Row inputs are pulled HIGH, and active LOW, this will evaulate to '1' if the
// row is active (LOW) and '0' if the row is inactive (HIGH)
#define READ_ROW(row) (!((row.port)->IDR &= (1UL << row.pin)))
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

// attributes for each gpio used
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} gpio_t;

// macro expand column gpio attribute array
static const gpio_t col[] = {
#define COL(port, pin) {GPIO##port, pin},
    COL_TABLE(COL)
#undef COL
};

// macro expand row gpio attribute array
static const gpio_t row[] = {
#define ROW(port, pin) {GPIO##port, pin},
    ROW_TABLE(ROW)
#undef ROW
};

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
static callback_states_t callback_states = { 0 };

void keyMatrixScan(key_buf_t *keybuf);

/**
 * KeyMatrixInit
 *
 * @brief Initializes columns/rows
 *
 * Takes the given row/columns gpio definitions and inits them as needed.
 * The inputs need a pullup or else they will float.
 */
void KeyMatrixInit(void)
{
    // macro expand the col table into open drain output gpio init
#define COL(port, pin)                                                                    \
    RCC->AHBENR |= RCC_AHBENR_GPIO##port##EN;                                             \
    GPIO##port->MODER =                                                                   \
        ((GPIO##port->MODER & ~GPIO_MODER_MODER##pin##_Msk) | GPIO_MODER_MODER##pin##_0); \
    GPIO##port->OTYPER |= GPIO_OTYPER_OT_##pin;
    COL_TABLE(COL)
#undef COL

    // macro expand the row table into pullup input gpio init
#define ROW(port, pin)                                                                    \
    RCC->AHBENR |= RCC_AHBENR_GPIO##port##EN;                                             \
    GPIO##port->PUPDR =                                                                   \
        ((GPIO##port->PUPDR & ~GPIO_PUPDR_PUPDR##pin##_Msk) | GPIO_PUPDR_PUPDR##pin##_0); \
    GPIO##port->MODER &= ~GPIO_MODER_MODER##pin##_Msk;
    ROW_TABLE(ROW)
#undef ROW

    DbgPrintf("Initialized: Key Matrix\r\n");
}

/**
 * KeyMatrixTask
 *
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
        keys_in[i]          = KEY(NOEVT);
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

/*
 * keyMatrixScan
 *
 * @brief Scans the key matrix to detect key presses
 *
 * Will set each column and read each row for each column. This allows detection of individual
 * keys. If a key is found, its layer is pushed into the key buffer.
 *
 * @param[in,out] keybuf buffer/info to fill
 */
void keyMatrixScan(key_buf_t *keybuf)
{
    // ensure all columns are off
    for (int ncol = 0; ncol < (int)NUM_COLS; ++ncol) {
        DEACTIVATE_COL(col[ncol]);
    }

    // set columns, one by one
    for (int ncol = 0; ncol < (int)NUM_COLS; ++ncol) {
        ACTIVATE_COL(col[ncol]);

        // and read each row for each set column
        for (int nrow = 0; nrow < (int)NUM_ROWS; ++nrow) {
            int state = READ_ROW(row[nrow]);
            if (state == ROW_SET) {
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

        DEACTIVATE_COL(col[ncol]);

        // ~10us delay. allows row to pull back up to VCC
        LOOP_DELAY(40);
    }
}
