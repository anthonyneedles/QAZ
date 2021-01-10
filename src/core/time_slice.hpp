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

/// Period at which the loop will execute (in milliseconds). try to make as large as possible
inline constexpr unsigned LOOP_PERIOD_MS = 10;

/// Maximum number of tasks that can be registerd. try to make as small as possible
inline constexpr unsigned MAX_NUM_TASKS  = 4;

/// Return status values
enum RegStatus {
    SUCCESS,
    FAILURE,
};

/// Init SysTick timer for counting milliseconds for the TimeSlice scheduler
void init(void);

/// Register a task with the scheduler (must not be at maximum # of tasks, see `MAX_NUM_TASKS`)
RegStatus register_task(unsigned period, void (*task_func)(void));

/// Enter timeslice loop and start scheduler. Never returns...
void enter_loop(void);

}  // namespace timeslice

#endif  // CORE_TIME_SLICE_HPP_
