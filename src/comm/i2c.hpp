/**
 * @file      i2c.hpp
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

#ifndef COMM_I2C_HPP_
#define COMM_I2C_HPP_

#include "comm/comm_base.hpp"
#include "stm32f0xx.h"  // NOLINT

/**
 * @brief I2C communication class
 *
 * Derived from the Base communication class, this class implements the I2C driver
 */
class I2C : public CommBase {
 public:
    /// CTOR, initialize private member variables
    explicit I2C(I2C_TypeDef *regs, uint8_t self_addr, uint8_t send_addr = 0) :
        _regs(regs), _self_addr(self_addr), _send_addr(send_addr) {}

    /// I2C init, enables peripheral clocking, self address, and timing config for 100kHz SCL
    comm::Status init(void);

    /// Master transmit raw bytes, blocks each byte transfer for TXE (transmit buffer empty) flag
    comm::Status write_blocking(const uint8_t *data, unsigned nbytes);

    /// Set the I2C slave address
    inline void set_send_addr(uint8_t addr);

 private:
    /// Register structure pointer, required CTOR init
    I2C_TypeDef *const _regs;

    /// Master address of I2C peripheral, required CTOR init
    const uint8_t _self_addr;

    /// Slave address to transmit to, optional CTOR init
    uint8_t _send_addr;

    /// State of the I2C driver
    comm::State _state = comm::RESET;
};

/**
 * @brief Set slave address of I2C transmissions
 *
 * This sets the internally held address of the slave that will be written to.
 *
 * @param addr  8-bit slave address
 */
inline void I2C::set_send_addr(uint8_t addr)
{
    _send_addr = addr;
}

#endif  // COMM_I2C_HPP_
