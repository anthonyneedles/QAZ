/**
 * @file      rgb_led.c
 * @brief     RGB LED driver
 *
 * @author    Anthony Needles
 * @date      2020/10/31
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Drives the RGB LED(s) via LP5009 LED driver in bank mode (all LEDs get set at once).
 */

#include "qaz/rgb_led.h"

#include <stdbool.h>

#include "bsp/bsp.h"
#include "comms/i2c.h"
#include "qaz/key_matrix.h"
#include "qaz/lp500x_regs.h"
#include "util/debug.h"
#include "util/macros.h"
#include "stm32f0xx.h"  // NOLINT

#define I2C_ADDR (0x14)

// converts brightness index to percent, then percent to 256 value
#define BRIGHTNESS_INDEX(idx) BRIGHTNESS_PERCENT((idx*100)/BRIGHTNESS_LEVELS)

// every n loops to update breathing profile, to make it go slower
// TODO: set profile speeds from user input
#define N_LOOP_UPDATE_BREATHING (2)

// lowest brightness that the breathing profile will go down to
#define LOWEST_BREATHING_BRIGHTNESS (0x10)

// amount decremented/incremented each rainbow profile step
#define RAINBOW_COLOR_STEPS (5)

// number of different brightness levels to cycle through
#define BRIGHTNESS_LEVELS (5)

// the backlight coloring profiles
typedef enum {
    PROFILE_SOLID,
    PROFILE_BREATHING,
    PROFILE_RAINBOW,
} color_profile_t;

// rainbow profile states
typedef enum {
    BLUE_UP,
    RED_DOWN,
    GREEN_UP,
    BLUE_DOWN,
    RED_UP,
    GREEN_DOWN,
} rainbow_state_t;

// our rgb control structure
typedef struct {
    int bright_idx;
    int color_idx;
    color_profile_t profile;
} rgb_ctrl_t;

// colors to cycle through
static const uint32_t COLORS[] = {
    COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW
};

// profiles to cycle through
static const color_profile_t PROFILES[] = {
    PROFILE_SOLID, PROFILE_BREATHING, PROFILE_RAINBOW,
};

// rgb control structure
static rgb_ctrl_t rgb = {
    .bright_idx = 4,
    .color_idx  = 0,
    .profile    = PROFILE_SOLID,
};

// our handle to the i2c we use to communicate with LED controller
static i2c_handle_t i2c_handle = {
    .regs      = RGB_LED_I2C,
    .state     = I2C_RESET,
    .self_addr = 0x53,
};

static void rgbledProfileBreathing(void);
static void rgbledProfileRainbow(void);

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
void RGBLEDInit(void)
{
    // enable RGB LED EN GPIO port clock, set as output
    GPIO_CLOCK_ENABLE(LED_EN_PORT);
    GPIO_MODE_SET(LED_EN_PORT, LED_EN_PIN, GPIO_OUTPUT);

    // we keep the LED EN pin set
    GPIO_OUTPUT_SET(LED_EN_PORT, LED_EN_PIN);

    // enable I2C SCL/SDA GPIO port clock
    GPIO_CLOCK_ENABLE(RGB_LED_SDA_PORT);
    GPIO_CLOCK_ENABLE(RGB_LED_SCL_PORT);

    // set to SCL/SDA pints to alternate mode
    GPIO_MODE_SET(RGB_LED_SDA_PORT, RGB_LED_SDA_PIN, GPIO_ALTFN);
    GPIO_MODE_SET(RGB_LED_SCL_PORT, RGB_LED_SCL_PIN, GPIO_ALTFN);

    // set to SCL/SDA pins to open drain
    GPIO_OUTPUT_TYPE_SET(RGB_LED_SDA_PORT, RGB_LED_SDA_PIN, GPIO_OPEN_DRAIN);
    GPIO_OUTPUT_TYPE_SET(RGB_LED_SCL_PORT, RGB_LED_SCL_PIN, GPIO_OPEN_DRAIN);

    // set to SCL/SDA pins to Alternate Function 1
    GPIO_AF_SET(RGB_LED_SDA_PORT, RGB_LED_SDA_PIN, GPIO_AF1);
    GPIO_AF_SET(RGB_LED_SCL_PORT, RGB_LED_SCL_PIN, GPIO_AF1);

    I2CInit(&i2c_handle);

    // init config registers, starting at DEVICE_CONFIG_0 register
    const uint8_t init_data[] = {
        DEVICE_CONFIG0_R,
        CHIP_EN,
        LOG_SCALE_EN | POWER_SAVE_EN | AUTO_INCR_EN | PWM_DITHER_EN,
        LED2_BANK_EN | LED1_BANK_EN | LED0_BANK_EN,
        BRIGHTNESS_PERCENT(rgb.bright_idx*25),
    };
    I2CWriteMasterBlocking(&i2c_handle, I2C_ADDR, init_data, sizeof(init_data));

    RGBLEDBankSetColor(COLOR_WHITE);

    DbgPrintf("Initialized: RGB LED\r\n");
}

