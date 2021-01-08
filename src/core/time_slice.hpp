/**
 * @file      time_slice.hpp
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

/**
 * @brief Timeslice scheduler namespace
 *
 * This namespace holds initialization routines for the timeslice scheduler, which handles calling
 * tasks at a certain period. Tasks must be registered to be ran via the timeslice loop.
 */
namespace timeslice {

// period at which the loop will execute (in milliseconds). try to make as large as possible
inline constexpr unsigned LOOP_PERIOD_MS = 10;

// maximum number of tasks that can be registerd. try to make as small as possible
inline constexpr unsigned MAX_NUM_TASKS  = 4;

// return status values
enum RegStatus {
    SUCCESS,
    FAILURE,
};

/**
 * @brief Init TimeSlice loop
 *
 * Enables SysTick timer via CMSIS SysTick_Config (found in arch/core_cm0.h) with required clock
 * cycles to result in 1ms interrupts.
 */
void init(void);

/**
 * @brief Register task for timeslice loop
 *
 * If a task can be added, the input task function and period is saved in next open task regsitery
 * slot. Tasks will be executed in order in the task registry.
 *
 * A task is not registerd if the maximum number of tasks have already been registered, the task
 * function is invalid, or if the task period is 0, less than the loop period, and/or not a multiple
 * of the loop period.
 *
 * @param[in] period    task period, in millisecond
 * @param[in] task_func task function to be called at task period
 * @return timeslice::SUCCESS if the task has been registered
 *         timeslice::FAILURE if the task has not been registered
 */
RegStatus register_task(unsigned period, void (*task_func)(void));

/**
 * @brief Enter the timeslice loop
 *
 * This should be called ONLY when all initialization has been completed. There should be no return
 * from this fuction.
 *
 * The manager task ensures that each task loop counter is increased every loop period. When the
 * task loop counter reaches the required value to achieve the desired task period, it will execute
 * the task function and start counting again.
 */
void enter_loop(void);

}  // namespace timeslice

#endif  // CORE_TIME_SLICE_HPP_
