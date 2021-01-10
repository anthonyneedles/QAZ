/**
 * @file      lp500x.hpp
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2020/10/31
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Drives the RGB LED(s) via LP5009 LED driver in bank mode (all LEDs get set at once).
 */

#ifndef LP500X_LP500X_HPP_
#define LP500X_LP500X_HPP_

#include <cstdint>

/**
 * @brief LP500x namespace
 *
 * This namespace holds both the utility functions for controlling the LP500x external device (via
 * I2C), as well as the registers for that device.
 */
namespace lp500x {

/// Percent to 256 value
constexpr std::uint8_t BRIGHTNESS_PERCENT_TO_256(unsigned percent)
{
    return static_cast<std::uint8_t>((0xff*percent)/100);
}

/// RGB values to 24-bit color code
constexpr std::uint32_t RGB_CODE(std::uint8_t red, std::uint8_t blue, std::uint8_t green)
{
    return (static_cast<std::uint32_t>((red   << 16) & 0xff0000) |
            static_cast<std::uint32_t>((green <<  8) & 0x00ff00) |
            static_cast<std::uint32_t>((blue)        & 0x0000ff));
}

/// 24-bit color code to red value
constexpr std::uint32_t R_RGB(std::uint32_t rgb_code) { return (rgb_code & 0xff0000) >> 16; }

/// 24-bit color code to green value
constexpr std::uint32_t G_RGB(std::uint32_t rgb_code) { return (rgb_code & 0x00ff00) >> 8;  }

/// 24-bit color code to blue value
constexpr std::uint32_t B_RGB(std::uint32_t rgb_code) { return (rgb_code & 0x0000ff);       }

// RGB color codes
constexpr std::uint32_t WHITE   = RGB_CODE(0xff, 0xff, 0xff);
constexpr std::uint32_t RED     = RGB_CODE(0xff, 0x00, 0x00);
constexpr std::uint32_t GREEN   = RGB_CODE(0x00, 0xff, 0x00);
constexpr std::uint32_t BLUE    = RGB_CODE(0x00, 0x00, 0xff);
constexpr std::uint32_t CYAN    = RGB_CODE(0x00, 0xff, 0xff);
constexpr std::uint32_t MAGENTA = RGB_CODE(0xff, 0x00, 0xff);
constexpr std::uint32_t YELLOW  = RGB_CODE(0xff, 0xff, 0x00);

/// Init LP500x, including I2C driver instantiation and pin config
void init(void);

/// Set color for ALL RGB LEDs
void bank_set_color(std::uint32_t rgb_code);

/// Set logarithmic brightness for ALL RGB LEDs
void bank_set_brightness(std::uint8_t val);

}  // namespace lp500x

#endif  // LP500X_LP500X_HPP_
