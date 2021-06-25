/**
 * @file      bsp_qaz_media.hpp
 * @brief     BSP for the QAZ Media board
 *
 * @author    Anthony Needles
 * @date      2021/06/24
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Definitions specfic to the QAZ Media board.
 */

#if !defined(BSP_BSP_HPP_)

#error Do not include board BSP header directly, please include bsp.hpp

#endif

#ifndef BSP_QAZ_MEDIA_BSP_QAZ_MEDIA_HPP_
#define BSP_QAZ_MEDIA_BSP_QAZ_MEDIA_HPP_

#include "core/gpio.hpp"

/**
 * @brief Board support package namespace (for QAZ Media board)
 *
 * This namespace holds definitions specific to a certain QAZ board.
 *
 * Is this the correct way to use the term "BSP"? Eh...
 */
namespace bsp {

// individual gpio pins
constexpr gpio::Id HB_LED  = { gpio::A, gpio::PIN_5  };
constexpr gpio::Id MCO     = { gpio::A, gpio::PIN_8  };
constexpr gpio::Id DBG_TX  = { gpio::A, gpio::PIN_9  };

/// bsp-specific initializations
void init(void);

}  // namespace bsp

/// USART used for sending debug messages
#define DEBUG_UART USART1

#endif  // BSP_QAZ_MEDIA_BSP_QAZ_MEDIA_HPP_
