/**
 * @file      macros.hpp
 * @brief     Holds useful utility macros
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#ifndef UTIL_MACROS_HPP_
#define UTIL_MACROS_HPP_

// combining arguments after expansion
#define GLUE(a, b) __GLUE(a, b)
#define __GLUE(a, b) a ## b

// (for C) use CSTATIC_ASSERT outside of functions to force a compiler error if 'exp' is false
// "context_msg" will appear in the compiler message, so fill it with useful information
#define CASSERT(expr, msg) typedef char GLUE (STATIC_ASSERT_, msg) [(expr) ? (+1) : (-1)]
#define CSTATIC_ASSERT(exp, context, msg) CASSERT(exp, GLUE(GLUE(context, _), msg))

// bypassing warnings
#define UNUSED(x) ((void)(x))

// number of elements in an array
#define N_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))

// cycling through indicies, not incrementing/decrementing past the end/beginning
#define NEXT_LINEAR_INDEX(index, indicies) \
    ((index) >= (indicies) - 1) ? (indicies) - 1: (index) + 1;
#define PREV_LINEAR_INDEX(index, indicies) \
    ((index) <= 0) ? 0 : (index) - 1;

// cycling through indicies, wrapping the beginning/end
#define NEXT_CIRCULAR_INDEX(index, indicies) \
    ((index) >= (indicies) - 1) ? 0 : (index) + 1;
#define PREV_CIRCULAR_INDEX(index, indicies) \
    ((index) <= 0) ? (indicies) - 1 : (index) - 1;

// for-loop delay. must measure actual delay for "accuracy"
#define LOOP_DELAY(loops) for (volatile int loop_cnt = 0; loop_cnt < loops; ++loop_cnt);

#endif  // UTIL_MACROS_HPP_
