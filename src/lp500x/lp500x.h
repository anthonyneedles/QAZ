/**
 * @file      lp500x.h
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2020/10/31
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Drives the RGB LED(s) via LP5009 LED driver in bank mode (all LEDs get set at once).
 */

#ifndef LP500X_LP500X_H_
#define LP500X_LP500X_H_

#include <stdint.h>

// percent to 256 value
#define BRIGHTNESS_PERCENT(x) (((0xffUL*(x))/100) & 0xffUL)

// RGB values to 24-bit color code
#define RGB_CODE(red, blue, green) \
    (uint32_t)((((uint32_t)(red)   << 16) & 0xff0000UL) | \
               (((uint32_t)(green) <<  8) & 0x00ff00UL) | \
               (((uint32_t)(blue))        & 0x0000ffUL))

// 24-bit color code to RGB values
#define R_RGB(rgb_code) (((uint32_t)(rgb_code) & 0xff0000UL) >> 16)
#define G_RGB(rgb_code) (((uint32_t)(rgb_code) & 0x00ff00UL) >>  8)
#define B_RGB(rgb_code) (((uint32_t)(rgb_code) & 0x0000ffUL))

// RGB color codes
#define COLOR_WHITE   RGB_CODE(0xff, 0xff, 0xff)
#define COLOR_RED     RGB_CODE(0xff, 0x00, 0x00)
#define COLOR_GREEN   RGB_CODE(0x00, 0xff, 0x00)
#define COLOR_BLUE    RGB_CODE(0x00, 0x00, 0xff)
#define COLOR_CYAN    RGB_CODE(0x00, 0xff, 0xff)
#define COLOR_MAGENTA RGB_CODE(0xff, 0x00, 0xff)
#define COLOR_YELLOW  RGB_CODE(0xff, 0xff, 0x00)

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
void LP500xInit(void);

/**
 * @brief Sets ALL RGB LEDs to color
 *
 * Since the LEDs are in bank mode, all red/blue/green LEDs get set at once.
 *
 * @param[in] rgb_code RGB hex code to set
 */
void LP500xBankSetColor(uint32_t rgb_code);

/**
 * @brief Sets ALL RGB LEDs brightnesses
 *
 * Since the LEDs are in bank mode, all LED brightnesses set at once.
 *
 * @param[in] val brightness value 0x00-0xFF
 */
void LP500xBankSetBrightness(uint8_t val);

#endif  // LP500X_LP500X_H_
