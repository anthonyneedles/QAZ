/**
 * @file      rgb_led.h
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2020/10/31
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * Drives the RGB LED(s) via LP5009 LED driver in bank mode (all LEDs get set at once).
 */

#ifndef __QAZ_RGB_LED_H
#define __QAZ_RGB_LED_H

#include <stdint.h>

#include "bsp/bsp.h"

#define RGB_LED_TASK_PERIOD_MS (10U)

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
 * RGBLEDInit
 *
 * @brief Initializes RGB LED
 *
 * Handles setting initial settings to the LED driver for the RGB LED. This includes first setting
 * the LED EN GPIO pin, which brings the LP500x out of SHUTDOWN into INITIALIZATION, then STANDBY.
 * Then sets the chip enable, to go to NORMAL, where the driver starts driving the LEDs.
 *
 * Sets logarithmic dimming curve, power saving, auto incrementing registers, PWM dithering, and
 * a max current of 35mA.
 */
void RGBLEDInit(void);

/**
 * RGBLEDBankSetColor
 *
 * @brief Sets ALL RGB LEDs to color
 *
 * Since the LEDs are in bank mode, all red/blue/green LEDs get set at once.
 *
 * @param[in] rgb_code RGB hex code to set
 */
void RGBLEDBankSetColor(uint32_t rgb_code);

/**
 * RGBLEDBankSetBrightness
 *
 * @brief Sets ALL RGB LEDs brightnesses
 *
 * Since the LEDs are in bank mode, all LED brightnesses set at once.
 *
 * @param[in] val brightness value 0x00-0xFF
 */
void RGBLEDBankSetBrightness(uint8_t val);

/**
 * RGBLEDTask
 *
 * @brief Task for updating LED brightness.
 *
 * Changes depending on the chosen profile.
 */
void RGBLEDTask(void);

/**
 * KeyMatrixCallback_BRTUP
 *
 * @brief BRTUP key callback
 *
 * Increases brightness setting up
 */
void KeyMatrixCallback_BRTUP(void);

/**
 * KeyMatrixCallback_BRTDN
 *
 * @brief BRTDN key callback
 *
 * Increases brightness setting down
 */
void KeyMatrixCallback_BRTDN(void);

/**
 * KeyMatrixCallback_COLOR
 *
 * @brief COLOR key callback
 *
 * Cycles through colors
 */
void KeyMatrixCallback_COLOR(void);

/**
 * KeyMatrixCallback_PROF
 *
 * @brief PROF key callback
 *
 * Cycles through coloring profiles
 */
void KeyMatrixCallback_PROF(void);

#endif /* __QAZ_RGB_LED_H */
