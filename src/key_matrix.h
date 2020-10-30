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
 */

#ifndef __KEY_MATRIX_H_
#define __KEY_MATRIX_H_

// max time between key press and validation is TWICE this period
#define KEY_MATRIX_TASK_PERIOD_MS (25u)

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

// key symbol table. callback function will use this symbol. each key has:
//     symbol - the symbol for the key. make it simple.
#define KEY_TABLE(KEY) \
     KEY(1) KEY(2) KEY(3) \
     KEY(4) KEY(5) KEY(6) \
     KEY(7) KEY(8) KEY(9)

// macro expand enumeration value for each key with name KEY_*
typedef enum {
    NO_KEY = 0,
#define KEY(symbol) \
    KEY_##symbol,
    KEY_TABLE(KEY)
#undef KEY
} keys_t;

/**
 * KeyMatrixInit
 *
 * @brief Initializes columns/rows
 *
 * Takes the given row/columns gpio definitions and inits them as needed.
 * The inputs need a pulldown or else they will float.
 */
void KeyMatrixInit(void);

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
void KeyMatrixTask(void);

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
keys_t KeyMatrixGetKey(void);

#endif /* __KEY_MATRIX_H_ */
