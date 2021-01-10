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
    /// CTOR, initialize private member variables
    explicit UART(USART_TypeDef *regs) : _regs(regs) {}

    /// UART init, enables peripheral clocking, 8-N-1 setup, and timing config for 115200 baud
    comm::Status init(void);

    /// Transmit raw bytes, blocks each byte transfer for TXE (transmit buffer empty) flag
    comm::Status write_blocking(const uint8_t *data, unsigned nbytes);
 private:
    /// Register structure pointer, required CTOR init
    USART_TypeDef *const _regs;

    /// State of the UART driver
    comm::State _state = comm::RESET;
};

#endif  // COMM_UART_HPP_
