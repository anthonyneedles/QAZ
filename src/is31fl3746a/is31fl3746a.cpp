/**
 * @file      is31fl3746a.cpp
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2021/05/19
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Drives the RGB LED(s) via IS31FL3746A LED driver in bank mode (all LEDs get set at once).
 *
 * With an R_ISET of 10kΩ, a scale of 255, a current control of 255, using only SW1~SW3,
 * the current for each LED can be calculated via:
 *
 * I_LED = 343/10kΩ * 255/256 * 255/256 * 1/3 * PWM/256
 *
 * So the maximum current per LED is ~11.3mA.
 *
 * There are 64 input PWM steps, which are then converted to a gamma corrected value.
 *
 */

#include "is31fl3746a/is31fl3746a.hpp"

#include <stdbool.h>

#include "bsp/bsp.hpp"
#include "comm/i2c.hpp"
#include "is31fl3746a/is31fl3746a_regs.hpp"
#include "util/debug.hpp"
#include "util/expressions.hpp"

namespace {

/// is31fl3746a slave addressr (grounding ADDR1/ADDR2)
constexpr uint8_t IS31FL3746A_I2C_ADDR = 0x60;

/// Self address of our I2C master peripheral
constexpr uint8_t SELF_ADDR = 0x53;

/// set current control to max for each CSY
constexpr uint8_t CURRENT_CONTROL_VALUE = 255;

/// set current scale for each LED to max. brightness should be set via PWM value
constexpr uint8_t LED_SCALE_VALUE = 255;

/// 64-step gamma correction LUT for setting the PWM
constexpr uint8_t GAMMA_STEP_LUT[] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,  10,  12,  14,  16,  18,  20,  22,
     24,  26,  29,  32,  35,  38,  41,  44,  47,  50,  53,  57,  61,  65,  69,  73,
     77,  81,  85,  89,  94,  99, 104, 109, 114, 119, 124, 129, 134, 140, 146, 152,
    158, 164, 170, 176, 182, 188, 195, 202, 209, 216, 223, 230, 237, 244, 251, 255,
};

/// number of gamma steps for brightness
constexpr int NUM_GAMMA_STEPS = COUNT_OF(GAMMA_STEP_LUT);

/// number of LEDs (18 RGBs)
constexpr int NUM_LEDS = 54;

/// used to hold gamma corrected pwm values
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} PWMValues;

/// RGB LED I2C class object
I2C rgb_i2c(RGB_LED_I2C, SELF_ADDR, IS31FL3746A_I2C_ADDR);

/// save the brightness value for entire board, needed for color setting
uint8_t brightness = 0;

/// save the color value for entire board, needed for brightness setting
uint32_t color = 0;

/**
 * @brief Sets is32fl3746a register page
 *
 * Page 0 contains the PWM registers for each LED. Page 1 contains scale registers for each LED, and
 * several configuration registers.
 *
 * @ param[in] page  PAGE_0 or PAGE_1
 */
void set_page(uint8_t page)
{
    if ((page != is31fl3746a::reg::PAGE_0) && (page != is31fl3746a::reg::PAGE_1)) {
        DBG_ASSERT(debug::FORCE_ASSERT);
        return;
    }

    uint8_t buf[2];

    // first unlock the page select register
    buf[0] = is31fl3746a::reg::PAGE_SEL_WR_LOCK_R;
    buf[1] = is31fl3746a::reg::UNLOCK_CODE;
    rgb_i2c.write_blocking(buf, sizeof(buf));

    // then set the page
    buf[0] = is31fl3746a::reg::PAGE_SEL_R;
    buf[1] = page;
    rgb_i2c.write_blocking(buf, sizeof(buf));
}

/**
 * @brief Sets PWM values for all 36 RGB
 *
 * Each LED has individual PWM control. The value depends on both the brightness, and the color.
 * The non-gamma-scaled value is scaled up and down for EVERY LED based on the brightness. This
 * value is also scaled on the red/green/blue value in the current color, for EVERY red/green/blue
 * LED.
 *
 * Every PWM register where ADDRESS % 3 = 1 is a red LED, ADDRESS % 3 = 2 is green, and
 * ADDRESS % 3 = 0 is blue.
 *
 * For example, if the red-portion of the current color is 127, and the brightness is 32, then the
 * resultant non-gamma-scaled value would be 16. This number will then be used to index into the
 * gamma corrected value LUT to reach a value of 24. If the brightness was then incresed to 48,
 * then the non-gamma-scaled value would be scaled to 24, and corrected value of 47.
 */
