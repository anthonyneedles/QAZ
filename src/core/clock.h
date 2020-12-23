/**
 * @file      clock.h
 * @brief     System clock initialization
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Holds any user clock configuration that should be applied before any other user initialization
 * or project execution. Set CLK_SOURCE in the Makefile to select the clock.
 */

#ifndef CORE_CLOCK_H_
#define CORE_CLOCK_H_

/**
 * @brief Init system clock
 *
 * Enable and switch system clock over to desired clock domain depending on the CLK_SOURCE
 * option in the Makefile. Also, set MCO to PA8, so that we can scope the SYSCLK.
 */
void ClockInit(void);

#endif  // CORE_CLOCK_H_
