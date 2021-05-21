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

/// Combining arguments after expansion
#define GLUE(a, b) __GLUE(a, b)
#define __GLUE(a, b) a ## b

/// (For C) use CSTATIC_ASSERT outside of functions to force a compiler error if 'exp' is false
/// "context_msg" will appear in the compiler message, so fill it with useful information
#define CASSERT(expr, msg) typedef char GLUE (STATIC_ASSERT_, msg) [(expr) ? (+1) : (-1)]
#define CSTATIC_ASSERT(exp, context, msg) CASSERT(exp, GLUE(GLUE(context, _), msg))

/// Bypassing warnings
#define UNUSED(x) do { (void)(x); } while (0)

template <typename T>
constexpr T DIVIDE_ROUND(T dividend, T divisor)
{
    return (dividend + divisor - 1) / divisor;
}

#endif  // UTIL_MACROS_HPP_
