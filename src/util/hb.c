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

#include "util/debug.h"
#include "stm32f0xx.h"  // NOLINT

#define HB_LED_ON()  (HB_LED_PORT->ODR |=  (1UL << HB_LED_NUM))
#define HB_LED_OFF() (HB_LED_PORT->ODR &= ~(1UL << HB_LED_NUM))

#define OUTPUT (1UL)

/**
 * @brief Initializes heartbeat LED
 *
 * The LED should have its cathode pulled to ground with a resistor of proper value, and the LED
 * GPIO output port on its anode.
 */
void HeartbeatInit(void)
{
    // enable HB LED GPIO port clock
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // set HB LED as GPIO output
    HB_LED_PORT->MODER = ((HB_LED_PORT->MODER & ~(0x3UL << (HB_LED_NUM * 2)))
            | (OUTPUT << (HB_LED_NUM * 2)));

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