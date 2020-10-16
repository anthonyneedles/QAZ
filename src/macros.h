/**
 * @file      macros.h
 * @brief     Holds useful utility macros 
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 */

#ifndef __STATIC_ASSERT_H_
#define __STATIC_ASSERT_H_

// combining arguments after expansion
#define GLUE(a,b) __GLUE(a,b)
#define __GLUE(a,b) a ## b

// use STATIC_ASSERT outside of functions to force a compiler error if 'exp' is false
// "context_msg" will appear in the compiler message, so fill it with useful information
#define CASSERT(expr, msg) typedef char GLUE (STATIC_ASSERT_, msg) [(expr) ? (+1) : (-1)]
#define STATIC_ASSERT(exp, context, msg) CASSERT(exp, GLUE(GLUE(context, _), msg))

// bypassing warnings
#define UNUSED(x) ((void)(x))

// number of elements in an array
#define N_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))

#endif /* __STATIC_ASSERT_H_ */
