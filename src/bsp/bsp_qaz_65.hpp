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

#ifndef BSP_BSP_QAZ_65_HPP_
#define BSP_BSP_QAZ_65_HPP_

#include "core/gpio.hpp"

/**
 * @brief Board support package namespace (for QAZ 65% board)
 *
 * This namespace holds definitions specific to a certain QAZ board.
 *
 * Is this the correct way to use the term "BSP"? Eh...
 */
namespace bsp {

// individual gpio pins
constexpr gpio::Id HB_LED  = { gpio::B, gpio::PIN_3  };
constexpr gpio::Id MCO     = { gpio::A, gpio::PIN_8  };
constexpr gpio::Id DBG_TX  = { gpio::A, gpio::PIN_9  };
constexpr gpio::Id RGB_EN  = { gpio::B, gpio::PIN_2  };
constexpr gpio::Id RGB_SDA = { gpio::B, gpio::PIN_10 };
constexpr gpio::Id RGB_SCL = { gpio::B, gpio::PIN_11 };

/// Key matrix column gpio pins
constexpr gpio::Id COLS[] = {
    { gpio::A, gpio::PIN_5  },
    { gpio::A, gpio::PIN_6  },
    { gpio::A, gpio::PIN_7  },
    { gpio::B, gpio::PIN_13 },
    { gpio::B, gpio::PIN_14 },
    { gpio::B, gpio::PIN_15 },
    { gpio::A, gpio::PIN_10 },
    { gpio::B, gpio::PIN_4  },
    { gpio::B, gpio::PIN_7  },
    { gpio::B, gpio::PIN_8  },
    { gpio::B, gpio::PIN_9  },
    { gpio::C, gpio::PIN_13 },
    { gpio::B, gpio::PIN_6  },
    { gpio::C, gpio::PIN_14 },
    { gpio::C, gpio::PIN_15 },
};

/// Key matrix row gpio pins
constexpr gpio::Id ROWS[] = {
    { gpio::B, gpio::PIN_0  },
    { gpio::B, gpio::PIN_1  },
    { gpio::A, gpio::PIN_15 },
    { gpio::B, gpio::PIN_12 },
    { gpio::B, gpio::PIN_5  },
};

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
    K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(NONE)  K(FN)    K(NONE)  K(NONE)  K(NONE)  K(VOLDN) K(NONE)   /* NOLINT */

/// Which keys get a callback function
#define CALLBACK_KEY_TABLE(K) \
    K(BRTUP) K(BRTDN) K(COLOR) K(PROF)

/// USART used for sending debug messages
#define DEBUG_UART    USART1

/// I2C used for talking to the LED controller
#define RGB_LED_I2C      I2C1

#endif  // BSP_BSP_QAZ_65_HPP_
