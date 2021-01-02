/**
 * @file      i2c.cpp
 * @brief     I2C driver
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This source file handles all I2C communications. Configured for 100kHz SCL frequency.
 *
 * 4.7k resistors are expected close to master device to pull SDA and SCL busses high.
 *
 * Assumes SYSCLK = 48MHz
 */

#include "comms/i2c.hpp"

#include "util/debug.hpp"
#include "util/macros.hpp"

// Calculated for 100kHz with 48MHz I2C clock
#define TIMING_CONFIG 0xB0240F13

/**
 * @brief Initializes I2C module
 *
 * Enables clocks for I2C pins as well as I2C module. GPIO configured as open drain with no pull
 * up/down resistors. Expected 4.7k resistors pulling SCL and SDA high. AF1 for both GPIO select
 * I2C SCL and SDA. Timing configuration constant gives a frequency of 100kHz. Clock stretching
 * disabled.
 *
 * @param[in] i2c handle for i2c to init
 * @return I2C_SUCCCESS - successfully initialized i2c
 *         I2C_FAILURE  - failed i2c init (already initialized)
 */
i2c_status_t I2CInit(i2c_handle_t *i2c)
{
    if (!i2c) {
        DBG_ASSERT(FORCE_ASSERT);
        return I2C_FAILURE;
    }

    if (i2c->state != I2C_RESET) {
        DbgPrintf("I2C init error, not in I2C_RESET (%p)\r\n", i2c->regs);
        return I2C_FAILURE;
    }

    CLR(i2c->regs->CR1, I2C_CR1_PE);

    // enable I2C clocking with SYSCLK
    if (i2c->regs == I2C1) {
        SET(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
        SET(RCC->CFGR3,   RCC_CFGR3_I2C1SW);
    } else {
        DBG_ASSERT(FORCE_ASSERT);
        return I2C_FAILURE;
    }

    i2c->regs->TIMINGR = TIMING_CONFIG;
    SET(i2c->regs->CR1, I2C_CR1_PE);

    // set own address
    BITMASK_UPDATE(i2c->regs->OAR1, (I2C_OAR1_OA1EN_Msk | I2C_OAR1_OA1_Msk),
            (i2c->self_addr << 1) | I2C_OAR1_OA1EN);

    i2c->state = I2C_READY;

    return I2C_SUCCESS;
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
 * @param[in] i2c  handle for i2c to init
 * @param[in] addr address of target slave
 * @param[in] data buffer to transmit
 * @param[in] n    number of bytes to transmit
 * @return I2C_SUCCCESS - successfully initialized i2c
 *         I2C_FAILURE  - failed i2c init (already initialized)
 */
i2c_status_t I2CWriteMasterBlocking(i2c_handle_t *i2c, uint8_t addr, const uint8_t *data, int n)
{
    if (!i2c || !data || (n <= 0)) {
        DBG_ASSERT(FORCE_ASSERT);
        return I2C_FAILURE;
    }

    if (i2c->state != I2C_READY) {
        DbgPrintf("I2C write error, not in I2C_READY (%p)\r\n", i2c->regs);
        return I2C_FAILURE;
    }

    CLR(i2c->regs->CR2, I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk | I2C_CR2_RD_WRN);
    SET(i2c->regs->CR2, ((uint32_t)addr << 1U) | I2C_CR2_AUTOEND |
            ((uint32_t)n << I2C_CR2_NBYTES_Pos) | I2C_CR2_START);

    for (int i = 0; i < n; ++i) {
        while (BIT_READ(i2c->regs->ISR, I2C_ISR_TXE_Pos) != 1) {}
        i2c->regs->TXDR = data[i];
    }

    while (BIT_READ(i2c->regs->ISR, I2C_ISR_STOPF_Pos) != 1) {}
    SET(i2c->regs->ICR, I2C_ICR_STOPCF);

    CLR(i2c->regs->CR2, I2C_CR2_SADD_Msk | I2C_CR2_AUTOEND_Msk | I2C_CR2_NBYTES_Msk);

    return I2C_SUCCESS;
}
