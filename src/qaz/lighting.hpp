/**
 * @file      lighting.hpp
 * @brief     Color profile manager
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Uses LP500x driver to control the RGB LEDs with backlight coloring profiles.
 */

#ifndef QAZ_LIGHTING_HPP_
#define QAZ_LIGHTING_HPP_

/**
 * @brief Lighting namespace
 *
 * This namespace holds the LP500x lighting module init and task routines.
 */
namespace lighting {

/// Init lighting by initializing the LP500x driver
void init(void);

/// Runs given lighting profile
void task(void);

}  // namespace lighting

#endif  // QAZ_LIGHTING_HPP_
