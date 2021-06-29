/**
 * @file      IS31FL3746A.hpp
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2021/05/19
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * TODO
 */

#ifndef IS31FL3746A_IS31FL3746A_HPP_
#define IS31FL3746A_IS31FL3746A_HPP_

#include <cstdint>

#include "util/macros.hpp"

/**
 * @brief IS31FL3746A namespace
 *
 * This namespace holds both the utility functions for controlling the IS31FL3746A external device
 * (via I2C), as well as the registers for that device.
 */
namespace is31fl3746a {

/// Percent to 64 value (results in value 0-63)
constexpr uint8_t BRIGHTNESS_PERCENT_TO_64_STEP(unsigned percent)
{
    return DIVIDE_ROUND<int>((63*percent), 100);
}

/// Init IS31FL3746A, including I2C driver instantiation and pin config
void init(void);

/// Set color for ALL RGB LEDs
void set_color(uint32_t rgb_code);

/// Set brightness for ALL RGB LEDs
void set_brightness(uint8_t val);

/// Put driver into sleep mode; turn off all LEDs
void sleep(void);

/// Take driver out of sleep mode
void wake(void);

}  // namespace is31fl3746a

#endif  // IS31FL3746A_IS31FL3746A_HPP_
