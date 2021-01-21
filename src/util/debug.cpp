/**
 * @file      debug.cpp
 * @brief     Debug functionality. Only used when BUILD_TYPE = DEBUG
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Holds any debug functionality that will effectively "not do anything" if BUILD_TYPE is not set
 * to DEBUG, in order to remove code size and processor time dedicated to debug.
 */

#include "util/debug.hpp"

#include <stdarg.h>

#include "bsp/bsp.hpp"
#include "comm/uart.hpp"
#include "util/macros.hpp"
#include "version.hpp"

#if defined(DEBUG)

namespace {

/// Maximum amount of characters a number can be expanded to ("45" = 2, "12345" = 5, etc.)
constexpr unsigned MAX_EXPAND_CHARACTERS = 50;

/// Checks for '0n' (for n = 0, 1, ..., 8) after a '%', signaling width specifier
constexpr bool IS_WIDTH_SPECIFIER(char x, char y) { return ((x == '0') && (y >= '0' && y <= '8')); }

/// Debug uart class object
UART dbg_uart(DEBUG_UART);

}  // namespace

static char *expand_num(unsigned num, int base, int width);

/**
 * @brief Enables USART1 for TX at 115200 on pin PA9 (only for DEBUG)
 */
void debug::init(void)
{
    // Set debug tx port into alt function 1 mode, pullup, and high speed output
    gpio::enable_port_clock(bsp::DBG_TX);
    gpio::set_mode(bsp::DBG_TX, gpio::ALTFN);
    gpio::set_altfn(bsp::DBG_TX, gpio::ALTFN_1);
    gpio::set_pull(bsp::DBG_TX, gpio::PULL_UP);
    gpio::set_output_speed(bsp::DBG_TX, gpio::HIGH_SPEED);

    dbg_uart.init();

    // print project information
    debug::puts("\r\n===== QAZ =====\r\n");
    debug::printf("Board: %s\r\n", version::BOARD);
    debug::printf("Hash:  %s (%s)\r\n\r\n", version::GIT_HASH, version::GIT_STATE);

    debug::puts("Initialized: Debug\r\n");
}

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
 * @param[in] fs   Format string, with or without format specifiers
 * @param[in] ...  Variable arguments for format speifiers
 */
void debug::printf(const char *fs, ...)
{
    DBG_ASSERT(fs);

    int      sint_arg;
    unsigned uint_arg;
    char    *str_arg;
    int      width;

    va_list arg;
    va_start(arg, fs);

    for (; *fs != '\0'; ++fs) {
        if ( *fs == '%' ) {
            // handle format specifiers
            fs++;
            width = 0;

            // if there is a '0n', we now have a specified width
            if (IS_WIDTH_SPECIFIER(*fs, *(fs + 1))) {
                width = *(fs + 1) - '0';
                fs += 2;
            }

            switch (*fs) {
            case 'c' :
                // character specifier (char promoted to int)
                sint_arg = va_arg(arg, int);
                putchar(sint_arg);
                break;

            case 's':
                // string specifier
                str_arg = va_arg(arg, char *);
                puts(str_arg);
                break;

            case 'd' :
                // signed decimal specifier
                sint_arg = va_arg(arg, int);
                if (sint_arg < 0) {
                    sint_arg = -sint_arg;
                    putchar('-');
                }
                puts(expand_num((unsigned)sint_arg, 10, width));
                break;

            case 'u' :
                // unsigned decimal specifier
                uint_arg = va_arg(arg, unsigned);
                puts(expand_num(uint_arg, 10, width));
                break;

            case 'o':
                // octal specifier
                uint_arg = va_arg(arg, unsigned int);
                puts(expand_num(uint_arg, 8, width));
                break;

            case 'x':
                // hexadecimal specifier
                uint_arg = va_arg(arg, unsigned int);
                puts(expand_num(uint_arg, 16, width));
                break;

            case 'p':
                // p specifier (width always 8)
                uint_arg = va_arg(arg, unsigned int);
                puts(expand_num(uint_arg, 16, 8));
                break;

            default:
                putchar(*fs);
                break;
            }
        } else {
            // print and 'normal' character
            putchar(*fs);
        }
    }

    va_end(arg);
}

/**
 * @brief Sends string over USART
 *
 * Pushes each character in a string over Debug USART.
 *
 * Use when only a non-format string is needed to be sent.
 *
 * @param[in] s  string to print
 */
void debug::puts(const char *s)
{
    DBG_ASSERT(s);

    for (int i = 0; s[i] != '\0'; ++i) {
        putchar(s[i]);
    }
}

/**
 * @brief Sends single character over USART
 *
 * Blocks until Debug USART is ready to transmit, then pushes character onto output buffer.
 *
 * Use when only a single non-format character is needed to be sent.
 *
 * @param[in] c  character to print
 */
void debug::putchar(char c)
{
    dbg_uart.write_blocking(reinterpret_cast<uint8_t *>(&c), 1);
}

/**
 * @brief Called by DBG_ASSERT() if assertion failed (ONLY IN DEBUG)
 *
 * Print out the context and expression of the failed assertion.
 * We stop here, never to return.
 *
 * @param[in] file  expression file name string
 * @param[in] base  expression line number
 * @param[in] expr  expression string
 */
void debug::assert_failed(char *file, int line, char *expr)
{
    debug::puts("\r\nERROR: ASSERTION FAILED!\r\n");
    debug::printf("EXPR: %s\r\n", expr);
    debug::printf("LINE: %d\r\n", line);
    debug::printf("FILE: %s\r\n", file);
    while (1) {}
}

/**
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
 * @param[in] num    absolute value of number to expand
 * @param[in] base   what base the number is to be represented in
 * @param[in] width  the '0'-padded width of the output
 *
 * @return pointer to expanded string
 */
static char *expand_num(unsigned num, int base, int width)
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
