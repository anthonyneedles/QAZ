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

#include <stdbool.h>

#include "util/debug.hpp"
#include "stm32f0xx.h"  // NOLINT

// systick handler needs C linkage
extern "C" void SysTick_Handler(void);

// find number of loops needed to meet a given period
#define CALCULATE_LOOPS(period_ms) (period_ms/LOOP_PERIOD_MS)

// static asserts to ensure task periods are multiples of loop period
#define TASK(period_ms, task_func) \
    static_assert((period_ms / LOOP_PERIOD_MS) != 0, \
        "Time Slice: " #task_func " task period 0 or > LOOP_PERIOD_MS") \
    static_assert((period_ms % LOOP_PERIOD_MS) == 0, \
        "Time Slice: " #task_func " task period not multiple of LOOP_PERIOD_MS") \
    TASK_TABLE(TASK)
#undef TASK

// define loop counter structure, keeping a counter for each task
typedef struct {
#define TASK(period_ms, task_func) \
    uint32_t task_func;
    TASK_TABLE(TASK)
#undef TASK
} task_loop_cnts_t;

// create loop counter structure, init each value so all tasks enter the first time around
static task_loop_cnts_t loop_counts = {
#define TASK(period_ms, task_func) \
    .task_func = CALCULATE_LOOPS(period_ms),
    TASK_TABLE(TASK)
#undef TASK
};

#define CLKCYCLES_PER_MS 48000U

static volatile int current_ms_cnt = 0U;
static bool init_flag = 0U;

void timeSliceManagerTask(void);

/**
 * @brief Init TimeSlice loop
 *
 * Enables SysTick timer via CMSIS SysTick_Config (found in arch/core_cm0.h) with required clock
 * cycles to result in 1ms interrupts.
 */
void TimeSliceInit(void)
{
    uint32_t st_error = SysTick_Config(CLKCYCLES_PER_MS);
    if (st_error == 0U) {
        // 0U = Systick timer successfully loaded
        init_flag = true;
        DbgPrintf("Initialized: TimeSlice\r\n");
    } else {
        // 1U = Reload value impossible
        init_flag = false;
        DbgPrintf("ERROR: SysTick load failed!\r\n");
        DBG_ASSERT(FORCE_ASSERT);
      }
}

/**
 * @brief Init TimeSlice loop
 *
 * Enables SysTick timer via CMSIS SysTick_Config (found in arch/core_cm0.h) with required clock
 * cycles to result in 1ms interrupts.
 */
void TimeSliceLoop(void)
{
    DbgPrintf("Starting timeslice loop...\r\n");

    while (1) {
        timeSliceManagerTask();

        // handle each task counter, and call task function if desired # of loops reached
#define TASK(period_ms, task_func) \
        if (loop_counts.task_func >= CALCULATE_LOOPS(period_ms)) { \
            loop_counts.task_func = 0;                             \
            task_func();                                           \
        }                                                          \
        loop_counts.task_func++;
        TASK_TABLE(TASK)
#undef TASK
    }
}

/**
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
void timeSliceManagerTask(void)
{
    uint32_t elapsed_ticks;
    static uint32_t last_tick = 0;
    static bool is_first_entry = true;

    // copy value now, can change at any time
    uint32_t current_tick = current_ms_cnt;

    if (is_first_entry) {
        // we want to skip the first entry
        is_first_entry = false;
    } else if (!init_flag) {
        // failure in init, we got a problem
        DbgPrintf("ERROR: SysTick can't run, init failure\n\r");
        DBG_ASSERT(FORCE_ASSERT);
    } else {
        if (current_tick >= last_tick) {
            // find the time we spent in the loop so far
            elapsed_ticks = current_tick - last_tick;
        } else {
            // likely tick overflow
            elapsed_ticks = current_tick + (UINT32_MAX - last_tick);
            DbgPrintf("INFO: Likely tick overflow, OK\r\n");
        }

        if (elapsed_ticks <= LOOP_PERIOD_MS) {
            // wait out the remaining time in the loop period
            while ((current_ms_cnt - last_tick) < LOOP_PERIOD_MS) {}
            current_tick = current_ms_cnt;
        } else {
            DbgPrintf("WARNING: Loop overran by %ums\r\n", elapsed_ticks - LOOP_PERIOD_MS);
        }
    }

    last_tick = current_tick;
}

/**
* @brief SysTick IRQ Handler
*
* When initalized, the SysTick will generate interrupts at 1kHz. This IRQ handler will then
* increment the TimeSlice millisecond count every entrance.
*/
void SysTick_Handler(void)
{
    current_ms_cnt++;
}