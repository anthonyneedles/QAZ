/**
 * @file      i2c.c
 * @brief     I2C driver
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * This source file handles all I2C communications. Configured for 100kHz SCL frequency.
 *
 * 4.7k resistors are expected close to master device to pull SDA and SCL busses high.
 *
 * Assumes SYSCLK = 48MHz
 */

#include "comms/i2c.h"

#include "stm32f0xx.h"
#include "util/debug.h"

#define SELF_ADDR (0x53)

#define GPIO_AFRH_AFSEL10_AF1 (0x1u << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL11_AF1 (0x1u << GPIO_AFRH_AFSEL11_Pos)
#define TX_REG_EMPTY_FLAG ((I2C1->ISR & I2C_ISR_TXE_Msk) >> I2C_ISR_TXE_Pos)
#define STOP_COND_GEN_FLAG ((I2C1->ISR & I2C_ISR_STOPF_Msk) >> I2C_ISR_STOPF_Pos)
#define SET 1U

// Calculated for 100kHz with 48MHz I2C clock
#define TIMING_CONFIG 0xB0240F13

/**
 * I2CInit
 *
 * @brief Initializes I2C module
 *
 * Enables clocks for I2C1 pins as well as I2C1 module. GPIO configured as open drain with no pull
 * up/down resistors. Expected 4.7k resistors pulling SCL and SDA high. AF1 for both GPIO select
 * I2C1 SCL and SDA. Timing configuration constant gives a frequency of 100kHz. Clock stretching
 * disabled.
 */
void I2CInit(void)
{
    I2C1->CR1 &= ~I2C_CR1_PE;

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

    I2C1->TIMINGR = TIMING_CONFIG;
    I2C1->CR1 |= I2C_CR1_PE;

    I2CSetOwnAddr(SELF_ADDR);

    DbgPrintf("Initialized: I2C\r\n");
}

/**
 * I2CMasterTx
 *
 * @brief Master transmit function for I2C
 *
 * Handles master transmission of data to slave. Clears current slave address and number of bytes
 * to be sent values from CR2 register, then populates with passed values. Also, AUTOEND is enabled
 * (stop condition is automatically generated when number of bytes is reached. Start condition is
 * initiated. Data is loaded into transmit data register when register is ready. Data array is
 * iterated through num_bytes number of times, passing all data. The stop condition is confirmed,
 * then stop flag is cleared and CR2 is cleared of set values.
 *
 * @param[in] addr      Address of target slave
 * @param[in] num_bytes Number of bytes of data that is desired to be sent
 * @param[in] tx_data   Pointer to 8-bit data array of desired transmit data
 */
void I2CMasterTx(uint8_t addr, uint8_t num_bytes, const uint8_t *tx_data_ptr)
{
    DBG_ASSERT(tx_data_ptr);

    I2C1->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk | I2C_CR2_RD_WRN);
    I2C1->CR2 |= (((uint32_t)addr << 1U) | I2C_CR2_AUTOEND |
            ((uint32_t)num_bytes << I2C_CR2_NBYTES_Pos) | I2C_CR2_START);

    while (num_bytes > 0) {
        while (TX_REG_EMPTY_FLAG != SET) {}
        I2C1->TXDR = *tx_data_ptr;
        tx_data_ptr++;
        num_bytes--;
    }

    while(STOP_COND_GEN_FLAG != SET){}
    I2C1->ICR |= (I2C_ICR_STOPCF);

    I2C1->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_AUTOEND_Msk | I2C_CR2_NBYTES_Msk);
}

/**
 * I2CSetOwnAddr
 *
 * @brief Sets 7-bit address of MCU for slave ability (only OA1)
 *
 * First, OA1 (own address #1) enable is cleared as it must be 0 to set an address. Current address
 * field is then cleared. Passed address is then loaded into 7-bit address field in OA1 register.
 *
 * @param[in] addr Desired 7-bit address
 */
void I2CSetOwnAddr(uint8_t addr)
{
    I2C1->OAR1 &= ~(I2C_OAR1_OA1EN_Msk);
    I2C1->OAR1 &= ~(I2C_OAR1_OA1_Msk);
    I2C1->OAR1 |= (((uint32_t)addr << 1U) | I2C_OAR1_OA1EN);
}
