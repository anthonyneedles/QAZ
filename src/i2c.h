/**
 * @file      i2c.h
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
 */

#ifndef __I2C_H_
#define __I2C_H_

#include "stdint.h"

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
void I2CInit(void);

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
void I2CMasterTx(uint8_t addr, uint8_t num_bytes, const uint8_t *tx_data);

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
void I2CSetOwnAddr(uint8_t addr);

#endif /* __I2C_H_ */
