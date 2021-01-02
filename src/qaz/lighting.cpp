/**
 * @file      lighting.cpp
 * @brief     Color profile manager
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Uses LP500x driver to control the RGB LEDs with backlight coloring profiles.
 */

#include "qaz/lighting.hpp"

#include <stdint.h>
#include <stdbool.h>

#include "lp500x/lp500x.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"

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

// our lighting  control structure
typedef struct {
    int bright_idx;
    int color_idx;
    int profile_idx;
} lighting_ctrl_t;

// colors to cycle through
static const uint32_t COLORS[] = {
    COLOR_WHITE, COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW
};

// profiles to cycle through
static const color_profile_t PROFILES[] = {
    PROFILE_SOLID, PROFILE_BREATHING, PROFILE_RAINBOW,
};

static lighting_ctrl_t lighting = {
    .bright_idx  = BRIGHTNESS_LEVELS - 1,
    .color_idx   = 0,
    .profile_idx = 0,
};

static void lightingProfileBreathing(void);
static void lightingProfileRainbow(void);

/**
 * @brief Initializes lighting profile
 *
 * Initializes the LP500x driver for control of the RGB LEDs.
 */
void LightingInit(void)
{
    LP500xInit();

    LP500xBankSetBrightness(BRIGHTNESS_INDEX(lighting.bright_idx));
    LP500xBankSetColor(COLOR_WHITE);
}

/**
 * @brief Task for updating RGB LEDs.
 *
 * Runs chosen lighting profile, unless at lowest brightness, where it will just turn off LEDs.
 */
void LightingTask(void)
{
    if (lighting.bright_idx > 0) {
        switch (PROFILES[lighting.profile_idx]) {
        case PROFILE_SOLID:
            LP500xBankSetColor(COLORS[lighting.color_idx]);
            LP500xBankSetBrightness(BRIGHTNESS_INDEX(lighting.bright_idx));
            break;
        case PROFILE_BREATHING:
            lightingProfileBreathing();
            break;
        case PROFILE_RAINBOW:
            lightingProfileRainbow();
            break;
        default:
            DbgPrintf("ERROR: Invalid RGB LED profile idx (%d)\r\n", lighting.profile_idx);
            lighting.profile_idx = 0;
            break;
        }
    } else {
        LP500xBankSetBrightness(0);
    }
}

/**
 * @brief Controls LED brightness for "breathing" profile
 *
 * Ramps brightness level all the way up, then all the way down, over and over. Since the LED driver
 * brightness is in logarithmic mode, this should result in a (roughly) linear brightness change.
 */
static void lightingProfileBreathing(void)
{
    static uint8_t brightness = 0;
    static bool    ramp_up    = true;
    static int     loop_cnt   = 0;

    LP500xBankSetColor(COLORS[lighting.color_idx]);

    if (loop_cnt < N_LOOP_UPDATE_BREATHING - 1) {
        loop_cnt++;
        return;
    } else {
        loop_cnt = 0;
    }

    if (ramp_up) {
        if (brightness >= BRIGHTNESS_INDEX(lighting.bright_idx)) {
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

    LP500xBankSetBrightness(brightness);
}

/**
 * @brief Controls LED color for "rainbow" profile
 *
 * Since color is handled with RGB codes rather than HSV/HSL, cycling through "all" colors is a
 * little awkward. The state machine will cycle through increasing/decreasing each color intensity,
 * which works well enough.
 */
static void lightingProfileRainbow(void)
{
    static uint8_t red   = 0xff;
    static uint8_t green = 0x00;
    static uint8_t blue  = 0x00;
    static rainbow_state_t rainbow_state = BLUE_UP;

    LP500xBankSetColor(RGB_CODE(red, green, blue));
    LP500xBankSetBrightness(BRIGHTNESS_INDEX(lighting.bright_idx));

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
    lighting.bright_idx = NEXT_LINEAR_INDEX(lighting.bright_idx, BRIGHTNESS_LEVELS);
}

/**
 * @brief BRTDN key callback
 *
 * Increases brightness setting down. Saturates at min.
 */
void KeyMatrixCallback_BRTDN(void)
{
    lighting.bright_idx = PREV_LINEAR_INDEX(lighting.bright_idx, BRIGHTNESS_LEVELS);
}

/**
 * @brief COLOR key callback
 *
 * Cycles through colors
 */
void KeyMatrixCallback_COLOR(void)
{
    lighting.color_idx = NEXT_CIRCULAR_INDEX(lighting.color_idx, N_ELEMENTS(COLORS));
}

/**
 * @brief PROF key callback
 *
 * Cycles through coloring profiles
 */
void KeyMatrixCallback_PROF(void)
{
    lighting.profile_idx = NEXT_CIRCULAR_INDEX(lighting.profile_idx, N_ELEMENTS(PROFILES));
}
