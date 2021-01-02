/**
 * @file      macros.h
 * @brief     Holds useful utility macros
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#ifndef UTIL_MACROS_HPP_
#define UTIL_MACROS_HPP_

// bit operations
#define SET(x, mask) ((x) |=  (mask))
#define CLR(x, mask) ((x) &= ~(mask))
#define BIT_SET(x, bitno) SET(x, 1 << (bitno))
#define BIT_CLR(x, bitno) CLR(x, 1 << (bitno))
#define BIT_READ(x, bitno) (((unsigned)(x) >> (bitno)) & 1)
#define BITMASK_UPDATE(x, mask, val) ((x) = ((x) & ~(mask)) | ((val) & (mask)))

// combining arguments after expansion
#define GLUE(a, b) __GLUE(a, b)
#define __GLUE(a, b) a ## b

// use STATIC_ASSERT outside of functions to force a compiler error if 'exp' is false
// "context_msg" will appear in the compiler message, so fill it with useful information
#define CASSERT(expr, msg) typedef char GLUE (STATIC_ASSERT_, msg) [(expr) ? (+1) : (-1)]
#define CSTATIC_ASSERT(exp, context, msg) CASSERT(exp, GLUE(GLUE(context, _), msg))

// TODO: replace
#define STATIC_ASSERT(exp, context, msg) static_assert(exp, #msg)

// bypassing warnings
#define UNUSED(x) ((void)(x))

// number of elements in an array
#define N_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))

// cycling through indicies, not incrementing/decrementing past the end/beginning
#define NEXT_LINEAR_INDEX(index, indicies) \
    (int)((int)(index) >= (int)(indicies) - 1) ? (int)(indicies) - 1: (int)(index) + 1;
#define PREV_LINEAR_INDEX(index, indicies) \
    (int)((int)(index) <= 0) ? 0 : (int)(index) - 1;

// cycling through indicies, wrapping the beginning/end
#define NEXT_CIRCULAR_INDEX(index, indicies) \
    (int)((int)(index) >= (int)(indicies) - 1) ? 0 : (int)(index) + 1;
#define PREV_CIRCULAR_INDEX(index, indicies) \
    (int)((int)(index) <= 0) ? (int)(indicies) - 1 : (int)(index) - 1;

// for-loop delay. must measure actual delay for "accuracy"
#define LOOP_DELAY(loops) for (volatile int loop_cnt = 0; loop_cnt < loops; ++loop_cnt);

// GPIO AHB clock enable. not too elegant...
#define GPIO_CLOCK_ENABLE(port) RCC->AHBENR |= \
    (port == GPIOA) ? RCC_AHBENR_GPIOAEN :     \
    (port == GPIOB) ? RCC_AHBENR_GPIOBEN :     \
    (port == GPIOC) ? RCC_AHBENR_GPIOCEN :     \
    (port == GPIOF) ? RCC_AHBENR_GPIOFEN : 0

// GPIO mode settings
#define GPIO_INPUT  0x0UL
#define GPIO_OUTPUT 0x1UL
#define GPIO_ALTFN  0x2UL
#define GPIO_ANALOG 0x3UL
#define GPIO_MODE_SET(port, pin, mode) \
    BITMASK_UPDATE((port)->MODER, 0x3UL << (pin)*2, (mode) << (pin)*2)

// GPIO output data setting/clearing
#define GPIO_OUTPUT_SET(port, pin) BIT_SET((port)->ODR, pin)
#define GPIO_OUTPUT_CLR(port, pin) BIT_CLR((port)->ODR, pin)

// GPIO read input data
#define GPIO_READ_INPUT(port, pin) BIT_READ((port)->IDR, pin)

// GPIO output type settings
#define GPIO_PUSH_PULL  0x0UL
#define GPIO_OPEN_DRAIN 0x1UL
#define GPIO_OUTPUT_TYPE_SET(port, pin, type) \
    BITMASK_UPDATE((port)->OTYPER, 0x1UL << (pin), type << (pin))

// GPIO pull up/down settings
#define GPIO_NO_PULL   0x0UL
#define GPIO_PULL_UP   0x1UL
#define GPIO_PULL_DOWN 0x2UL
#define GPIO_PULL_SET(port, pin, pull) \
    BITMASK_UPDATE((port)->PUPDR, 0x3UL << (pin)*2, pull << (pin)*2)

// GPIO alternate function settings. only 0-7 valid for afn. pins 0-7 use AFRL, 8-15 use AFRH
#define GPIO_AF0 0x0UL
#define GPIO_AF1 0x1UL
#define GPIO_AF2 0x2UL
#define GPIO_AF3 0x3UL
#define GPIO_AF4 0x4UL
#define GPIO_AF5 0x5UL
#define GPIO_AF6 0x6UL
#define GPIO_AF7 0x7UL
#define GPIO_AF_SET(port, pin, afn) \
    BITMASK_UPDATE((port)->AFR[(pin) < 8 ? 0 : 1], 0xFUL << ((pin) % 8)*4, afn << ((pin) % 8)*4);

// GPIO output speed settings
#define GPIO_LOW_SPEED  0x0UL
#define GPIO_MED_SPEED  0x1UL
#define GPIO_HIGH_SPEED 0x3UL
#define GPIO_OUT_SPEED_SET(port, pin, speed) \
    BITMASK_UPDATE((port)->OSPEEDR, 0x3UL << (pin)*2, speed << (pin)*2)

#endif  // UTIL_MACROS_HPP_
