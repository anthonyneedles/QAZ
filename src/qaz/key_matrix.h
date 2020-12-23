/**
 * @file      key_matrix.h
 * @brief     Implements key matrix scanning
 * 
 * @author    Anthony Needles
 * @date      2020/10/04
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
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

#ifndef __QAZ_KEY_MATRIX_H_
#define __QAZ_KEY_MATRIX_H_

#include <stdint.h>

#include "bsp/bsp.h"
#include "stm32f0xx.h"

#define KEY_MATRIX_TASK_PERIOD_MS (20u)

// weak callbacks for each of the callback keys. these are called ONCE PER BUTTON PRESS. the user
// must release then repress the key for a second call
#define K(symbol) __WEAK void KeyMatrixCallback_##symbol(void);
CALLBACK_KEY_TABLE(K)
#undef K

typedef uint16_t keys_t;

// get the keycode from a symbol
#define KEY(x) ((keys_t)(HID_USAGE_KEYBOARD_##x))

// keys that can be detected at once
#define KEY_BUF_SIZE (6)

// each physical key has 'base' key, and a 'fn' key. which is considered 'pressed' depends on if
// the FN key is pressed
typedef struct {
    keys_t base;
    keys_t fn;
} key_layer_t;

/**
 * @brief Initializes columns/rows
 *
 * Takes the given row/columns gpio definitions and inits them as needed.
 * The inputs need a pullup or else they will float.
 */
void KeyMatrixInit(void);

/**
 * @brief Calls key scan routine, fills key code buffer, calls callbacks
 *
 * This task will scan the physical keys each task period. The output key_in buffer will hold the
 * actual keycodes for this set, either the base keys of fn keys (if FN key also pressed). If any
 * of the callback keys are newly pressed, the callbacks get called, otherwise their states get
 * updated accordingly.
 */
void KeyMatrixTask(void);

/**
 * @brief Fills input buffer with current key buffer
 *
 * @param[in,out] keybuf buffer/info to fill into (assumed size = KEY_BUF_SIZE)
 */
void KeyMatrixGetKeyBuffer(keys_t *key_buf);

#endif /* __QAZ_KEY_MATRIX_H_ */
