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
 * @param[in] loops  the current index
 */
inline void LOOP_DELAY(int loops)
{
    for (volatile int loop_cnt = 0; loop_cnt < loops; ++loop_cnt) { }
}

/**
 * @brief Find number of elements in an array
 *
 * @tparam N  number of elements in array
 * @tparam T  type of array members
 */
template <unsigned N, class T>
constexpr unsigned COUNT_OF(T(&)[N])
{
    return N;
}

/**
 * @brief 8-bit RGB values to 24-bit color code
 *
 * @param[in] red    8-bit intensity of red   in color
 * @param[in] green  8-bit intensity of green in color
 * @param[in] blue   8-bit intensity of blue  in color
 *
 * @return RGB code, in lower 24 bits of word
 */
constexpr uint32_t RGB_CODE(uint8_t red, uint8_t green, uint8_t blue)
{
    return (static_cast<uint32_t>((red   << 16) & 0xFF0000) |
            static_cast<uint32_t>((green <<  8) & 0x00FF00) |
            static_cast<uint32_t>((blue)        & 0x0000FF));
}

/**
 * @brief Red intensity from 24-bit color code
 *
 * @param[in] rgb_code  RGB code, in lower 24 bits
 *
 * @return 8-bit red intensity
 */
constexpr uint8_t R_RGB(uint32_t rgb_code) {
    return (rgb_code & 0xFF0000) >> 16;
}

/**
 * @brief Green intensity from 24-bit color code
 *
 * @param[in] rgb_code  RGB code, in lower 24 bits
 *
 * @return 8-bit green intensity
 */
constexpr uint8_t G_RGB(uint32_t rgb_code) {
    return (rgb_code & 0x00FF00) >> 8;
}

/**
 * @brief Blue intensity from 24-bit color code
 *
 * @param[in] rgb_code  RGB code, in lower 24 bits
 *
 * @return 8-bit blue intensity
 */
constexpr uint8_t B_RGB(uint32_t rgb_code) {
    return (rgb_code & 0x0000FF);
}

#endif  // UTIL_EXPRESSIONS_HPP_
