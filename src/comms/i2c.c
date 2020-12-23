/**
 * @file      i2c.c
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

#include "comms/i2c.h"

#include "util/debug.h"

#define GPIO_AFRH_AFSEL10_AF1 (0x1u << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL11_AF1 (0x1u << GPIO_AFRH_AFSEL11_Pos)
#define TX_REG_EMPTY_FLAG  ((I2C1->ISR & I2C_ISR_TXE_Msk)   >> I2C_ISR_TXE_Pos)
#define STOP_COND_GEN_FLAG ((I2C1->ISR & I2C_ISR_STOPF_Msk) >> I2C_ISR_STOPF_Pos)
#define SET 1U

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

    i2c->regs->CR1 &= ~I2C_CR1_PE;

    // enable I2C1 clocking with SYSCLK
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->CFGR3   |= RCC_CFGR3_I2C1SW;

    // enable HB LED GPIO port clock
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // set to SCL/SDA pints to alternate mode
    GPIOB->MODER  &= ~(GPIO_MODER_MODER10_Msk | GPIO_MODER_MODER11_Msk);
    GPIOB->MODER  |=  (GPIO_MODER_MODER10_1   | GPIO_MODER_MODER11_1);

    GPIOB->MODER  &= ~GPIO_MODER_MODER2_Msk;
    GPIOB->MODER  |=  GPIO_MODER_MODER2_0;
    GPIOB->ODR |=  (1UL << 2);

    // set to SCL/SDA pins to open drain
    GPIOB->OTYPER |= (GPIO_OTYPER_OT_10 | GPIO_OTYPER_OT_10);

    // set to SCL/SDA pins to Alternate Function 1
    GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL10_Msk | GPIO_AFRH_AFSEL11_Msk);
    GPIOB->AFR[1] |=  (GPIO_AFRH_AFSEL10_AF1 | GPIO_AFRH_AFSEL11_AF1);

    i2c->regs->TIMINGR = TIMING_CONFIG;
    i2c->regs->CR1 |= I2C_CR1_PE;

    // set own address
    i2c->regs->OAR1 &= ~(I2C_OAR1_OA1EN_Msk);
    i2c->regs->OAR1 &= ~(I2C_OAR1_OA1_Msk);
    i2c->regs->OAR1 |= (((uint32_t)i2c->self_addr << 1U) | I2C_OAR1_OA1EN);

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

    i2c->regs->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk | I2C_CR2_RD_WRN);
    i2c->regs->CR2 |= (((uint32_t)addr << 1U) | I2C_CR2_AUTOEND |
            ((uint32_t)n << I2C_CR2_NBYTES_Pos) | I2C_CR2_START);

    for (int i = 0; i < n; ++i) {
        while (TX_REG_EMPTY_FLAG != SET) {}
        i2c->regs->TXDR = data[i];
    }

    while (STOP_COND_GEN_FLAG != SET) {}
    i2c->regs->ICR |= (I2C_ICR_STOPCF);

    i2c->regs->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_AUTOEND_Msk | I2C_CR2_NBYTES_Msk);

    return I2C_SUCCESS;
}