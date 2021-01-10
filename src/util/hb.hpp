/**
 * @file      hb.hpp
 * @brief     Heartbeat LED functionality
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Initializes heartbeat. Flashes heartbeat LED at 1Hz to provide sanity check that program is not
 * hanging and/or violating timeslice scheduling.
 */

#ifndef UTIL_HB_HPP_
#define UTIL_HB_HPP_

/**
 * @brief Heartbeat namespace
 *
 * This namespace defines the methods for operating the heartbeat LED.
 */
namespace heartbeat {

/// Init heartbeat pin and task
void init(void);

/// Toggle LED
void task(void);

}  // namespace heartbeat

#endif  // UTIL_HB_HPP_
