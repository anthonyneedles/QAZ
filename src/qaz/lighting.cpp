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

#include "qaz/key_matrix.hpp"
#include "core/time_slice.hpp"
#include "lp500x/lp500x.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"

namespace {

/// Task fuction will execute every 10ms
constexpr unsigned LIGHTING_TASK_PERIOD_MS = 10;

/// Every n loops to update breathing profile, to make it go slower
constexpr unsigned N_LOOP_UPDATE_BREATHING = 2;
// TODO: set profile speeds from user input

/// Lowest brightness that the breathing profile will go down to
constexpr unsigned LOWEST_BREATHING_BRIGHTNESS = 0x10;

/// Amount decremented/incremented each rainbow profile step
constexpr unsigned RAINBOW_STEPS = 5;

/// Number of different brightness levels to cycle through
constexpr unsigned BRIGHTNESS_LEVELS = 5;

/// Converts brightness index to percent, then percent to 256 value
constexpr std::uint8_t BRIGHTNESS_INDEX_TO_256(unsigned idx)
{
    return static_cast<uint8_t>(lp500x::BRIGHTNESS_PERCENT_TO_256((idx*100)/BRIGHTNESS_LEVELS));
}

/// The backlight coloring profiles
enum ColorProfile {
    PROFILE_SOLID,
    PROFILE_BREATHING,
    PROFILE_RAINBOW,
};

/// Rainbow profile states
enum RainbowState{
    BLUE_UP,
    RED_DOWN,
    GREEN_UP,
    BLUE_DOWN,
    RED_UP,
    GREEN_DOWN,
};

/// Our lighting  control structure
struct LightingCtrl{
    unsigned bright_idx;
    unsigned color_idx;
    unsigned profile_idx;
};

/// Colors to cycle through
const uint32_t COLORS[] = {
    lp500x::WHITE, lp500x::RED,     lp500x::GREEN, lp500x::BLUE,
    lp500x::CYAN,  lp500x::MAGENTA, lp500x::YELLOW
};

/// Profiles to cycle through
const ColorProfile PROFILES[] = {
    PROFILE_SOLID, PROFILE_BREATHING, PROFILE_RAINBOW,
};

/// Lighting control structure instantiation
LightingCtrl lighting = {
    .bright_idx  = BRIGHTNESS_LEVELS - 1,
    .color_idx   = 0,
    .profile_idx = 0,
};

}  // namespace

static void lightingProfileBreathing(void);
static void lightingProfileRainbow(void);

/**
 * @brief Initializes lighting profile
 *
 * Initializes the LP500x driver for control of the RGB LEDs.
 */
void LightingInit(void)
{
    lp500x::init();

    lp500x::bank_set_brightness(BRIGHTNESS_INDEX_TO_256(lighting.bright_idx));
    lp500x::bank_set_color(lp500x::WHITE);

    auto status = timeslice::register_task(LIGHTING_TASK_PERIOD_MS, LightingTask);
    DBG_ASSERT(status == timeslice::SUCCESS);
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
            lp500x::bank_set_color(COLORS[lighting.color_idx]);
            lp500x::bank_set_brightness(BRIGHTNESS_INDEX_TO_256(lighting.bright_idx));
            break;
        case PROFILE_BREATHING:
            lightingProfileBreathing();
            break;
        case PROFILE_RAINBOW:
            lightingProfileRainbow();
            break;
        default:
            debug::printf("ERROR: Invalid RGB LED profile idx (%d)\r\n", lighting.profile_idx);
            lighting.profile_idx = 0;
            break;
        }
    } else {
        lp500x::bank_set_brightness(0);
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
    static uint8_t  brightness = 0;
    static bool     ramp_up    = true;
    static unsigned loop_cnt   = 0;

    lp500x::bank_set_color(COLORS[lighting.color_idx]);

    if (loop_cnt < N_LOOP_UPDATE_BREATHING - 1) {
        loop_cnt++;
        return;
    } else {
        loop_cnt = 0;
    }

    if (ramp_up) {
        if (brightness >= BRIGHTNESS_INDEX_TO_256(lighting.bright_idx)) {
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

    lp500x::bank_set_brightness(brightness);
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
    static RainbowState rainbow_state = BLUE_UP;

    lp500x::bank_set_color(lp500x::RGB_CODE(red, green, blue));
    lp500x::bank_set_brightness(BRIGHTNESS_INDEX_TO_256(lighting.bright_idx));

    switch (rainbow_state) {
    case BLUE_UP:
        if (blue == 0xff) {
            rainbow_state = RED_DOWN;
        } else {
            blue += RAINBOW_STEPS;
        }
        break;
    case RED_DOWN:
        if (red == 0x00) {
            rainbow_state = GREEN_UP;
        } else {
            red -= RAINBOW_STEPS;
        }
        break;
    case GREEN_UP:
        if (green == 0xff) {
            rainbow_state = BLUE_DOWN;
        } else {
            green += RAINBOW_STEPS;
        }
        break;
    case BLUE_DOWN:
        if (blue == 0x00) {
            rainbow_state = RED_UP;
        } else {
            blue -= RAINBOW_STEPS;
        }
        break;
    case RED_UP:
        if (red == 0xff) {
            rainbow_state = GREEN_DOWN;
        } else {
            red += RAINBOW_STEPS;
        }
        break;
    case GREEN_DOWN:
        if (green == 0x00) {
            rainbow_state = BLUE_UP;
        } else {
            green -= RAINBOW_STEPS;
        }
        break;
    default:
        debug::printf("ERROR: Invalid rainbow profile state (%d)\r\n", rainbow_state);
        rainbow_state = BLUE_UP;
        break;
    }
}

/**
 * @brief BRTUP key callback
 *
 * Increases brightness setting up. Saturates at max.
 */
void keymatrix::callback_BRTUP(void)
{
    lighting.bright_idx = NEXT_LINEAR_INDEX(lighting.bright_idx, BRIGHTNESS_LEVELS);
}

/**
 * @brief BRTDN key callback
 *
 * Increases brightness setting down. Saturates at min.
 */
void keymatrix::callback_BRTDN(void)
{
    lighting.bright_idx = PREV_LINEAR_INDEX(lighting.bright_idx, BRIGHTNESS_LEVELS);
}

/**
 * @brief COLOR key callback
 *
 * Cycles through colors
 */
void keymatrix::callback_COLOR(void)
{
    lighting.color_idx = NEXT_CIRCULAR_INDEX(lighting.color_idx, N_ELEMENTS(COLORS));
}

/**
 * @brief PROF key callback
 *
 * Cycles through coloring profiles
 */
void keymatrix::callback_PROF(void)
{
    lighting.profile_idx = NEXT_CIRCULAR_INDEX(lighting.profile_idx, N_ELEMENTS(PROFILES));
}
