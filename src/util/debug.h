/**
 * @file      debug.h
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

#ifndef UTIL_DEBUG_H_
#define UTIL_DEBUG_H_

#if defined(DEBUG)

// similar to assert() in standard library. if expr is false, the assert fails, and the
// line/file/expr is printed, and the program stops
#define DBG_ASSERT(expr) ((expr) ? ((void)0) : DebugAssertFailed(__FILE__, __LINE__, #expr))
#define FORCE_ASSERT (0)

/**
 * @brief Enables USART1 for TX at 115200 on pin PA9 (only for DEBUG)
 */
void DebugInit(void);

/**
 * @brief Sends formatted string over UART
 *
 * When DEBUG, this function will expand the given format string with the variable args. The
 * expanded string will then be output on USART1 TX.
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
void DbgPrintf(const char* format, ...);

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
void DebugAssertFailed(char *file, int line, char *expr);

#else

// these do nothing when not DEBUG
#define DebugInit(x)      ((void)0)
#define DbgPrintf(x, ...) ((void)0)
#define DBG_ASSERT(x)     ((void)0)

#endif

#endif  // UTIL_DEBUG_H_
