/**
 * @file      bsp_qaz_testboard.hpp
 * @brief     BSP for the QAZ testboard
 *
 * @author    Anthony Needles
 * @date      2020/12/20
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Definitions specfic to the QAZ testboard.
 */

#if !defined(BSP_BSP_HPP_)

#error Do not include board BSP header directly, please include bsp.hpp

#endif

#ifndef BSP_QAZ_TESTBOARD_BSP_QAZ_TESTBOARD_HPP_
#define BSP_QAZ_TESTBOARD_BSP_QAZ_TESTBOARD_HPP_

#include "core/gpio.hpp"

/**
 * @brief Board support package namespace (for QAZ testboard)
 *
 * This namespace holds definitions specific to a certain QAZ board.
 *
 * Is this the correct way to use the term "BSP"? Eh...
 */
namespace bsp {

// individual gpio pins
constexpr gpio::Id HB_LED  = { gpio::B, gpio::PIN_13 };
constexpr gpio::Id MCO     = { gpio::A, gpio::PIN_8  };
constexpr gpio::Id DBG_TX  = { gpio::A, gpio::PIN_9  };
constexpr gpio::Id DBG_RX  = { gpio::A, gpio::PIN_10 };
constexpr gpio::Id RGB_EN  = { gpio::B, gpio::PIN_2  };
constexpr gpio::Id RGB_SDA = { gpio::B, gpio::PIN_10 };
constexpr gpio::Id RGB_SCL = { gpio::B, gpio::PIN_11 };

/// Key matrix column gpio pins
constexpr gpio::Id COLS[] = {
    { gpio::A, gpio::PIN_15 },
    { gpio::B, gpio::PIN_3  },
    { gpio::B, gpio::PIN_6  },
};

/// Key matrix row gpio pins
constexpr gpio::Id ROWS[] = {
    { gpio::B, gpio::PIN_4  },
    { gpio::B, gpio::PIN_5  },
    { gpio::B, gpio::PIN_7  },
};

/// bsp-specific initializations
void init(void);

}  // namespace bsp

/// Base key symbol table
///     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define BASE_TABLE(K) \
    K(FN)    K(2)     K(3)     \
    K(4)     K(5)     K(6)     \
    K(7)     K(8)     K(9)

/// Fn key symbol table - for when the FN key is pressed
///     symbol - the symbol for the key. must match with HID_USAGE_KEYBOARD_* define
#define FN_TABLE(K) \
    K(FN)    K(2)     K(3)     \
    K(4)     K(COLOR) K(BRTUP) \
    K(7)     K(PROF)  K(BRTDN)

/// Which keys get a callback function
#define CALLBACK_KEY_TABLE(K) \
    K(BRTUP) K(BRTDN) K(COLOR) K(PROF) K(SPDUP) K(SPDDN)

/// USART used for sending debug messages
#define DEBUG_UART USART1

/// I2C used for talking to the LED controller
#define RGB_LED_I2C I2C1

#endif  // BSP_QAZ_TESTBOARD_BSP_QAZ_TESTBOARD_HPP_
