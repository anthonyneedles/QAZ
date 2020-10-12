/**
 * @file      clock.h
 * @brief     System clock initialization
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 * 
 * Holds any user clock configuration that should be applied before any other user initialization
 * or project execution. Set CLK_SOURCE in the Makefile to select the clock.
 */

#ifndef __CLOCK_H
#define __CLOCK_H

/**
 * ClockInit
 *
 * @brief Init system clock
 *
 * Enable and switch system clock over to desired clock domain depending on the CLK_SOURCE
 * option in the Makefile. Also, set MCO to PA8, so that we can scope the SYSCLK.
 */
void ClockInit(void);

#endif /* __CLOCK_H */
