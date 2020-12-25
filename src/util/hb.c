/**
 * @file      hb.c
 * @brief     Heartbeat LED functionality
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Initializes heartbeat. Flashes heartbeat LED at 1Hz to provide sanity check that program is not
 * hanging and/or violating timeslice scheduling.
 */

#include "util/hb.h"

#include "bsp/bsp.h"
#include "util/debug.h"
#include "util/macros.h"
#include "stm32f0xx.h"  // NOLINT

#define HB_LED_ON()  GPIO_OUTPUT_SET(HB_LED_PORT, HB_LED_PIN)
#define HB_LED_OFF() GPIO_OUTPUT_CLR(HB_LED_PORT, HB_LED_PIN)

/**
 * @brief Initializes heartbeat LED
 *
 * The LED should have its cathode pulled to ground with a resistor of proper value, and the LED
 * GPIO output port on its anode.
 */
void HeartbeatInit(void)
{
    // enable HB LED GPIO port clock, set as output
    GPIO_CLOCK_ENABLE(HB_LED_PORT);
    GPIO_MODE_SET(HB_LED_PORT, HB_LED_PIN, GPIO_OUTPUT);

    DbgPrintf("Initialized: Heartbeat\r\n");
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
        HB_LED_ON();
    } else {
        HB_LED_OFF();
    }
}
