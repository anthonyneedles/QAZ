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

#ifndef __COMMS_I2C_H_
#define __COMMS_I2C_H_

#include <stdint.h>

#include "stm32f0xx.h"

// status code returned by I2C API
typedef enum {
    I2C_SUCCESS,
    I2C_FAILURE,
} i2c_status_t;

// state of a given I2C instance
typedef enum {
    I2C_RESET = 0,
    I2C_READY,
} i2c_state_t;

// handle for an I2C instance, holds control information
typedef struct {
    I2C_TypeDef *regs;
    i2c_state_t state;
    uint8_t self_addr;
} i2c_handle_t;

/**
 * I2CInit
 *
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
i2c_status_t I2CInit(i2c_handle_t *i2c);

/**
 * I2CWriteMasterBlocking
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
 * @param[in] i2c  handle for i2c to init
 * @param[in] addr address of target slave
 * @param[in] data buffer to transmit
 * @param[in] n    number of bytes to transmit
 * @return I2C_SUCCCESS - successfully initialized i2c
 *         I2C_FAILURE  - failed i2c init (already initialized)
 */
i2c_status_t I2CWriteMasterBlocking(i2c_handle_t *i2c, uint8_t addr, const uint8_t *data, int n);

#endif /* __COMMS_I2C_H_ */
