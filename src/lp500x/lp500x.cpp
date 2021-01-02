/**
 * @file      lp500x.c
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2020/10/31
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Drives the RGB LED(s) via LP5009 LED driver in bank mode (all LEDs get set at once).
 */

#include "lp500x/lp500x.hpp"

#include <stdbool.h>

#include "bsp/bsp.hpp"
#include "comms/i2c.hpp"
#include "lp500x/lp500x_regs.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"

#define LP500X_I2C_ADDR (0x14)

// our handle to the i2c we use to communicate with LED controller
static i2c_handle_t i2c_handle = {
    .regs      = RGB_LED_I2C,
    .state     = I2C_RESET,
    .self_addr = 0x53,
};

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
void LP500xInit(void)
{
    // enable RGB LED EN GPIO port clock, set as output, and keep set
    bsp::rgb_led_en::enable_port_clock();
    bsp::rgb_led_en::set_mode(gpio::OUTPUT);
    bsp::rgb_led_en::set_output();

    // enable I2C SCL/SDA GPIO port clocks, put in alt mode 1 (I2C) as open drain
    bsp::rgb_led_sda::enable_port_clock();
    bsp::rgb_led_sda::set_mode(gpio::ALTFN);
    bsp::rgb_led_sda::set_output_type(gpio::OPEN_DRAIN);
    bsp::rgb_led_sda::set_altfn(gpio::ALTFN_1);
    bsp::rgb_led_scl::enable_port_clock();
    bsp::rgb_led_scl::set_mode(gpio::ALTFN);
    bsp::rgb_led_scl::set_output_type(gpio::OPEN_DRAIN);
    bsp::rgb_led_scl::set_altfn(gpio::ALTFN_1);

    I2CInit(&i2c_handle);

    // init config registers, starting at DEVICE_CONFIG_0 register
    const uint8_t init_data[] = {
        DEVICE_CONFIG0_R,
        CHIP_EN,
        LOG_SCALE_EN | POWER_SAVE_EN | AUTO_INCR_EN | PWM_DITHER_EN,
        LED2_BANK_EN | LED1_BANK_EN  | LED0_BANK_EN,
    };
    I2CWriteMasterBlocking(&i2c_handle, LP500X_I2C_ADDR, init_data, sizeof(init_data));

    DbgPrintf("Initialized: RGB LED\r\n");
}

/**
 * @brief Sets ALL RGB LEDs to color
 *
 * Since the LEDs are in bank mode, all red/blue/green LEDs get set at once.
 *
 * @param[in] rgb_code RGB hex code to set
 */
void LP500xBankSetColor(uint32_t rgb_code)
{
    uint8_t data[4];
    data[0] = BANK_A_COLOR_R;
    data[1] = R_RGB(rgb_code);  // BANK A = Red
    data[2] = G_RGB(rgb_code);  // BANK B = Green
    data[3] = B_RGB(rgb_code);  // BANK C = Blue
    I2CWriteMasterBlocking(&i2c_handle, LP500X_I2C_ADDR, data, sizeof(data));
}

/**
 * @brief Sets ALL RGB LEDs brightnesses
 *
 * Since the LEDs are in bank mode, all LED brightnesses set at once.
 *
 * @param[in] val brightness value 0x00-0xFF
 */
void LP500xBankSetBrightness(uint8_t val)
{
    uint8_t data[2];
    data[0] = BANK_BRIGHTNESS_R;
    data[1] = val;
    I2CWriteMasterBlocking(&i2c_handle, LP500X_I2C_ADDR, data, sizeof(data));
}
