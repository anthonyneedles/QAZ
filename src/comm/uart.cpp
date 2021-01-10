/**
 * @file      uart.cpp
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

#include "comm/uart.hpp"

#include "util/bitop.hpp"
#include "util/debug.hpp"

namespace {

/// Calculated for 115200 baud with 48MHz UART clock
constexpr std::uint16_t BAUD_115200 = 0x1A1;

}

/**
 * @brief Enables USART for TX at 115200 baud, 8-N-1.
 *
 * @return comm::SUCCESS - successfully initialized uart
 *         comm::FAILURE - failed uart init (already initialized)
 */
comm::Status UART::init(void)
{
    if (_state != comm::RESET) {
        debug::printf("UART init error, not in comm::RESET (%p)\r\n", _regs);
        return comm::FAILURE;
    }

    // Enable clock for given USART
    if (_regs == USART1) {
        bitop::set_msk(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
    } else {
        DBG_ASSERT(debug::FORCE_ASSERT);
        return comm::FAILURE;
    }

    // Enable transmitting
    _regs->CR1 = USART_CR1_TE;

    // Set baudrate to 115200
    _regs->BRR = BAUD_115200;

    // Enable USART1
    bitop::set_msk(_regs->CR1, USART_CR1_UE);

    _state = comm::READY;

    return comm::SUCCESS;
}

/**
 * @brief Sends data over USART, blocking on write ready
 *
 * Blocks until USART is ready to transmit, then pushes character onto output buffer.
 *
 * @param[in] data    buffer to transmit
 * @param[in] nbytes  number of bytes to transmit
 *
 * @return comm::SUCCESS - successful uart write
 *         comm::FAILURE - failed uart write (not ready, invalid buf)
 */
comm::Status UART::write_blocking(const std::uint8_t *data, unsigned nbytes)
{
    if (!data || (nbytes <= 0)) {
        DBG_ASSERT(debug::FORCE_ASSERT);
        return comm::FAILURE;
    }

    if (_state != comm::READY) {
        debug::printf("UART write error, not in comm::READY (%p)\r\n", _regs);
        return comm::FAILURE;
    }

    for (unsigned i = 0; i < nbytes; ++i) {
        while (bitop::read_bit(_regs->ISR, USART_ISR_TXE_Pos) != 1) {}
        _regs->TDR = data[i];
    }

    return comm::SUCCESS;
}
