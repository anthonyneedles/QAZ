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
    // ctor, initialize private member variables
    explicit I2C(I2C_TypeDef *regs, std::uint8_t self_addr, std::uint8_t send_addr = 0) :
        _regs(regs), _self_addr(self_addr), _send_addr(send_addr) {}

    // implementing base methods
    comm::Status init(void);
    comm::Status write_blocking(const std::uint8_t *data, unsigned nbytes);

    inline void set_send_addr(std::uint8_t addr);
 private:
    // must be set via ctor initializer list
    I2C_TypeDef *const _regs;
    const std::uint8_t _self_addr;

    // can be set via ctor initializer list OR set_send_addr()
    std::uint8_t _send_addr;

    comm::State _state = comm::RESET;
};

/**
 * @brief Set slave address of I2C transmissions
 *
 * This sets the internally held address of the slave that will be written to.
 */
inline void I2C::set_send_addr(std::uint8_t addr)
{
    _send_addr = addr;
}

#endif  // COMM_I2C_HPP_
