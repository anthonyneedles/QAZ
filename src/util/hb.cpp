/**
 * @file      hb.cpp
 * @brief     Heartbeat LED functionality
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Initializes heartbeat. Flashes heartbeat LED at 1Hz to provide sanity check that program is not
 * hanging and/or violating timeslice scheduling.
 */

#include "util/hb.hpp"

#include "bsp/bsp.hpp"
#include "core/time_slice.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"

namespace {

// task fuction will execute every 500ms (LED will flash at 1Hz)
constexpr unsigned HB_TASK_PERIOD_MS = 500;

}

/**
 * @brief Initializes heartbeat LED
 *
 * The LED should have its cathode pulled to ground with a resistor of proper value, and the LED
 * GPIO output port on its anode.
 */
void HeartbeatInit(void)
{
    // enable HB LED GPIO port clock, set as output
    gpio::enable_port_clock(bsp::HB_LED);
    gpio::set_mode(bsp::HB_LED, gpio::OUTPUT);

    auto status = timeslice::register_task(HB_TASK_PERIOD_MS, HeartbeatTask);
    DBG_ASSERT(status == timeslice::SUCCESS);

    debug::puts("Initialized: Heartbeat\r\n");
}

/**
 * @brief Task to toggle HB LED at 1Hz
 *
 * Just toggles the LED each entry
 */
void HeartbeatTask(void)
{
    static int state = 0;

    state = !state;

    if (state) {
        gpio::set_output(bsp::HB_LED);
    } else {
        gpio::clr_output(bsp::HB_LED);
    }
}
