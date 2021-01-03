/**
 * @file      bitop.hpp
 * @brief     Bit operations API
 *
 * @author    Anthony Needles
 * @date      2021/01/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Instead of explicitly using bit-wise operators (and macros), the bitop class template can
 * be used for performing bit operations on either a specific bit or bitmask.
 */

#ifndef UTIL_BITOP_HPP_
#define UTIL_BITOP_HPP_

#include <cstdint>

// forward declare
template <typename T> class BitOp;

// shorthand for standard integer sizes
using BitOp32  = BitOp<uint32_t>;
using BitOp16  = BitOp<uint16_t>;
using BitOp8   = BitOp<uint8_t>;

// shorthand for volatile standard integer sizes
using BitOpV32 = BitOp<volatile uint32_t>;
using BitOpV16 = BitOp<volatile uint16_t>;
using BitOpV8  = BitOp<volatile uint8_t>;

/**
 * @brief bit operations class template
 *
 * Bit operations can be performed using this template class for specific types.
 *
 * @tparam T type to use for operations
 */
template <typename T>
class BitOp {
 public:
    static void set_bit(T *x, unsigned bitn);
    static void clr_bit(T *x, unsigned bitn);
    static void upd_bit(T *x, unsigned bitn, T val);
    static void set_msk(T *x, T msk);
    static void clr_msk(T *x, T msk);
    static void upd_msk(T *x, T msk, T val);
};

/**
 * @brief Set a specific bit
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     bitn bit posiiton
 */
template <typename T>
inline void BitOp<T>::set_bit(T *x, unsigned bitn)
{
    *x |= (1 << bitn);
}

/**
 * @brief Clear a specific bit
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     bitn bit posiiton
 */
template <typename T>
inline void BitOp<T>::clr_bit(T *x, unsigned bitn)
{
    *x &= ~(1 << bitn);
}

/**
 * @brief Update a specific bit
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     bitn bit posiiton
 * @param[in]     val  value to update bit with
 */
template <typename T>
inline void BitOp<T>::upd_bit(T *x, unsigned bitn, T val)
{
    *x = ((*x & ~(1 << bitn)) | ((val & 1) << bitn));
}

/**
 * @brief Clear a bitmask
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     msk  bitmask
 */
template <typename T>
inline void BitOp<T>::set_msk(T *x, T msk)
{
    *x |= msk;
}

/**
 * @brief Clear a bitmask
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     msk  bitmask
 */
template <typename T>
inline void BitOp<T>::clr_msk(T *x, T msk)
{
    *x &= ~msk;
}

/**
 * @brief Update a bitmask
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     msk  bitmask
 * @param[in]     val  value to update bit with
 */
template <typename T>
inline void BitOp<T>::upd_msk(T *x, T msk, T val)
{
    *x = ((*x & ~msk) | (val & msk));
}

#endif  // UTIL_BITOP_HPP_
