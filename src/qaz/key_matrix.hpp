/**
 * @file      key_matrix.hpp
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

#ifndef QAZ_KEY_MATRIX_HPP_
#define QAZ_KEY_MATRIX_HPP_

#include <stdint.h>

#include "bsp/bsp.hpp"
#include "stm32f0xx.h"  // NOLINT

/// Weak callbacks for each of the callback keys. these are called ONCE PER BUTTON PRESS. The user
/// must release then repress the key for a second call
#define K(symbol) __WEAK void KeyMatrixCallback_##symbol(void);
CALLBACK_KEY_TABLE(K)
#undef K

// Keycodes in HID standard are 16-bit values
typedef int16_t keys_t;

/// Get the keycode from a symbol
#define KEY(x) ((keys_t)(HID_USAGE_KEYBOARD_##x))

/// Keys that can be detected at once
#define KEY_BUF_SIZE (6)

// Each physical key has 'base' key, and a 'fn' key. which is considered 'pressed' depends on if
// the FN key is pressed
typedef struct {
    keys_t base;
    keys_t fn;
} key_layer_t;

/// Init all rows as pullup inputs and columns as open-drain outputs
void KeyMatrixInit(void);

/// Run scan routine, fill internal key buffer, and call any key callbacks
void KeyMatrixTask(void);

/// Fills input buffer (OF SIZE `KEY_BUF_SIZE`) with current key buffer
void KeyMatrixGetKeyBuffer(keys_t *key_buf);

#endif  // QAZ_KEY_MATRIX_HPP_
