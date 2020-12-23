/**
 * @file      macros.h
 * @brief     Holds useful utility macros
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#ifndef UTIL_MACROS_H_
#define UTIL_MACROS_H_

// combining arguments after expansion
#define GLUE(a, b) __GLUE(a, b)
#define __GLUE(a, b) a ## b

// use STATIC_ASSERT outside of functions to force a compiler error if 'exp' is false
// "context_msg" will appear in the compiler message, so fill it with useful information
#define CASSERT(expr, msg) typedef char GLUE (STATIC_ASSERT_, msg) [(expr) ? (+1) : (-1)]
#define STATIC_ASSERT(exp, context, msg) CASSERT(exp, GLUE(GLUE(context, _), msg))

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
#define GPIO_INPUT  0x0U
#define GPIO_OUTPUT 0x1U
#define GPIO_ALTFN  0x2U
#define GPIO_ANALOG 0x3U
#define GPIO_MODE_SET(port, pin, mode) \
    (port)->MODER = (((port)->MODER & ~(0x3UL << ((pin)*2))) | ((mode) << ((pin)*2)))

// GPIO output data setting/clearing
#define GPIO_OUTPUT_SET(port, pin) (port)->ODR |=  (1UL << (pin))
#define GPIO_OUTPUT_CLR(port, pin) (port)->ODR &= ~(1UL << (pin))

// GPIO read input data
#define GPIO_READ_INPUT(port, pin) ((port)->IDR &= (1UL << (pin)))

// GPIO output type settings
#define GPIO_PUSH_PULL  0x0U
#define GPIO_OPEN_DRAIN 0x1U
#define GPIO_OUTPUT_TYPE_SET(port, pin, type) \
    (port)->OTYPER = (((port)->OTYPER & ~(0x1UL << (pin))) | ((type) << (pin)))

// GPIO pull up/down settings
#define GPIO_NO_PULL   0x0U
#define GPIO_PULL_UP   0x1U
#define GPIO_PULL_DOWN 0x2U
#define GPIO_PULL_SET(port, pin, pull) \
    port->PUPDR = (((port)->PUPDR & ~(0x3UL << ((pin)*2))) | ((pull) << ((pin)*2)))

#endif  // UTIL_MACROS_H_
