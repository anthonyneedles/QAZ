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

/// RGB values to 24-bit color code
constexpr uint32_t RGB_CODE(uint8_t red, uint8_t blue, uint8_t green)
{
    return (static_cast<uint32_t>((red   << 16) & 0xFF0000) |
            static_cast<uint32_t>((green <<  8) & 0x00FF00) |
            static_cast<uint32_t>((blue)        & 0x0000FF));
}

/// 24-bit color code to red value
constexpr uint8_t R_RGB(uint32_t rgb_code) { return (rgb_code & 0xFF0000) >> 16; }

/// 24-bit color code to green value
constexpr uint8_t G_RGB(uint32_t rgb_code) { return (rgb_code & 0x00FF00) >> 8;  }

/// 24-bit color code to blue value
constexpr uint8_t B_RGB(uint32_t rgb_code) { return (rgb_code & 0x0000FF);       }

// RGB color codes
constexpr uint32_t WHITE   = RGB_CODE(0xFF, 0xFF, 0xFF);
constexpr uint32_t RED     = RGB_CODE(0xFF, 0x00, 0x00);
constexpr uint32_t GREEN   = RGB_CODE(0x00, 0xFF, 0x00);
constexpr uint32_t BLUE    = RGB_CODE(0x00, 0x00, 0xFF);
constexpr uint32_t CYAN    = RGB_CODE(0x00, 0xFF, 0xFF);
constexpr uint32_t MAGENTA = RGB_CODE(0xFF, 0x00, 0xFF);
constexpr uint32_t YELLOW  = RGB_CODE(0xFF, 0xFF, 0x00);

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
