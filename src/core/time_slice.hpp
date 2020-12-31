/**
 * @file      time_slice.h
 * @brief     Implements time slice loop scheduler
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
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

#ifndef CORE_TIME_SLICE_HPP_
#define CORE_TIME_SLICE_HPP_

#include "qaz/key_matrix.hpp"
#include "qaz/lighting.hpp"
#include "usb/usb_hid.hpp"
#include "util/hb.hpp"

// period at which the loop will execute. try to make as large as possible
#define LOOP_PERIOD_MS (10U)

// table for defining tasks. used in many x-macros. each task definition requires:
//     period_ms - period the task will execute. shall be multiple of LOOP_PERIOD_MS
//     task_func - task function, called at task period
#define TASK_TABLE(TASK) \
    TASK(HB_TASK_PERIOD_MS,         HeartbeatTask) \
    TASK(KEY_MATRIX_TASK_PERIOD_MS, KeyMatrixTask) \
    TASK(LIGHTING_TASK_PERIOD_MS,   LightingTask)  \

/**
 * @brief Init TimeSlice loop
 *
 * Enables SysTick timer via CMSIS SysTick_Config (found in arch/core_cm0.h) with required clock
 * cycles to result in 1ms interrupts.
 */
void TimeSliceInit(void);

/**
 * @brief Init TimeSlice loop
 *
 * Enables SysTick timer via CMSIS SysTick_Config (found in arch/core_cm0.h) with required clock
 * cycles to result in 1ms interrupts.
 */
void TimeSliceLoop(void);

#endif  // CORE_TIME_SLICE_HPP_
