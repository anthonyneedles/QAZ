/**
 * @file      i2c.cpp
 * @brief     I2C driver
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Low-level I2C driver. Configured for 100kHz SCL frequency.
 *
 * 4.7k resistors are expected close to master device to pull SDA and SCL busses high.
 *
 * Assumes SYSCLK = 48MHz
 */

#include "comm/i2c.hpp"

#include "util/bitop.hpp"
#include "util/debug.hpp"

namespace {

/// Calculated for 100kHz with 48MHz I2C clock
constexpr std::uint32_t TIMING_CONFIG = 0xB0240F13;

}

/**
 * @brief Initializes I2C module
 *
 * Enables clocks for I2C pins as well as I2C module. GPIO configured as open drain with no pull
 * up/down resistors. Expected 4.7k resistors pulling SCL and SDA high. AF1 for both GPIO select
 * I2C SCL and SDA. Timing configuration constant gives a frequency of 100kHz. Clock stretching
 * disabled.
 *
 * @return comm::SUCCCESS - successfully initialized i2c
 *         comm::FAILURE  - failed i2c init (already initialized)
 */
comm::Status I2C::init(void)
{
    if (_state != comm::RESET) {
        debug::printf("I2C init error, not in I2C_RESET (%p)\r\n", _regs);
        return comm::FAILURE;
    }

    bitop::clr_msk(_regs->CR1, I2C_CR1_PE);

    // enable I2C clocking with SYSCLK
    if (_regs == I2C1) {
        bitop::set_msk(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
        bitop::set_msk(RCC->CFGR3,   RCC_CFGR3_I2C1SW);
    } else {
        DBG_ASSERT(debug::FORCE_ASSERT);
        return comm::FAILURE;
    }

    _regs->TIMINGR = TIMING_CONFIG;
    bitop::set_msk(_regs->CR1, I2C_CR1_PE);

    // set own address
    bitop::update_msk(_regs->OAR1, (I2C_OAR1_OA1EN_Msk | I2C_OAR1_OA1_Msk),
            (_self_addr << 1) | I2C_OAR1_OA1EN);

    _state = comm::READY;

    return comm::SUCCESS;
}

/**
 * @brief Master transmit function for I2C
 *
 * Handles master transmission of data to slave. Clears current slave address and number of bytes
 * to be sent values from CR2 register, then populates with passed values. Also, AUTOEND is enabled
 * (stop condition is automatically generated when number of bytes is reached. Start condition is
 * initiated. Data is loaded into transmit data register when register is ready. Data array is
 * iterated through num_bytes number of times, passing all data. The stop condition is confirmed,
 * then stop flag is cleared and CR2 is cleared of set values.
 *
 * @param[in] data    buffer to transmit
 * @param[in] nbytes  number of bytes to transmit
 *
 * @return comm::SUCCCESS - successfully initialized i2c
 *         comm::FAILURE  - failed i2c init (already initialized)
 */
comm::Status I2C::write_blocking(const std::uint8_t *data, unsigned nbytes)
{
    if (!data || (nbytes <= 0)) {
        DBG_ASSERT(debug::FORCE_ASSERT);
        return comm::FAILURE;
    }

    if (_state != comm::READY) {
        debug::printf("I2C write error, not in I2C_READY (%p)\r\n", _regs);
        return comm::FAILURE;
    }

    bitop::clr_msk(_regs->CR2, I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk | I2C_CR2_RD_WRN);
    bitop::set_msk(_regs->CR2, ((uint32_t)_send_addr << 1U) | I2C_CR2_AUTOEND |
            ((uint32_t)nbytes << I2C_CR2_NBYTES_Pos) | I2C_CR2_START);

    for (unsigned i = 0; i < nbytes; ++i) {
        while (bitop::read_bit(_regs->ISR, I2C_ISR_TXE_Pos) != 1) {}
        _regs->TXDR = data[i];
    }

    while (bitop::read_bit(_regs->ISR, I2C_ISR_STOPF_Pos) != 1) {}
    bitop::set_msk(_regs->ICR, I2C_ICR_STOPCF);

    bitop::clr_msk(_regs->CR2, I2C_CR2_SADD_Msk | I2C_CR2_AUTOEND_Msk | I2C_CR2_NBYTES_Msk);

    return comm::SUCCESS;
}