void set_pwm(void)
{
    uint8_t idx, rpwm, gpwm, bpwm;
    idx  = DIVIDE_ROUND<uint16_t>(is31fl3746a::R_RGB(color)*brightness, 255);
    rpwm = GAMMA_STEP_LUT[idx];

    idx  = DIVIDE_ROUND<uint16_t>(is31fl3746a::G_RGB(color)*brightness, 255);
    gpwm = GAMMA_STEP_LUT[idx];

    idx  = DIVIDE_ROUND<uint16_t>(is31fl3746a::B_RGB(color)*brightness, 255);
    bpwm = GAMMA_STEP_LUT[idx];

    // set all pwm registers
    uint8_t buf[NUM_LEDS + 1];
    buf[0] = is31fl3746a::reg::LED_PWM_START_R;
    for (int i = 1; i < (NUM_LEDS + 1); i += 3) {
        buf[i]     = rpwm;
        buf[i + 1] = gpwm;
        buf[i + 2] = bpwm;
    }
    set_page(is31fl3746a::reg::PAGE_0);
    rgb_i2c.write_blocking(buf, sizeof(buf));
}

}  // namespace

/**
 * @brief Initializes RGB LED driver
 *
 * Sets ups the I2C driver instantiation (including GPIO pins). Brings the is31fl3746a out of
 * hardware shutdown.
 *
 * Initializes registers by maxing LED current scale, set use of SW1~SW3, max current control value,
 * enable PWM, and bring out of software shutdown.
 */
void is31fl3746a::init(void)
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

    // init scaling registers for all LEDs
    // the device auto-increments the write address
    uint8_t buf[NUM_LEDS + 1];
    buf[0] = is31fl3746a::reg::LED_SCALE_START_R;
    for (int i = 1; i < (NUM_LEDS + 1); ++i) {
        buf[i] = LED_SCALE_VALUE;
    }
    set_page(is31fl3746a::reg::PAGE_1);
    rgb_i2c.write_blocking(buf, NUM_LEDS + 1);

    // continue init, starting at CONFIGURATION, ending at GBL_CURRENT_CTRL
    buf[0] = is31fl3746a::reg::CONFIGURATION_R;
    buf[1] = (is31fl3746a::reg::SWX_SW1_THRU_SW3 << is31fl3746a::reg::SWX_SETTING_SH) |
        is31fl3746a::reg::SW_NORMAL_OPERATION,
    buf[2] = CURRENT_CONTROL_VALUE;
    rgb_i2c.write_blocking(buf, 3);

    // continue init, enable PWM
    buf[0] = is31fl3746a::reg::PWM_FREQ_EN_R;
    buf[1] = is31fl3746a::reg::PWM_EN;
    rgb_i2c.write_blocking(buf, 2);

    debug::puts("Initialized: IS31FL3746A\r\n");
}

/**
 * @brief Sets color for ALL RGB LEDs
 *
 * The input RGB code will be used (along with the current brightness) to calculate corresponding
 * PWM value.
 *
 * @param[in] rgb_code  RGB hex code to set
 */
void is31fl3746a::set_color(uint32_t rgb_code)
{
    color = rgb_code;
    set_pwm();
}

/**
 * @brief Sets brightness for ALL RGB LEDs
 *
 * The input brightness value will be used (along with the current color) to calculate
 * corresponding PWM value.
 *
 * @param[in] val  brightness value [0 - 63]
 */
void is31fl3746a::set_brightness(uint8_t val)
{
    brightness = val % NUM_GAMMA_STEPS;
    set_pwm();
}

/**
 * @brief Put the is31fl3746a into sleep mode
 *
 * Puts the LED driver into "shutdown" mode, which disables all current sources but preserves
 * register states. All LEDs will be disabled.
 */
void is31fl3746a::sleep(void)
{
    uint8_t buf[2];
    buf[0] = is31fl3746a::reg::CONFIGURATION_R;
    buf[1] = (is31fl3746a::reg::SWX_SW1_THRU_SW3 << is31fl3746a::reg::SWX_SETTING_SH) |
        is31fl3746a::reg::SW_SHUTDOWN,
    set_page(is31fl3746a::reg::PAGE_1);
    rgb_i2c.write_blocking(buf, sizeof(buf));
}

/**
 * @brief Brings the is31fl3746a out of sleep mode
 *
 * Puts the LED driver into normal mode, re-enabling all current sources.
 */
void is31fl3746a::wake(void)
{
    uint8_t buf[2];
    buf[0] = is31fl3746a::reg::CONFIGURATION_R;
    buf[1] = (is31fl3746a::reg::SWX_SW1_THRU_SW3 << is31fl3746a::reg::SWX_SETTING_SH) |
        is31fl3746a::reg::SW_NORMAL_OPERATION,
    set_page(is31fl3746a::reg::PAGE_1);
    rgb_i2c.write_blocking(buf, sizeof(buf));
}
