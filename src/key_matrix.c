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

#include "debug.h"
#include "macros.h"
#include "stm32f0xx.h"

#define NUM_COLS (sizeof(col)/sizeof(col[0]))
#define NUM_ROWS (sizeof(row)/sizeof(row[0]))

// index into key symbol array for corresponding symbol
#define KEY_SYMBOL(col, row) (keys[row*NUM_COLS + col])

// SET/CLR does not mean driving the column 3.3V/GND, but rather (respectively)
// activating/deactivating it. Since the inputs are pulled HIGH, and the outputs
// are open drain, SET/CLR corresponds to (respectively) GND/HIGH-Z
#define SET_PIN(col) ((col.port)->ODR &= ~(1UL << col.pin))
#define CLR_PIN(col) ((col.port)->ODR |=  (1UL << col.pin))

// Row inputs are pulled HIGH, and active LOW, this will evaulate to '1' if the
// row is active (LOW) and '0' if the row is inactive (HIGH)
#define READ_PIN(row) (!((row.port)->IDR &= (1UL << row.pin)))
#define PIN_SET (1)
#define PIN_CLR (0)

typedef enum {
    IDLE,
    VERIFY_KEY,
    VERIFED_KEY,
} debounce_state_t;

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

// macro expand key symbol array. this holds every KEY_* enumeration value corresponding to every
// key, in order (for N columns and M rows):
//   col0_row0, col1_row0, ..., colN_row0, col0_row1, col1_row1, ... colN_rowM
static const keys_t keys[NUM_COLS*NUM_ROWS] = {
#define KEY(symbol) KEY_##symbol,
        KEY_TABLE(KEY)
#undef KEY
};

// buffer for current validated key
static keys_t key_in;

keys_t keyMatrixScan(void);

/**
 * KeyMatrixInit
 * 
 * @brief Initializes columns/rows
 *
 * Takes the given row/columns gpio definitions and inits them as needed.
 * The inputs need a pulldown or else they will float.
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

    key_in = NO_KEY;
}

/**
 * KeyMatrixTask
 *
 * @brief Verifies key presses
 *
 * Implements key debouncing state machine to verify key presses.
 *
 * The delay from a key press and the verification of said key has a maximum time of double the
 * task period.
 */
void KeyMatrixTask(void)
{
    static debounce_state_t state = IDLE;
    static keys_t last_key = NO_KEY;

    keys_t cur_key = keyMatrixScan();

    switch (state) {
    case IDLE:
        if (cur_key != NO_KEY) {
            state = VERIFY_KEY;
        }
        break;
    case VERIFY_KEY:
        if (cur_key == last_key) {
            key_in = cur_key;
            state = VERIFED_KEY;
        } else {
            state = IDLE;
        }
        break;
    case VERIFED_KEY:
        if (cur_key != last_key) {
            state = IDLE;
        }
        break;
    default:
        state = IDLE;
        break;
    }

    last_key = cur_key;
}

/**
 * KeyMatrixGetKey
 *
 * @brief Returns key in key buffer
 *
 * Also clears the key in the key buffer, so that keys will need to be re-pressed in order to be
 * be registered multiple times.
 *
 * @return validated key press
 */
keys_t KeyMatrixGetKey(void) {
    keys_t key = key_in;
    key_in = NO_KEY;
    return key;
}

/**
 * keyMatrixScan
 *
 * @brief Scans the key matrix to detect key presses
 *
 * Will set each column and read each row for each column. This allows detection of individual
 * keys. If a key is found, it's returned.
 *
 * The first key press seen is the one 'detected'. This means that
 *
 * Ghosting is not accounted for in software.
 *
 * @return detected key press key enum
 */
keys_t keyMatrixScan(void)
{
    keys_t key = NO_KEY;

    // ensure all columns are off
    for (int ncol = 0; ncol < (int)NUM_COLS; ++ncol) {
        CLR_PIN(col[ncol]);
    }

    // set columns, one by one
    for (int ncol = 0; ncol < (int)NUM_COLS; ++ncol) {
        SET_PIN(col[ncol]);

        // and read each row for each set column
        for (int nrow = 0; nrow < (int)NUM_ROWS; ++nrow) {
            int state = READ_PIN(row[nrow]);
            if (state == PIN_SET) {
                key = KEY_SYMBOL(ncol, nrow);
                DbgPrintf("(%d,%d)\r\n", ncol, nrow);
            }
        }

        CLR_PIN(col[ncol]);
    }

    return key;
}
