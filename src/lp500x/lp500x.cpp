/**
 * @file      lp500x.cpp
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
#include "comm/i2c.hpp"
#include "lp500x/lp500x_regs.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"

namespace {

/// LP500x broadcast address
constexpr uint8_t LP500X_I2C_ADDR = 0x14;

/// Self address of our I2C master peripheral
constexpr uint8_t SELF_ADDR = 0x53;

/// RGB LED I2C class object
I2C rgb_i2c(RGB_LED_I2C, SELF_ADDR, LP500X_I2C_ADDR);

}  // namespace

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
void lp500x::init(void)
{
    // enable RGB LED EN GPIO port clock, set as output, and keep set
    gpio::enable_port_clock(bsp::RGB_EN);
    gpio::set_mode(bsp::RGB_EN, gpio::OUTPUT);
    gpio::set_output(bsp::RGB_EN);

    // enable I2C SCL/SDA GPIO port clocks, put in alt mode 1 (I2C) as open drain
    gpio::enable_port_clock(bsp::RGB_SDA);
    gpio::set_mode(bsp::RGB_SDA, gpio::ALTFN);
    gpio::set_output_type(bsp::RGB_SDA, gpio::OPEN_DRAIN);
    gpio::set_altfn(bsp::RGB_SDA, gpio::ALTFN_1);
    gpio::enable_port_clock(bsp::RGB_SCL);
    gpio::set_mode(bsp::RGB_SCL, gpio::ALTFN);
    gpio::set_output_type(bsp::RGB_SCL, gpio::OPEN_DRAIN);
    gpio::set_altfn(bsp::RGB_SCL, gpio::ALTFN_1);

    rgb_i2c.init();

    // init config registers, starting at DEVICE_CONFIG_0 register
    const uint8_t init_data[] = {
        lp500x::DEVICE_CONFIG0_R,
        lp500x::CHIP_EN,
        lp500x::LOG_SCALE_EN | lp500x::POWER_SAVE_EN | lp500x::AUTO_INCR_EN | lp500x::PWM_DITHER_EN,
        lp500x::LED2_BANK_EN | lp500x::LED1_BANK_EN  | lp500x::LED0_BANK_EN,
    };
    rgb_i2c.write_blocking(init_data, sizeof(init_data));

    debug::puts("Initialized: LP500x\r\n");
}

/**
 * @brief Sets ALL RGB LEDs to color
 *
 * Since the LEDs are in bank mode, all red/blue/green LEDs get set at once.
 *
 * @param[in] rgb_code  RGB hex code to set
 */
void lp500x::bank_set_color(uint32_t rgb_code)
{
    uint8_t data[4];
    data[0] = lp500x::BANK_A_COLOR_R;
    data[1] = lp500x::R_RGB(rgb_code);  // BANK A = Red
    data[2] = lp500x::G_RGB(rgb_code);  // BANK B = Green
    data[3] = lp500x::B_RGB(rgb_code);  // BANK C = Blue
    rgb_i2c.write_blocking(data, sizeof(data));
}

/**
 * @brief Sets ALL RGB LEDs brightnesses
 *
 * Since the LEDs are in bank mode, all LED brightnesses set at once.
 *
 * @param[in] val  brightness value 0x00-0xFF
 */
void lp500x::bank_set_brightness(uint8_t val)
{
    uint8_t data[2];
    data[0] = lp500x::BANK_BRIGHTNESS_R;
    data[1] = val;
    rgb_i2c.write_blocking(data, sizeof(data));
}
