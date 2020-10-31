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

#include "rgb_led.h"

#include <stdbool.h>

#include "debug.h"
#include "i2c.h"
#include "lp500x_regs.h"
#include "key_matrix.h"
#include "macros.h"
#include "stm32f0xx.h"

#define I2C_ADDR (0x14)

#define LED_EN GPIO(B, 2)

// extracting color from RGB code
#define R_RGB(rgb_code) ((rgb_code & 0x00FF0000UL) >> 16)
#define G_RGB(rgb_code) ((rgb_code & 0x0000FF00UL) >>  8)
#define B_RGB(rgb_code) ((rgb_code & 0x000000FFUL))

#define LOWEST_ACTIVE_BRIGHTNESS (0x05)
#define BRIGHT_STEPS (5)

static bool breathing_profile = false;

// brighness level, max of BRIGHT_STEPS - 1
static unsigned bright_idx = 2;

static const uint32_t colors[] = {
    COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW
};

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
void RGBLEDInit(void)
{
#define GPIO(port, pin) \
    RCC->AHBENR  |= RCC_AHBENR_GPIO##port##EN;                              \
    GPIO##port->MODER  = (GPIO##port->MODER & ~GPIO_MODER_MODER##pin##_Msk) \
                         | GPIO_MODER_MODER##pin##_0;                       \
    GPIO##port->ODR |= 1UL << pin;
#undef GPIO

    I2CInit();

    // init config registers, starting at DEVICE_CONFIG_0
    const uint8_t init_data[] = {
        DEVICE_CONFIG0_R,
        CHIP_EN,
        LOG_SCALE_EN | POWER_SAVE_EN | AUTO_INCR_EN | PWM_DITHER_EN,
        LED2_BANK_EN | LED1_BANK_EN | LED0_BANK_EN,
        BRIGHTNESS_PERCENT(bright_idx*25),
    };
    I2CMasterTx(I2C_ADDR, sizeof(init_data), init_data);

    RGBLEDBankSetColor(COLOR_WHITE);

    DbgPrintf("Initialized: RGB LED\r\n");
}

/**
 * RGBLEDBankSetColor
 *
 * @brief Sets ALL RGB LEDs to color
 *
 * Since the LEDs are in bank mode, all red/blue/green LEDs get set at once.
 *
 * @param[in] rgb_code RGB hex code to set
 */
void RGBLEDBankSetColor(uint32_t rgb_code)
{
    uint8_t data[4];
    data[0] = BANK_A_COLOR_R;
    data[1] = G_RGB(rgb_code);  // BANK A = Green
    data[2] = B_RGB(rgb_code);  // BANK B = Blue
    data[3] = R_RGB(rgb_code);  // BANK C = Red
    I2CMasterTx(I2C_ADDR, sizeof(data), data);
}

/**
 * RGBLEDBankSetBrightness
 *
 * @brief Sets ALL RGB LEDs brightnesses
 *
 * Since the LEDs are in bank mode, all LED brightnesses set at once.
 *
 * @param[in] val brightness value 0x00-0xFF
 */
void RGBLEDBankSetBrightness(uint8_t val)
{
    uint8_t data[2];
    data[0] = BANK_BRIGHTNESS_R;
    data[1] = val;
    I2CMasterTx(I2C_ADDR, sizeof(data), data);
}

/**
 * RGBLEDTask
 *
 * @brief Task for updating LED brightness.
 *
 * Changes depending on the chosen profile.
 */
void RGBLEDTask(void)
{
    static bool ramp_up = 1;
    static uint8_t brightness = LOWEST_ACTIVE_BRIGHTNESS;

    if (bright_idx > 0) {
        if (breathing_profile) {
            // the breathing profile, down and up in brightness
            if (ramp_up) {
                if (brightness >= BRIGHTNESS_PERCENT(bright_idx*100/BRIGHT_STEPS)) {
                    ramp_up = 0;
                } else {
                    brightness++;
                }
            } else {
                if (brightness <= LOWEST_ACTIVE_BRIGHTNESS) {
                    ramp_up = 1;
                } else {
                    brightness--;
                }
            }
        } else {
            // static brightness depending on setting
            brightness = BRIGHTNESS_PERCENT(bright_idx*100/BRIGHT_STEPS);
        }

        RGBLEDBankSetBrightness(brightness);
    } else {
        RGBLEDBankSetBrightness(0);
    }
}

/**
 * KeyMatrixCallback_BRTUP
 *
 * @brief BRTUP key callback
 *
 * Increases brightness setting up
 */
void KeyMatrixCallback_BRTUP(void)
{
    bright_idx = (bright_idx >= BRIGHT_STEPS - 1) ? BRIGHT_STEPS - 1 : bright_idx + 1;
}

/**
 * KeyMatrixCallback_BRTDN
 *
 * @brief BRTDN key callback
 *
 * Increases brightness setting down
 */
void KeyMatrixCallback_BRTDN(void)
{
    bright_idx = (bright_idx == 0) ? 0 : bright_idx - 1;
}

/**
 * KeyMatrixCallback_COLOR
 *
 * @brief COLOR key callback
 *
 * Cycles through colors
 */
void KeyMatrixCallback_COLOR(void)
{
    static unsigned color_idx = 0;
    color_idx = (color_idx >= (N_ELEMENTS(colors) - 1)) ? 0 : color_idx + 1;
    RGBLEDBankSetColor(colors[color_idx]);
}

/**
 * KeyMatrixCallback_PROF
 *
 * @brief PROF key callback
 *
 * Cycles through coloring profiles
 */
void KeyMatrixCallback_PROF(void)
{
    breathing_profile = (breathing_profile) ? false : true;
}
