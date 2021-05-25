/**
 * @file      expressions.hpp
 * @brief     Holds useful utility expressions
 *
 * @author    Anthony Needles
 * @date      2021/05/24
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#ifndef UTIL_EXPRESSIONS_HPP_
#define UTIL_EXPRESSIONS_HPP_

#include "util/macros.hpp"

/**
 * @brief Increment index in linear fashion
 *
 * Increment an index value, saturating at maximum value.
 *
 * @param[in] index     the current index
 * @param[in] indicies  total number of indicies
 */
constexpr unsigned NEXT_LINEAR_INDEX(unsigned index, unsigned indicies)
{
    return index >= (indicies - 1) ? indicies - 1 : index + 1;
}

/**
 * @brief Decrement index in linear fashion
 *
 * Decrement an index value, saturating at 0.
 *
 * @param[in] index     the current index
 * @param[in] indicies  total number of indicies
 */
constexpr unsigned PREV_LINEAR_INDEX(unsigned index, unsigned indicies)
{
    UNUSED(indicies);
    return index <= 0 ? 0 : index - 1;
}

/**
 * @brief Increment index in circular fashion
 *
 * Increment an index value, wrapping around to 0.
 *
 * @param[in] index     the current index
 * @param[in] indicies  total number of indicies
 */
constexpr unsigned NEXT_CIRCULAR_INDEX(unsigned index, unsigned indicies)
{
    return index >= (indicies - 1) ? 0 : index + 1;
}

/**
 * @brief Decrement index in circular fashion
 *
 * Decrement an index value, wrapping around to the maximum value.
 *
 * @param[in] index     the current index
 * @param[in] indicies  total number of indicies
 */
constexpr unsigned PREV_CIRCULAR_INDEX(unsigned index, unsigned indicies)
{
    return index <= 0 ? indicies - 1 : index - 1;
}

/**
 * @brief Implement busy-wait loop delay
 *
 * Must measure actual delay for "accuracy"
 *
 * @param[in] loops     the current index
 */
inline void LOOP_DELAY(int loops)
{
    for (volatile int loop_cnt = 0; loop_cnt < loops; ++loop_cnt) { }
}

/**
 * @brief Find number of elements in an array
 *
 * @tparam    N     number of elements in array
 * @tparam    T     type of array members
 */
template <unsigned N, class T>
constexpr unsigned COUNT_OF(T(&)[N])
{
    return N;
}

#endif  // UTIL_EXPRESSIONS_HPP_
