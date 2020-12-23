/**
 * @file      bsp_qaz_testboard.h
 * @brief     BSP for the QAZ testboard
 *
 * @author    Anthony Needles
 * @date      2020/12/20
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Definitions specfic to the QAZ testboard.
 */

#ifndef BSP_BSP_QAZ_TESTBOARD_H_
#define BSP_BSP_QAZ_TESTBOARD_H_

// output GPIO ports. each column has:
//     port - the port (A, B, C, D, ...)
//     pin  - the pin number
#define COL_TABLE(COL) \
    COL(GPIOA, 15) \
    COL(GPIOB,  3) \
    COL(GPIOB,  6)

// input GPIO rows. each row has:
//     port - the port (A, B, C, D, ...)
//     pin  - the pin number
#define ROW_TABLE(ROW) \
    ROW(GPIOB,  4) \
    ROW(GPIOB,  5) \
    ROW(GPIOB,  7)

// base key symbol table
//     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define BASE_TABLE(K) \
    K(FN)    K(2)     K(3)     \
    K(4)     K(5)     K(6)     \
    K(7)     K(8)     K(9)

// fn key symbol table - for when the FN key is pressed
//     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define FN_TABLE(K) \
    K(FN)    K(2)     K(3)     \
    K(4)     K(COLOR) K(BRTUP) \
    K(7)     K(PROF)  K(BRTDN)

// which keys get a callback function
#define CALLBACK_KEY_TABLE(K) \
    K(BRTUP) K(BRTDN) K(COLOR) K(PROF)

// HB driving GPIO port
#define HB_LED_PORT GPIOB
#define HB_LED_PIN  13

// RGB LED enable pin
#define LED_EN_PORT GPIOB
#define LED_EN_PIN  2

// USART used for sending debug messages
#define DEBUG_UART USART1

// I2C used for talking to the LED controller
#define RGB_LED_I2C I2C1

#endif  // BSP_BSP_QAZ_TESTBOARD_H_
