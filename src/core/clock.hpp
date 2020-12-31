/**
 * @file      clock.h
 * @brief     System clock initialization
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Holds any user clock configuration that should be applied before any other user initialization
 * or project execution.
 */

#ifndef CORE_CLOCK_HPP_
#define CORE_CLOCK_HPP_

/**
 * @brief Init system clock
 *
 * Enable and switch system clock over to using HSE and PLL to result in 48MHz SYSCLK.
 * Also, set MCO to PA8, so that we can scope the SYSCLK. Assumes 8MHz external crystal.
 */
void ClockInit(void);

#endif  // CORE_CLOCK_HPP_
