/**
 * @file      rgb_led.c
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2020/10/31
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * Drives the RGB LED(s) via LP5009 LED driver in bank mode (all LEDs get set at once).
 */

#ifndef __RGB_LED_H
#define __RGB_LED_H

#include <stdint.h>

#define RGB_LED_TASK_PERIOD_MS (50u)

// percent to 256 value
#define BRIGHTNESS_PERCENT(x) (((0xffUL*(x))/100) & 0xffUL)

// RGB color codes
#define COLOR_WHITE   (0xffffffUL)
#define COLOR_RED     (0xff0000UL)
#define COLOR_GREEN   (0x00ff00UL)
#define COLOR_BLUE    (0x0000ffUL)
#define COLOR_CYAN    (0x00ffffUL)
#define COLOR_MAGENTA (0xff00ffUL)
#define COLOR_YELLOW  (0xffff00UL)

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

#endif /* __RGB_LED_H */
