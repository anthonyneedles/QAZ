/**
 * @file      time_slice.cpp
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

#include "core/time_slice.hpp"

#include <cstdint>

#include "core/clock.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"
#include "stm32f0xx.h"  // NOLINT

// systick handler needs C linkage
extern "C" void SysTick_Handler(void);

namespace {

// each registered task has an info struct
struct task_info {
    unsigned loop_cnt;
    unsigned loops_per_period;
    void (*task_func)(void);
};

// the current number of milliseconds elapsed
volatile std::uint32_t ms_cnt = 0;

// the millisecond count the last time the manager task ran
std::uint32_t last_ms = 0;

// total tasks registered. can never be > MAX_NUM_TASKS
unsigned ntasks = 0;

// task registry is just an array of task info, filled with each register
task_info task_registry[timeslice::MAX_NUM_TASKS] = { };

}  // namespace

void manager_task(void);

/**
 * @brief Init TimeSlice loop
 *
 * Enables SysTick timer via CMSIS SysTick_Config (found in arch/core_cm0.h) with required clock
 * cycles to result in 1ms interrupts.
 */
void timeslice::init(void)
{
    std::uint32_t st_error = SysTick_Config(clock::SYSCLK_HZ/1000);
    if (st_error != SUCCESS) {
        DBG_ASSERT(FORCE_ASSERT);
    }

    DbgPrintf("Initialized: TimeSlice\r\n");
}

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
timeslice::RegStatus timeslice::register_task(unsigned period, void (*task_func)(void))
{
    if (((period % timeslice::LOOP_PERIOD_MS) != 0) || ((period / timeslice::LOOP_PERIOD_MS) == 0)
            || ((task_func == nullptr) || (ntasks >= timeslice::MAX_NUM_TASKS))) {
        return timeslice::FAILURE;
    }

    // populate next task registry slot
    task_registry[ntasks].loops_per_period = period / timeslice::LOOP_PERIOD_MS;
    task_registry[ntasks].loop_cnt         = 0;
    task_registry[ntasks].task_func        = task_func;

    ntasks++;

    return timeslice::SUCCESS;
}

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
void timeslice::enter_loop(void)
{
    DbgPrintf("Starting timeslice loop...\r\n");

    // any amount of time could have passed since initialization
    last_ms = ms_cnt;

    while (1) {
        manager_task();

        // handle each task counter, and call task function if desired # of loops reached
        for (unsigned i = 0; i < ntasks; ++i) {
            if (task_registry[i].loop_cnt >= task_registry[i].loops_per_period) {
                task_registry[i].loop_cnt = 0;
                task_registry[i].task_func();
            }
            task_registry[i].loop_cnt++;
        }
    }
}

/**
 * @brief Manages timing loops
 *
 * This "task" regulates the timing of the loop to the given loop period. It does this by saving
 * the previous ms count, and comparing it to the current ms count. It will wait out any remaining
 * time until the loop period is achieved.
 *
 * If the calculated elapsed time is greater than the loop period, some task must have overran. The
 * function may be hanging, or the loop period must be increased.
 */
void manager_task(void)
{
    std::uint32_t elapsed_ms;

    // copy value now, it can change at any time
    std::uint32_t current_ms = ms_cnt;

    if (current_ms >= last_ms) {
        // find the time we spent in the loop so far
        elapsed_ms = current_ms - last_ms;
    } else {
        // likely tick overflow
        elapsed_ms = current_ms + (UINT32_MAX - last_ms);
        DbgPrintf("INFO: Likely tick overflow, OK\r\n");
    }

    if (elapsed_ms <= timeslice::LOOP_PERIOD_MS) {
        // wait out the remaining time in the loop period
        while ((ms_cnt - last_ms) < timeslice::LOOP_PERIOD_MS) {}
        current_ms = ms_cnt;
    } else {
        DbgPrintf("WARNING: Loop overran by %ums\r\n", elapsed_ms - timeslice::LOOP_PERIOD_MS);
    }

    last_ms = current_ms;
}

/**
* @brief SysTick IRQ Handler
*
* When initalized, the SysTick will generate interrupts at 1kHz. This IRQ handler will then
* increment the TimeSlice millisecond count every entrance.
*/
void SysTick_Handler(void)
{
    ms_cnt++;
}
