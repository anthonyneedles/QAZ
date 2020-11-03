/**
 * @file    key_matrix.h
 * @author  Anthony Needles
 * @date    2020/10/04
 * @brief   Implements key matrix scanning
 *
 * Used to detect keypress on a key matrix. The columns open drain outputs, and the rows are inputs
 * with the pull ups. Under normal circumstances, the columns are high-Z, and the rows will read
 * VCC. When scanning, each column is driven to GND, and so each row with a pressed key will read
 * GND.
 *
 * Two keypress functionality exist in this module:
 *   1. Constantly pressed key buffering
 *
 *   The key in buffer is filled with every key currently pressed. This is what USB HID wants.
 *   Functionality to get this buffer is TBD.
 *
 *   2. Single callback key presses
 *
 *   For specified keys, a callback function will be called ONCE per key press, so the user needs
 *   to release the key and press it again for the callback to be called again. This is useful for
 *   user keys, such as changing the RGB LED color, brightness, etc.
 */

#ifndef __KEY_MATRIX_H_
#define __KEY_MATRIX_H_

#include <stdint.h>
#include "stm32f0xx.h"

#define KEY_MATRIX_TASK_PERIOD_MS (50U)

// output GPIO ports. each column has:
//     port - the port (A, B, C, D, ...)
//     pin  - the pin number
#define COL_TABLE(COL) \
    COL(A, 15) \
    COL(B,  3) \
    COL(B,  6)

// input GPIO rows. each row has:
//     port - the port (A, B, C, D, ...)
//     pin  - the pin number
#define ROW_TABLE(ROW) \
    ROW(B,  4) \
    ROW(B,  5) \
    ROW(B,  7)

// base key symbol table
//     symbol - the symbol for the key. make it simple.
#define BASE_TABLE(K) \
     K(1)     K(2)     K(3) \
     K(4)     K(5)     K(6) \
     K(7)     K(FN)    K(9)

// fn key symbol table - for when the FN key is pressed
//     symbol - the symbol for the key. make it simple.
#define FN_TABLE(K) \
     K(a)     K(b)     K(BRTUP) \
     K(c)     K(d)     K(BRTDN) \
     K(PROF)  K(FN)    K(COLOR)

// which keys get a callback function
#define CALLBACK_KEY_TABLE(K) \
    K(BRTUP) K(BRTDN) K(COLOR) K(PROF)

// weak callbacks for each of the callback keys. these are called ONCE PER BUTTON PRESS. the user
// must release then repress the key for a second call
#define K(symbol) __WEAK void KeyMatrixCallback_##symbol(void);
CALLBACK_KEY_TABLE(K)
#undef K

typedef uint16_t keys_t;

// get the keycode from a symbol
#define KEY(x) ((keys_t)(HID_USAGE_KEYBOARD_##x))

// keys that can be detected at once
#define KEY_BUF_SIZE (8)

// each physical key has 'base' key, and a 'fn' key. which is considered 'pressed' depends on if
// the FN key is pressed
typedef struct {
    keys_t base;
    keys_t fn;
} key_layer_t;

/**
 * KeyMatrixInit
 *
 * @brief Initializes columns/rows
 *
 * Takes the given row/columns gpio definitions and inits them as needed.
 * The inputs need a pullup or else they will float.
 */
void KeyMatrixInit(void);

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
void KeyMatrixTask(void);

#endif /* __KEY_MATRIX_H_ */
