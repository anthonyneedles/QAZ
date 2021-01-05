/**
 * @file      uart.hpp
 * @brief     UART driver
 *
 * @author    Anthony Needles
 * @date      2020/12/21
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This source file handles all UART communications. Configured for 115200 baud.
 *
 * Assumes SYSCLK = 48MHz
 */

#ifndef COMM_UART_HPP_
#define COMM_UART_HPP_

#include "comm/comm_base.hpp"
#include "stm32f0xx.h"  // NOLINT

/**
 * @brief I2C communication class
 *
 * Derived from the Base communication class, this class implements the I2C driver
 */
class UART : public CommBase {
 public:
    // ctor, initialize private member variables
    explicit UART(USART_TypeDef *regs) : _regs(regs) {}

    // implementing base methods
    comm::Status init(void);
    comm::Status write_blocking(const std::uint8_t *data, unsigned nbytes);
 private:
    // must be set via ctor initializer list
    USART_TypeDef *const _regs;

    comm::State _state = comm::RESET;
};

#endif  // COMM_UART_HPP_
