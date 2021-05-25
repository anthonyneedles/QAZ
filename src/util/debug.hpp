/**
 * @file      debug.hpp
 * @brief     Debug functionality. Only used when BUILD_TYPE = DEBUG
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Holds any debug functionality that will effectively "not do anything" if BUILD_TYPE is not set
 * to DEBUG (in top level Makefile), in order to remove code size and processor time dedicated to
 * debug.
 */

#ifndef UTIL_DEBUG_HPP_
#define UTIL_DEBUG_HPP_

/**
 * @brief Debug namespace
 *
 * The debug namespace will hold functions relevant to debug, such as printing to the debug output
 * (only if BUILD_TYPE = DEBUG). If BUILD_TYPE = RELEASE, most things here are no-ops.
 */
namespace debug {

/// Will force an assert when given to DBG_ASSERT
constexpr bool FORCE_ASSERT = false;

#if defined(RELEASE)

/// Similar to assert() in standard library. If expr is false, the assert fails.
/// In RELEASE, we just stop the program here
#define DBG_ASSERT(expr) \
    if (!expr) { while (1) {} }

// these do nothing when not DEBUG
inline void init(void) { }
inline void printf(const char *, ...) { }
inline void puts(const char *) { }
inline void putchar(char ) { }
inline void assert_failed(char *, int, char *) { }

#elif defined(DEBUG)

/// Similar to assert() in standard library. If expr is false, the assert fails, and the
/// line/file/expr is printed, and the program stops
#define DBG_ASSERT(expr) \
    if (!expr) { debug::assert_failed((char *)__FILE__, __LINE__, (char *)#expr); }  // NOLINT

/// Init debug printing by instantiating UART driver object
void init(void);

/// Print a format string
void printf(const char *fs, ...);

/// Print a non-format string
void puts(const char *s);

/// Print a single character
void putchar(char c);

/// Only to be called when an assert fails (`DBG_ASSERT`), prints assert info and infinitely loops
void assert_failed(char *file, int line, char *expr);

#else

#error "No valid BUILD_TYPE value given"

#endif

}  // namespace debug

#endif  // UTIL_DEBUG_HPP_
