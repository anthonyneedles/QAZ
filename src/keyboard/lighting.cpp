/**
 * @file      lighting.cpp
 * @brief     Color profile manager
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Uses IS31FL3746A driver to control the RGB LEDs with backlight coloring profiles.
 */

#include "keyboard/lighting.hpp"

#include <stdint.h>
#include <stdbool.h>

#include "core/time_slice.hpp"
#include "flash/persist.hpp"
#include "is31fl3746a/is31fl3746a.hpp"
#include "keyboard/key_matrix.hpp"
#include "util/debug.hpp"
#include "util/expressions.hpp"

namespace {

/// Task fuction will execute every 10ms
constexpr unsigned LIGHTING_TASK_PERIOD_MS = 5;

/// Lowest brightness that the breathing profile will go down to
constexpr unsigned LOWEST_BREATHING_BRIGHTNESS = 0x01;

/// Amount decremented/incremented each rainbow profile step
constexpr uint8_t RAINBOW_STEPS = 5;

/// Number of different brightness levels to cycle through
constexpr unsigned BRIGHTNESS_LEVELS = 5;

/// Number of different speed levels to cycle through
constexpr unsigned SPEED_LEVELS = 5;

/// Default value for brightness index, if the last value isn't stored in FLASH
constexpr uint16_t DEFAULT_BRIGHT_IDX = BRIGHTNESS_LEVELS - 1;

/// Values that are cycled for red/green/blue intensities
constexpr uint8_t RGB_INTENSITIES[] =
    {
        0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
        0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0xFF
    };

/// Default RGB intensity idx, if the last value isn't stored in FLASH
constexpr uint32_t DEFAULT_INTENSITY_IDX = COUNT_OF(RGB_INTENSITIES) - 1;

/// Default value for profile index, if the last value isn't stored in FLASH
constexpr uint16_t DEFAULT_PROFIE_IDX = 0;

/// Default value for speed index, if the last value isn't stored in FLASH
constexpr uint16_t DEFAULT_SPEED_IDX = SPEED_LEVELS - 1;

/// Converts brightness index to percent, then percent to 64 value
constexpr uint8_t BRIGHTNESS_INDEX_TO_64(unsigned idx)
{
    return is31fl3746a::BRIGHTNESS_PERCENT_TO_64_STEP(
            DIVIDE_ROUND<uint16_t>(idx*100, BRIGHTNESS_LEVELS - 1));
}

/// The backlight coloring profiles
enum ColorProfile {
    PROFILE_SOLID,
    PROFILE_BREATHING,
    PROFILE_RAINBOW,
};

/// Profiles to cycle through
constexpr ColorProfile PROFILES[] = {
    PROFILE_SOLID, PROFILE_BREATHING, PROFILE_RAINBOW,
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
    uint16_t bright_idx;
    uint16_t prof_idx;
    uint16_t speed_idx;
    uint16_t red_idx;
    uint16_t green_idx;
    uint16_t blue_idx;
};

/// Lighting control structure instantiation
LightingCtrl lctrl;

/**
 * @brief Converts RGB indicies to RGB code
 *
 * We track the color as indicies into the intensity array.
 *
 * @return Current color RGB code
 */
uint32_t get_color(void)
{
    return RGB_CODE(RGB_INTENSITIES[lctrl.red_idx],
                    RGB_INTENSITIES[lctrl.green_idx],
                    RGB_INTENSITIES[lctrl.blue_idx]);
}

/**
 * @brief Controls LED brightness for "breathing" profile
 *
 * Ramps brightness level all the way up, then all the way down, over and over. Since the LED driver
 * brightness is gamma scaled, this should result in a (roughly) linear brightness change.
 */
void profile_breathing(void)
{
    static uint8_t  brightness = 0;
    static bool     ramp_up    = true;
    static unsigned loop_cnt   = 0;

    is31fl3746a::set_color(get_color());

    // the lower the speed index, the more loops until we update
    if (loop_cnt < 4*(((SPEED_LEVELS - 1) - lctrl.speed_idx) + 1)) {
        loop_cnt++;
        return;
    } else {
        loop_cnt = 0;
    }

    if (ramp_up) {
        // current bright_idx sets maximum brightness
        if (brightness >= BRIGHTNESS_INDEX_TO_64(lctrl.bright_idx)) {
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

    is31fl3746a::set_brightness(brightness);
}

/**
 * @brief Controls LED color for "rainbow" profile
 *
 * Since color is handled with RGB codes rather than HSV/HSL, cycling through "all" colors is a
 * little awkward. The state machine will cycle through increasing/decreasing each color intensity,
 * which works well enough.
 */
void profile_rainbow(void)
{
    static uint8_t red   = 0xFF;
    static uint8_t green = 0x00;
    static uint8_t blue  = 0x00;
    static RainbowState rainbow_state = BLUE_UP;
    static unsigned loop_cnt = 0;

    is31fl3746a::set_color(RGB_CODE(red, green, blue));
    is31fl3746a::set_brightness(BRIGHTNESS_INDEX_TO_64(lctrl.bright_idx));

    // the lower the speed index, the more loops until we update
    if (loop_cnt < ((SPEED_LEVELS - 1) - lctrl.speed_idx)) {
        loop_cnt++;
        return;
    } else {
        loop_cnt = 0;
    }

    switch (rainbow_state) {
    case BLUE_UP:
        if (blue == 0xFF) {
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
        if (green == 0xFF) {
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
        if (red == 0xFF) {
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

}  // namespace

/**
 * @brief Initializes lighting profile
 *
 * Initializes the is31fl3746a driver for control of the RGB LEDs.
 */
void lighting::init(void)
{
    // read our persistent data. if it doesn't exist in flash, define it with the default value
    persist::read_or_create_data(persist::BRIGHT_IDX,  lctrl.bright_idx, DEFAULT_BRIGHT_IDX);
    persist::read_or_create_data(persist::PROFILE_IDX, lctrl.prof_idx,   DEFAULT_PROFIE_IDX);
    persist::read_or_create_data(persist::SPEED_IDX,   lctrl.speed_idx,  DEFAULT_SPEED_IDX);
    persist::read_or_create_data(persist::RED_IDX,     lctrl.red_idx,    DEFAULT_INTENSITY_IDX);
    persist::read_or_create_data(persist::GREEN_IDX,   lctrl.green_idx,  DEFAULT_INTENSITY_IDX);
    persist::read_or_create_data(persist::BLUE_IDX,    lctrl.blue_idx,   DEFAULT_INTENSITY_IDX);

    is31fl3746a::init();

    is31fl3746a::set_brightness(BRIGHTNESS_INDEX_TO_64(lctrl.bright_idx));
    is31fl3746a::set_color(get_color());

    auto status = timeslice::register_task(LIGHTING_TASK_PERIOD_MS, lighting::task);
    DBG_ASSERT(status == timeslice::SUCCESS);

    debug::puts("Initialized: Lighting\r\n");
}

/**
 * @brief Task for updating RGB LEDs.
 *
 * Runs chosen lighting profile. If the key matrix is idle, or the brightness is at 0, the LED
 * driver will be put into sleep mode, where it will just turn off LEDs.
 */
void lighting::task(void)
{
    static bool was_idle = false;
    bool is_idle = keymatrix::is_idle() || (lctrl.bright_idx == 0);

    // if transitioning into idle, sleep. if transitioning out of idle, wake
    if (!was_idle && is_idle) {
        is31fl3746a::sleep();
    } else if (was_idle && !is_idle) {
        is31fl3746a::wake();
    }

    // don't run any coloring profiles if we are idle
    if (!is_idle) {
        switch (PROFILES[lctrl.prof_idx]) {
        case PROFILE_SOLID:
            is31fl3746a::set_color(get_color());
            is31fl3746a::set_brightness(BRIGHTNESS_INDEX_TO_64(lctrl.bright_idx));
            break;
        case PROFILE_BREATHING:
            profile_breathing();
            break;
        case PROFILE_RAINBOW:
            profile_rainbow();
            break;
        default:
            debug::printf("ERROR: Invalid RGB LED profile idx (%d)\r\n", lctrl.prof_idx);
            lctrl.prof_idx = 0;
            break;
        }
    }

    was_idle = is_idle;
}

// "WarNing: dOcumEnTed SYMboL 'vOid KEYMAtrix::callBaCk_*' WAs nOt DeCLarED Or DeFINed."
//  - big dumb doxygen

//! @cond Doxygen_Suppress

/**
 * @brief BRTUP key callback __WEAK override
 *
 * Brightness setting up. Saturates at max. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_BRTUP(void)
{
    lctrl.bright_idx = NEXT_LINEAR_INDEX(lctrl.bright_idx, BRIGHTNESS_LEVELS);
    persist::write_data(persist::BRIGHT_IDX, lctrl.bright_idx);
}

/**
 * @brief BRTDN key callback __WEAK override
 *
 * Brightness setting down. Saturates at min. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_BRTDN(void)
{
    lctrl.bright_idx = PREV_LINEAR_INDEX(lctrl.bright_idx, BRIGHTNESS_LEVELS);
    persist::write_data(persist::BRIGHT_IDX, lctrl.bright_idx);
}

/**
 * @brief R_UP key callback __WEAK override
 *
 * Red intensity index up. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_R_UP(void)
{
    lctrl.red_idx = NEXT_LINEAR_INDEX(lctrl.red_idx, COUNT_OF(RGB_INTENSITIES) - 1);
    persist::write_data(persist::RED_IDX, lctrl.red_idx);
}

/**
 * @brief R_DN key callback __WEAK override
 *
 * Red intensity index down. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_R_DN(void)
{
    lctrl.red_idx = PREV_LINEAR_INDEX(lctrl.red_idx, COUNT_OF(RGB_INTENSITIES) - 1);
    persist::write_data(persist::RED_IDX, lctrl.red_idx);
}

/**
 * @brief G_UP key callback __WEAK override
 *
 * Green intensity index up. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_G_UP(void)
{
    lctrl.green_idx = NEXT_LINEAR_INDEX(lctrl.green_idx, COUNT_OF(RGB_INTENSITIES) - 1);
    persist::write_data(persist::GREEN_IDX, lctrl.green_idx);
}

/**
 * @brief G_DN key callback __WEAK override
 *
 * Green intensity index down. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_G_DN(void)
{
    lctrl.green_idx = PREV_LINEAR_INDEX(lctrl.green_idx, COUNT_OF(RGB_INTENSITIES) - 1);
    persist::write_data(persist::GREEN_IDX, lctrl.green_idx);
}

/**
 * @brief B_UP key callback __WEAK override
 *
 * Blue intensity index up. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_B_UP(void)
{
    lctrl.blue_idx = NEXT_LINEAR_INDEX(lctrl.blue_idx, COUNT_OF(RGB_INTENSITIES) - 1);
    persist::write_data(persist::BLUE_IDX, lctrl.blue_idx);
}

/**
 * @brief B_DN key callback __WEAK override
 *
 * Blue intensity index down. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_B_DN(void)
{
    lctrl.blue_idx = PREV_LINEAR_INDEX(lctrl.blue_idx, COUNT_OF(RGB_INTENSITIES) - 1);
    persist::write_data(persist::BLUE_IDX, lctrl.blue_idx);
}

/**
 * @brief PROF key callback __WEAK override
 *
 * Cycles through coloring profiles. Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_PROF(void)
{
    lctrl.prof_idx = NEXT_CIRCULAR_INDEX(lctrl.prof_idx, COUNT_OF(PROFILES));
    persist::write_data(persist::PROFILE_IDX, lctrl.prof_idx);
}

/**
 * @brief SPDUP key callback __WEAK override
 *
 * Speeds up coloring of a given profile (if applicable). Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_SPDUP(void)
{
    lctrl.speed_idx = NEXT_LINEAR_INDEX(lctrl.speed_idx, SPEED_LEVELS);
    persist::write_data(persist::SPEED_IDX, lctrl.speed_idx);
}

/**
 * @brief SPDDN key callback __WEAK override
 *
 * Slows down coloring of a given profile (if applicable). Updates persistent data value in FLASH.
 */
extern void keymatrix::callback_SPDDN(void)
{
    lctrl.speed_idx = PREV_LINEAR_INDEX(lctrl.speed_idx, SPEED_LEVELS);
    persist::write_data(persist::SPEED_IDX, lctrl.speed_idx);
}

//! @endcond