/**
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
    data[1] = R_RGB(rgb_code);  // BANK A = Red
    data[2] = G_RGB(rgb_code);  // BANK B = Green
    data[3] = B_RGB(rgb_code);  // BANK C = Blue
    I2CWriteMasterBlocking(&i2c_handle, I2C_ADDR, data, sizeof(data));
}

/**
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
    I2CWriteMasterBlocking(&i2c_handle, I2C_ADDR, data, sizeof(data));
}

/**
 * @brief Task for updating RGB LEDs.
 *
 * Runs chosen lighting profile, unless at lowest brightness, where it will just turn off LEDs.
 */
void RGBLEDTask(void)
{
    if (rgb.bright_idx > 0) {
        switch (rgb.profile) {
        case PROFILE_SOLID:
            RGBLEDBankSetColor(COLORS[rgb.color_idx]);
            RGBLEDBankSetBrightness(BRIGHTNESS_INDEX(rgb.bright_idx));
            break;
        case PROFILE_BREATHING:
            rgbledProfileBreathing();
            break;
        case PROFILE_RAINBOW:
            rgbledProfileRainbow();
            break;
        default:
            DbgPrintf("ERROR: Invalid RGB LED profile (%d)\r\n", rgb.profile);
            rgb.profile = PROFILE_SOLID;
            break;
        }
    } else {
        RGBLEDBankSetBrightness(0);
    }
}

/**
 * @brief Controls LED brightness for "breathing" profile
 *
 * Ramps brightness level all the way up, then all the way down, over and over. Since the LED driver
 * brightness is in logarithmic mode, this should result in a (roughly) linear brightness change.
 */
static void rgbledProfileBreathing(void)
{
    static uint8_t brightness = 0;
    static bool    ramp_up    = true;
    static int     loop_cnt   = 0;

    RGBLEDBankSetColor(COLORS[rgb.color_idx]);

    if (loop_cnt < N_LOOP_UPDATE_BREATHING - 1) {
        loop_cnt++;
        return;
    } else {
        loop_cnt = 0;
    }

    if (ramp_up) {
        if (brightness >= BRIGHTNESS_INDEX(rgb.bright_idx)) {
            ramp_up = false;
        } else {
            brightness++;
        }
    } else {
        if (brightness <= LOWEST_BREATHING_BRIGHTNESS) {
            ramp_up = true;
        } else {
            brightness--;
        }
    }

    RGBLEDBankSetBrightness(brightness);
}

/**
 * @brief Controls LED color for "rainbow" profile
 *
 * Since color is handled with RGB codes rather than HSV/HSL, cycling through "all" colors is a
 * little awkward. The state machine will cycle through increasing/decreasing each color intensity,
 * which works well enough.
 */
static void rgbledProfileRainbow(void)
{
    static uint8_t red   = 0xff;
    static uint8_t green = 0x00;
    static uint8_t blue  = 0x00;
    static rainbow_state_t rainbow_state = BLUE_UP;

    RGBLEDBankSetColor(RGB_CODE(red, green, blue));
    RGBLEDBankSetBrightness(BRIGHTNESS_INDEX(rgb.bright_idx));

    switch (rainbow_state) {
    case BLUE_UP:
        if (blue == 0xff) {
            rainbow_state = RED_DOWN;
        } else {
            blue += 5;
        }
        break;
    case RED_DOWN:
        if (red == 0x00) {
            rainbow_state = GREEN_UP;
        } else {
            red -= 5;
        }
        break;
    case GREEN_UP:
        if (green == 0xff) {
            rainbow_state = BLUE_DOWN;
        } else {
            green += 5;
        }
        break;
    case BLUE_DOWN:
        if (blue == 0x00) {
            rainbow_state = RED_UP;
        } else {
            blue -= 5;
        }
        break;
    case RED_UP:
        if (red == 0xff) {
            rainbow_state = GREEN_DOWN;
        } else {
            red += 5;
        }
        break;
    case GREEN_DOWN:
        if (green == 0x00) {
            rainbow_state = BLUE_UP;
        } else {
            green -= 5;
        }
        break;
    default:
        DbgPrintf("ERROR: Invalid rainbow profile state (%d)\r\n", rainbow_state);
        rainbow_state = BLUE_UP;
        break;
    }
}

/**
 * @brief BRTUP key callback
 *
 * Increases brightness setting up. Saturates at max.
 */
void KeyMatrixCallback_BRTUP(void)
{
    rgb.bright_idx = NEXT_LINEAR_INDEX(rgb.bright_idx, BRIGHTNESS_LEVELS);
}

/**
 * @brief BRTDN key callback
 *
 * Increases brightness setting down. Saturates at min.
 */
void KeyMatrixCallback_BRTDN(void)
{
    rgb.bright_idx = PREV_LINEAR_INDEX(rgb.bright_idx, BRIGHTNESS_LEVELS);
}

/**
 * @brief COLOR key callback
 *
 * Cycles through colors
 */
void KeyMatrixCallback_COLOR(void)
{
    rgb.color_idx = NEXT_CIRCULAR_INDEX(rgb.color_idx, N_ELEMENTS(COLORS));
}

/**
 * @brief PROF key callback
 *
 * Cycles through coloring profiles
 */
void KeyMatrixCallback_PROF(void)
{
    rgb.profile = NEXT_CIRCULAR_INDEX(rgb.profile, N_ELEMENTS(PROFILES));
}
