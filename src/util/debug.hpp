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

inline constexpr bool FORCE_ASSERT = false;

#if defined(DEBUG)

// similar to assert() in standard library. if expr is false, the assert fails, and the
// line/file/expr is printed, and the program stops
#define DBG_ASSERT(expr) \
    if (!expr) { debug::assert_failed((char *)__FILE__, __LINE__, (char *)#expr); }  // NOLINT

/**
 * @brief Enables USART1 for TX at 115200 on pin PA9 (only for DEBUG)
 */
void init(void);

/**
 * @brief Sends formatted string over UART
 *
 * When DEBUG, this function will expand the given format string with the variable args. The
 * expanded string will then be output on the Debug USART TX.
 *
 * Format specifiers:
 * %c - Character
 * %s - String
 * %d - Decimal
 * %o - Octal
 * %x - Hexadecimal
 * %p - Pointer
 *
 * '0n' can be placed in between the '%' and type specifier to specify the minimum width of the
 * result. The output is zero-padded up to 'n' characters. Max width of 8. %p always pads to 8.
 *
 * For example: %08x with an arg of 0x1234 results in 00001234
 *
 * @param[in] fmt Format string, with or without format specifiers
 * @param[in] ... Variable arguments for format speifiers
 */
void printf(const char* format, ...);

/**
 * @brief Sends string over USART
 *
 * Pushes each character in a string over Debug USART.
 *
 * Use when only a non-format string is needed to be sent.
 */
void puts(const char *data);

/**
 * @brief Sends single character over USART
 *
 * Blocks until Debug USART is ready to transmit, then pushes character onto output buffer.
 *
 * Use when only a single non-format character is needed to be sent.
 */
void putchar(char data);

/**
 * @brief Called by DBG_ASSERT() if assertion failed (ONLY IN DEBUG)
 *
 * Print out the context and expression of the failed assertion.
 * We stop here, never to return.
 *
 * @param[in] file expression file name string
 * @param[in] base expression line number
 * @param[in] expr expression string
 */
void assert_failed(char *file, int line, char *expr);

#else

// similar to assert() in standard library. if expr is false, the assert fails.
// in RELEASE, we just stop the program here
#define DBG_ASSERT(expr) \
    if (!expr) { while (1) {} }

// these do nothing when not DEBUG
inline void init(void) { }
inline void printf(const char *, ...) { }
inline void puts(const char *) { }
inline void putchar(char ) { }
inline void assert_failed(char *, int, char *) { }

#endif

}  // namespace debug

#endif  // UTIL_DEBUG_HPP_
