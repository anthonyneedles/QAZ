/**
 * @file      hb.h
 * @brief     Heartbeat LED functionality
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Initializes heartbeat. Flashes heartbeat LED at 1Hz to provide sanity check that program is not
 * hanging and/or violating timeslice scheduling.
 */

#ifndef UTIL_HB_H_
#define UTIL_HB_H_

#define HB_TASK_PERIOD_MS (500)

/**
 * @brief Initializes heartbeat LED
 *
 * The LED should have its cathode pulled to ground with a resistor of proper value, and the LED
 * GPIO output port on its anode.
 */
void HeartbeatInit(void);

/**
 * @brief Task to toggle HB LED at 1Hz
 *
 * Just toggles the LED each entry
 */
void HeartbeatTask(void);

#endif  // UTIL_HB_H_
