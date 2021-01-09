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

// percent to 256 value
constexpr std::uint8_t BRIGHTNESS_PERCENT_TO_256(unsigned percent)
{
    return static_cast<std::uint8_t>((0xff*percent)/100);
}

// RGB values to 24-bit color code
constexpr std::uint32_t RGB_CODE(std::uint8_t red, std::uint8_t blue, std::uint8_t green)
{
    return (static_cast<std::uint32_t>((red   << 16) & 0xff0000) |
            static_cast<std::uint32_t>((green <<  8) & 0x00ff00) |
            static_cast<std::uint32_t>((blue)        & 0x0000ff));
}

// 24-bit color code to RGB values
constexpr std::uint32_t R_RGB(std::uint32_t rgb_code) { return (rgb_code & 0xff0000) >> 16; }
constexpr std::uint32_t G_RGB(std::uint32_t rgb_code) { return (rgb_code & 0x00ff00) >> 8;  }
constexpr std::uint32_t B_RGB(std::uint32_t rgb_code) { return (rgb_code & 0x0000ff);       }

// RGB color codes
constexpr std::uint32_t WHITE   = RGB_CODE(0xff, 0xff, 0xff);
constexpr std::uint32_t RED     = RGB_CODE(0xff, 0x00, 0x00);
constexpr std::uint32_t GREEN   = RGB_CODE(0x00, 0xff, 0x00);
constexpr std::uint32_t BLUE    = RGB_CODE(0x00, 0x00, 0xff);
constexpr std::uint32_t CYAN    = RGB_CODE(0x00, 0xff, 0xff);
constexpr std::uint32_t MAGENTA = RGB_CODE(0xff, 0x00, 0xff);
constexpr std::uint32_t YELLOW  = RGB_CODE(0xff, 0xff, 0x00);

/**
 * @brief Initializes RGB LED
 *
 * Handles setting initial settings to the LED driver for the RGB LED. This includes first setting
 * the LED EN GPIO pin, which brings the LP500x out of SHUTDOWN into INITIALIZATION, then STANDBY.
 * Then sets the chip enable, to go to NORMAL, where the driver starts driving the LEDs.
 *
 * Sets logarithmic dimming curve, power saving, auto incrementing registers, PWM dithering, and
 * a max current of 35mA.
 */
void init(void);

/**
 * @brief Sets ALL RGB LEDs to color
 *
 * Since the LEDs are in bank mode, all red/blue/green LEDs get set at once.
 *
 * @param[in] rgb_code RGB hex code to set
 */
void bank_set_color(std::uint32_t rgb_code);

/**
 * @brief Sets ALL RGB LEDs brightnesses
 *
 * Since the LEDs are in bank mode, all LED brightnesses set at once.
 *
 * @param[in] val brightness value 0x00-0xFF
 */
void bank_set_brightness(std::uint8_t val);

}  // namespace lp500x

#endif  // LP500X_LP500X_HPP_
