/**
 * @file      bsp_qaz_65.hpp
 * @brief     BSP for the QAZ 65% board
 *
 * @author    Anthony Needles
 * @date      2020/12/20
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Definitions specfic to the QAZ 65% board.
 */

#if !defined(BSP_BSP_HPP_)

#error Do not include board BSP header directly, please include bsp.hpp

#endif

#ifndef BSP_QAZ_65_BSP_QAZ_65_HPP_
#define BSP_QAZ_65_BSP_QAZ_65_HPP_

#include "core/gpio.hpp"

/**
 * @brief Board support package namespace
 *
 * This namespace holds definitions specific to a certain QAZ board.
 *
 * Is this the correct way to use the term "BSP"? Eh...
 */
namespace bsp {

// individual gpio pins
constexpr gpio::Id HB_LED  = { gpio::B, gpio::PIN_0  };
constexpr gpio::Id MCO     = { gpio::A, gpio::PIN_8  };
constexpr gpio::Id DBG_TX  = { gpio::A, gpio::PIN_9  };
constexpr gpio::Id RGB_EN  = { gpio::B, gpio::PIN_2  };
constexpr gpio::Id RGB_SDA = { gpio::B, gpio::PIN_11 };
constexpr gpio::Id RGB_SCL = { gpio::B, gpio::PIN_10 };

/// Key matrix column gpio pins
constexpr gpio::Id COLS[] = {
    { gpio::C, gpio::PIN_13 },  // COL00
    { gpio::C, gpio::PIN_14 },  // COL01
    { gpio::C, gpio::PIN_15 },  // COL02
    { gpio::B, gpio::PIN_12 },  // COL03
    { gpio::B, gpio::PIN_13 },  // COL04
    { gpio::B, gpio::PIN_14 },  // COL05
    { gpio::B, gpio::PIN_15 },  // COL06
    { gpio::A, gpio::PIN_10 },  // COL07
    { gpio::A, gpio::PIN_15 },  // COL08
    { gpio::B, gpio::PIN_3  },  // COL09
    { gpio::B, gpio::PIN_4  },  // COL10
    { gpio::B, gpio::PIN_5  },  // COL11
    { gpio::B, gpio::PIN_6  },  // COL12
    { gpio::B, gpio::PIN_7  },  // COL13
    { gpio::B, gpio::PIN_8  },  // COL14
};

/// Key matrix row gpio pins
constexpr gpio::Id ROWS[] = {
    { gpio::A, gpio::PIN_1  },  // ROW00
    { gpio::A, gpio::PIN_2  },  // ROW01
    { gpio::A, gpio::PIN_3  },  // ROW02
    { gpio::A, gpio::PIN_4  },  // ROW03
    { gpio::A, gpio::PIN_0  },  // ROW04
};

/// bsp-specific initializations
void init(void);

}  // namespace bsp

/// Base key symbol table
///     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define BASE_TABLE(K) \
    K(ESC)   K(1)     K(2)     K(3)     K(4)     K(5)     K(6)     K(7)     K(8)     K(9)     K(0)     K(DASH)  K(EQUAL) K(BKSPC) K(GRAVE)  /* NOLINT */  \
    K(TAB)   K(Q)     K(W)     K(E)     K(R)     K(T)     K(Y)     K(U)     K(I)     K(O)     K(P)     K(LBRKT) K(RBRKT) K(BSLSH) K(PGEUP)  /* NOLINT */  \
    K(CPLCK) K(A)     K(S)     K(D)     K(F)     K(G)     K(H)     K(J)     K(K)     K(L)     K(SEMI)  K(QUOTE) K(NONE)  K(ENTER) K(PGEDN)  /* NOLINT */  \
    K(LSHFT) K(Z)     K(X)     K(C)     K(V)     K(B)     K(N)     K(M)     K(COMMA) K(PRIOD) K(FSLSH) K(RSHFT) K(NONE)  K(UARRW) K(DELET)  /* NOLINT */  \
    K(LCTRL) K(LGUI)  K(LALT)  K(NONE)  K(NONE)  K(SPACE) K(NONE)  K(NONE)  K(RALT)  K(FN)    K(RCTRL) K(LARRW) K(NONE)  K(DARRW) K(RARRW)  /* NOLINT */

/// Fn key symbol table - for when the FN key is pressed
///     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define FN_TABLE(K) \
    K(NONE)  K(F1)    K(F2)    K(F3)    K(F4)    K(F5)    K(F6)    K(F7)    K(F8)    K(F9)    K(F10)   K(F11)   K(F12)   K(NONE)  K(PROF)   /* NOLINT */ \
    K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(BRTUP)  /* NOLINT */ \
    K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(BRTDN)  /* NOLINT */ \
    K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(VOLUP) K(COLOR)  /* NOLINT */ \
    K(LCTRL) K(LGUI)  K(LALT)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(RALT)  K(FN)    K(RCTRL) K(SPDDN) K(NONE)  K(VOLDN) K(SPDUP)  /* NOLINT */

/// Which keys get a callback function
#define CALLBACK_KEY_TABLE(K) \
    K(BRTUP) K(BRTDN) K(COLOR) K(PROF) K(SPDUP) K(SPDDN)

/// USART used for sending debug messages
#define DEBUG_UART    USART1

/// I2C used for talking to the LED controller
#define RGB_LED_I2C   I2C1

#endif  // BSP_QAZ_65_BSP_QAZ_65_HPP_
