/**
 * @file      bsp_qaz_65.h
 * @brief     BSP for the QAZ 65% board
 *
 * @author    Anthony Needles
 * @date      2020/12/20
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Definitions specfic to the QAZ 65% board.
 */

#ifndef BSP_BSP_QAZ_65_H_
#define BSP_BSP_QAZ_65_H_

// output GPIO ports. each column has:
//     port - the port (A, B, C, D, ...)
//     pin  - the pin number
#define COL_TABLE(COL) \
    COL(A,  5) \
    COL(A,  6) \
    COL(A,  7) \
    COL(B, 13) \
    COL(B, 14) \
    COL(B, 15) \
    COL(A, 10) \
    COL(B,  4) \
    COL(B,  7) \
    COL(B,  8) \
    COL(B,  9) \
    COL(C, 13) \
    COL(B,  6) \
    COL(C, 14) \
    COL(C, 15)

// input GPIO rows. each row has:
//     port - the port (A, B, C, D, ...)
//     pin  - the pin number
#define ROW_TABLE(ROW) \
    ROW(B,  0) \
    ROW(B,  1) \
    ROW(A, 15) \
    ROW(B, 12) \
    ROW(B,  5)

// base key symbol table
//     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define BASE_TABLE(K) \
     K(ESC)   K(1)     K(2)     K(3)     K(4)     K(5)     K(6)     K(7)     K(8)     K(9)     K(0)     K(DASH)  K(EQUAL) K(BKSPC) K(GRAVE)  /* NOLINT */  \
     K(TAB)   K(Q)     K(W)     K(E)     K(R)     K(T)     K(Y)     K(U)     K(I)     K(O)     K(P)     K(LBRKT) K(RBRKT) K(BSLSH) K(PGEUP)  /* NOLINT */  \
     K(CPLCK) K(A)     K(S)     K(D)     K(F)     K(G)     K(H)     K(J)     K(K)     K(L)     K(SEMI)  K(QUOTE) K(NONE)  K(ENTER) K(PGEDN)  /* NOLINT */  \
     K(LSHFT) K(Z)     K(X)     K(C)     K(V)     K(B)     K(N)     K(M)     K(COMMA) K(PRIOD) K(FSLSH) K(RSHFT) K(NONE)  K(UARRW) K(DELET)  /* NOLINT */  \
     K(LCTRL) K(LGUI)  K(LALT)  K(NONE)  K(NONE)  K(SPACE) K(NONE)  K(NONE)  K(RALT)  K(FN)    K(RCTRL) K(LARRW) K(NONE)  K(DARRW) K(RARRW)  /* NOLINT */ 

// fn key symbol table - for when the FN key is pressed
//     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define FN_TABLE(K) \
     K(NONE)  K(F1)    K(F2)    K(F3)    K(F4)    K(F5)    K(F6)    K(F7)    K(F8)    K(F9)    K(F10)   K(F11)   K(F12)   K(NONE)  K(PROF)   /* NOLINT */ \
     K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(BRTUP)  /* NOLINT */ \
     K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(BRTDN)  /* NOLINT */ \
     K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(VOLUP) K(COLOR)  /* NOLINT */ \
     K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(FN)    K(NONE)  K(NONE)  K(NONE)  K(VOLDN) K(NONE)   /* NOLINT */

// which keys get a callback function
#define CALLBACK_KEY_TABLE(K) \
    K(BRTUP) K(BRTDN) K(COLOR) K(PROF)

// HB driving GPIO port
#define HB_LED_NUM  (3)
#define HB_LED_PORT (GPIOB)

// RGB LED enable pin
#define LED_EN_PIN GPIO(B, 2)

// USART used for sending debug messages
#define DEBUG_UART USART1

// I2C used for talking to the LED controller
#define RGB_LED_I2C I2C1

#endif  // BSP_BSP_QAZ_65_H_
