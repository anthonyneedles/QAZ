/**
 * @file      buttons.cpp
 * @brief     Implements button debouncing
 *
 * @author    Anthony Needles
 * @date      2021/06/25
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module performs debouncing of any buttons connected in a low-side switch configuration.
 * When the button is validated as pressed, a callback function is called.
 */

#include "qaz/buttons.hpp"

#include "core/gpio.hpp"
#include "core/time_slice.hpp"
#include "util/debug.hpp"
#include "util/expressions.hpp"

namespace {

/// Task fuction will execute every 10ms
constexpr unsigned DEBOUNCE_TASK_PERIOD_MS = 10;

/// The number of buttons is defined in the bsp
constexpr unsigned NUM_BUTTONS = COUNT_OF(bsp::BUTTONS);

/// States for our debouncing state machine
enum DebounceStates {
    DB_UP,
    DB_MAYBE_DOWN,
    DB_DOWN,
    DB_MAYBE_UP,
};

/// Debounce control structure for each button
struct ButtonCtrl {
    DebounceStates state;
    void (*callback)(void);
};

/// Collection of control structures for all buttons
ButtonCtrl button_ctrl[NUM_BUTTONS];

/**
 * @brief Handles the pressing of the MUTE button (rotary encoder press)
 *
 * When the mute button is pressed we need to toggle the MUTE led.
 *
 * TODO: maybe the is something the host handles??? (like CAPS lock, etc.)
 */
void handle_mute(void)
{
    gpio::toggle_output(bsp::MUTE_LED);
}

}  // namespace

/**
 * @brief Initializes push button reading
 *
 * Each button is pulled up in the board hardware, so we just need set each gpio to input. We also
 * need to initialize each control structure and register our task.
 */
void buttons::init(void)
{
    // init each button gpio as input. initialize button ctrl array
    for (unsigned i = 0; i < NUM_BUTTONS; ++i) {
        gpio::enable_port_clock(bsp::BUTTONS[i]);
        gpio::set_mode(bsp::BUTTONS[i], gpio::INPUT);
        button_ctrl[i].state    = DB_UP;
        button_ctrl[i].callback = nullptr;
    }

    // enable MUTE LED GPIO port clock, set as output
    gpio::enable_port_clock(bsp::MUTE_LED);
    gpio::set_mode(bsp::MUTE_LED, gpio::OUTPUT);

    // TODO for now, we handle the MUTE led here
    auto stat1 = buttons::set_callback(bsp::MUTE, handle_mute);
    DBG_ASSERT(stat1 == buttons::SUCCESS);

    auto stat2 = timeslice::register_task(DEBOUNCE_TASK_PERIOD_MS, buttons::task);
    DBG_ASSERT(stat2 == timeslice::SUCCESS);

    debug::puts("Initialized: Buttons\r\n");
}

/**
 * @brief Run debounce state machine for each button
 *
 * Each button is connected to a gpio input pin, with a (hardware) pullup resistor, in a low-side
 * switch configuration.
 *
 * We scan each button and update the debouncing state accordingly. For a given task period X, the
 * max time between a button being pressed and the button being validated as pressed is ~X.
 *
 * For a task period of 10ms, this is long enough to allow any bouncing to stop, and short enough
 * to result in a near-instant response for the user.
 *
 * The button callback is called only when the button state is transitioning from DB_MAYBE_UP to
 * DB_UP.
 */
void buttons::task(void)
{
    for (unsigned i = 0; i < NUM_BUTTONS; ++i) {
        // read the pin. we need this for state machine input. active low
        bool active = gpio::read_input(bsp::BUTTONS[i]) == gpio::SET ? false : true;

        switch (button_ctrl[i].state) {
        case DB_UP:
            button_ctrl[i].state = active ? DB_MAYBE_UP : DB_UP;
            break;
        case DB_MAYBE_UP:
            if (active) {
                button_ctrl[i].state = DB_DOWN;
                if (button_ctrl[i].callback != nullptr) {
                    button_ctrl[i].callback();
                }
            }
            break;
        case DB_DOWN:
            button_ctrl[i].state = active ? DB_DOWN : DB_MAYBE_DOWN;
            break;
        case DB_MAYBE_DOWN:
            button_ctrl[i].state = active ? DB_DOWN : DB_UP;
            break;
        default:
            // what...
            debug::printf("Invalid button state %d\r\n", button_ctrl[i].state);
            button_ctrl[i].state = DB_UP;
            break;
        }
    }
}

/**
 * @brief Call a button callback (if exists)
 *
 * The given callback will be called exactly one time every time the button is validated as being
 * pressed. If a callback already exists, a new one can't be added.
 *
 * @param[in] id  The ID of the button to set the callback of
 * @param[in] cb  A pointer to the callback function
 *
 * @return OKAY   if success
 *         FAILED if a callback already exists
 */
buttons::Status buttons::set_callback(bsp::ButtonId id, void (*cb)(void))
{
    if (button_ctrl[id].callback == nullptr) {
        button_ctrl[id].callback = cb;
        return buttons::SUCCESS;
    } else {
        return buttons::FAILURE;
    }
}
