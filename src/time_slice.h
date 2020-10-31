/**
 * @file      time_slice.h
 * @brief     Implements time slice loop scheduler
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * Core time slice loop scheduler, which will use the SysTick timer to execute a loop at a set
 * LOOP_PERIOD_MS period. It will count these loops to execute given tasks at a specified period.
 * This gives program execution a concept of timing periodicity.
 *
 * If the loop manager detects an overrun of the loop period, it will complain, but will continue
 * the loop as normal.
 *
 * The SysTick timer shall not be used for anything else...
 */

#ifndef __TIME_SLICE_H_
#define __TIME_SLICE_H_

#include "hb.h"
#include "key_matrix.h"
#include "rgb_led.h"

// period at which the loop will execute. try to make as large as possible
#define LOOP_PERIOD_MS (25u)

// table for defining tasks. used in many x-macros. each task definition requires:
//     period_ms - period the task will execute. shall be multiple of LOOP_PERIOD_MS
//     task_func - task function, called at task period
#define TASK_TABLE(TASK) \
    TASK(HB_TASK_PERIOD_MS,         HeartbeatTask) \
    TASK(KEY_MATRIX_TASK_PERIOD_MS, KeyMatrixTask) \
    TASK(RGB_LED_TASK_PERIOD_MS,    RGBLEDTask)

/**
 * TimeSliceInit
 *
 * @brief Init TimeSlice loop
 *
 * Enables SysTick timer via CMSIS SysTick_Config (found in arch/core_cm0.h) with required clock
 * cycles to result in 1ms interrupts.
 */
void TimeSliceInit(void);

/**
 * TimeSliceLoop
 *
 * @brief Enters the infinite TimeSlice loop
 *
 * This is the main execution loop, and should be called after all initialization is finished.
 * Kills program if TimeSliceInit was never called.
 *
 * Calls the internal time slice manager, and increments task counters until their task period is
 * reached, then calls the given task function.
 *
 * Should NEVER return.
 */
void TimeSliceLoop(void);

/**
 * SysTickHandler
 *
 * @brief SysTick IRQ Handler
 *
 * When initalized, the SysTick will generate interrupts at 1kHz. This IRQ handler will then
 * increment the TimeSlice millisecond count every entrance.
 */
void SysTick_Handler(void);

#endif /* __TIME_SLICE_H_ */
