/**
 * @file      debug.c
 * @brief     Debug functionality. Only used when BUILD_TYPE = DEBUG
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * Holds any debug functionality that will effectively "not do anything" if BUILD_TYPE is not set
 * to DEBUG, in order to remove code size and processor time dedicated to debug.
 */

#include "util/debug.h"

#include <stdarg.h>

#include "bsp/bsp.h"
#include "comms/uart.h"
#include "util/macros.h"

#if defined(DEBUG)

// checks for '0n' (for n = 0, 1, ..., 8) after a '%', signaling width specifier
#define IS_WIDTH_SPECIFIER(x,y) ((x == '0') && (y >= '0' && y <= '8'))

// maximum amount of characters a number can be expanded to ("45" = 2, "12345" = 5, etc.)
#define MAX_EXPAND_CHARACTERS (50)

// our handle to the uart we use to send debug messages
static uart_handle_t uart_handle = {
    .regs  = DEBUG_UART,
    .state = UART_RESET,
};

static void debugPutChar(char data);
static void debugPutString(const char *data);
static char *debugExpandNum(unsigned num, int base, int width);

/**
 * DebugInit
 *
 * @brief Enables USART1 for TX at 115200 on pin PA9 (only for DEBUG)
 */
void DebugInit(void)
{
    UARTInit(&uart_handle);

    DbgPrintf("\r\n=== QAZ ===\r\n");
    DbgPrintf("Initialized: Debug\r\n");
}

/**
 * DbgPrint
 *
 * @brief Sends formatted string over USART1
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
void DbgPrintf(const char *fmt_ptr, ...)
{
    DBG_ASSERT(fmt_ptr);

    int      sint_arg;
    unsigned uint_arg;
    char    *str_arg;
    int      width;

    va_list arg;
    va_start(arg, fmt_ptr);

    for (; *fmt_ptr != '\0'; ++fmt_ptr) {
        if ( *fmt_ptr == '%' ) {
            // handle format specifiers
            fmt_ptr++;
            width = 0;

            // if there is a '0n', we now have a specified width
            if (IS_WIDTH_SPECIFIER(*fmt_ptr, *(fmt_ptr + 1))) {
                width = *(fmt_ptr + 1) - '0';
                fmt_ptr += 2;
            }

            switch (*fmt_ptr) {
            case 'c' :
                // character specifier (char promoted to int)
                sint_arg = va_arg(arg, int);
                debugPutChar(sint_arg);
                break;

            case 's':
                // string specifier
                str_arg = va_arg(arg, char *);
                debugPutString(str_arg);
                break;

            case 'd' :
                // signed decimal specifier
                sint_arg = va_arg(arg, int);
                if (sint_arg < 0) {
                    sint_arg = -sint_arg;
                    debugPutChar('-');
                }
                debugPutString(debugExpandNum((unsigned)sint_arg, 10, width));
                break;

            case 'u' :
                // unsigned decimal specifier
                uint_arg = va_arg(arg, unsigned);
                debugPutString(debugExpandNum(uint_arg, 10, width));
                break;

            case 'o':
                // octal specifier
                uint_arg = va_arg(arg, unsigned int);
                debugPutString(debugExpandNum(uint_arg, 8, width));
                break;

            case 'x':
                // hexadecimal specifier
                uint_arg = va_arg(arg, unsigned int);
                debugPutString(debugExpandNum(uint_arg, 16, width));
                break;

            case 'p':
                // p specifier (width always 8)
                uint_arg = va_arg(arg, unsigned int);
                debugPutString(debugExpandNum(uint_arg, 16, 8));
                break;

            default:
                debugPutChar(*fmt_ptr);
                break;
            }
        } else {
            // print and 'normal' character
            debugPutChar(*fmt_ptr);
        }
    }

    va_end(arg);
}

/**
 * DebugAssertFailed
 *
 * @brief Called by DBG_ASSERT() if assertion failed (ONLY IN DEBUG)
 *
 * Print out the context and expression of the failed assertion.
 * We stop here, never to return.
 *
 * @param[in] file expression file name string
 * @param[in] base expression line number
 * @param[in] expr expression string
 */
void DebugAssertFailed(char *file, int line, char *expr) 
{
    DbgPrintf("\r\nERROR: ASSERTION FAILED!\r\n");
    DbgPrintf("EXPR: %s\r\n", expr);
    DbgPrintf("LINE: %d\r\n", line);
    DbgPrintf("FILE: %s\r\n", file);
    while (1) {}
}

/**
 * debugPutChar
 *
 * @brief Sends single character over USART1
 *
 * Blocks until USART1 is ready to transmit, then pushes character onto output buffer.
 */
static void debugPutChar(char data)
{
    UARTWriteBlocking(&uart_handle, &data, 1);
}

/**
 * debugPutString
 *
 * @brief Sends string over USART1
 *
 * Pushes each character in a string over USART1.
 */
static void debugPutString(const char *data)
{
    DBG_ASSERT(data);

    for (int i = 0; data[i] != '\0'; ++i) {
        debugPutChar(data[i]);
    }
}

/**
 * debugExpandNum
 *
 * @brief Expand a number into string representation
 *
 * Takes the absolute value of the number to expand (if negative, the '-' prints before this) and
 * fills a buffer with the string reperesentation of that number, in the given base .
 *
 * It does this starting at the end of the output buffer (placing a '\0' to terminate the string),
 * then working towards the start (going from least significant digit to most significant digit).
 *
 * After all digits are populated, a pointer to the start of this string in the buffer is
 * returned (again, null terminated).
 *
 * If a nonzero width is given, the output string will be atleast that size, padded with '0's.
 *
 * @param[in] num   absolute value of number to expand
 * @param[in] base  what base the number is to be represented in
 * @param[in] width the '0'-padded width of the output
 *
 * @return pointer to expanded string
 */
static char *debugExpandNum(unsigned num, int base, int width)
{
  // number-to-character array
	static const char num_chars[]= "0123456789ABCDEF";

  // output buffer, +1 for the null. a pointer to somewhere in this buffer is returned
	static char buffer[MAX_EXPAND_CHARACTERS + 1];

  // pointer to where we are in buffer. start at the end and work towards the start
	char *expand_ptr =  &buffer[MAX_EXPAND_CHARACTERS];

  // the return char array will be interpreted as a string, so put a null at the end
	*expand_ptr = '\0';

  // convert input num to character, starting with least significant digit
	do {
    expand_ptr--;
		*expand_ptr = num_chars[num%base];
		num /= base;
    width--;
	} while ((num != 0) && (expand_ptr != buffer));

  // fill with zeros if we haven't hit the desired width yet
  while ((width > 0) && (expand_ptr != buffer)) {
    expand_ptr--;
    *expand_ptr = '0';
    width--;
  }

  // return the start of the chunk of the null-terminated buffer we filled with our expansion
	return expand_ptr;
}

#endif
