/**
 * @file      bitop.hpp
 * @brief     Bit operations API
 *
 * @author    Anthony Needles
 * @date      2021/01/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Instead of explicitly using bit-wise operators (and macros) this module can be used for
 * performing bit operations on either a specific bit or bitmask.
 */

#ifndef UTIL_BITOP_HPP_
#define UTIL_BITOP_HPP_

/**
 * @brief Bit operations namespace
 *
 * This namespace holds methods for performing bitwise operations. These can be done using a bit
 * position or a bitmask.
 */
namespace bitop {

/**
 * @brief Set a specific bit
 *
 * @tparam        T     type to use for operations
 * @param[in,out] x     reference of value to perform bitop on
 * @param[in]     bitn  bit posiiton
 */
template <typename T>
inline void set_bit(T &x, unsigned bitn)
{
    x |= (1u << bitn);
}

/**
 * @brief Clear a specific bit
 *
 * @tparam        T     type to use for operations
 * @param[in,out] x     reference of value to perform bitop on
 * @param[in]     bitn  bit posiiton
 */
template <typename T>
inline void clr_bit(T &x, unsigned bitn)
{
    x &= ~(1u << bitn);
}

/**
 * @brief Update a specific bit
 *
 * @tparam        T     type to use for operations
 * @param[in,out] x     reference of value to perform bitop on
 * @param[in]     bitn  bit posiiton
 * @param[in]     val   value to update bit with
 */
template <typename T>
inline void update_bit(T &x, unsigned bitn, unsigned val)
{
    x = ((x & ~(1u << bitn)) | ((val & 1u) << bitn));
}

/**
 * @brief Read a specific bit
 *
 * @tparam        T     type to use for operations
 * @param[in,out] x     reference of value to perform bitop on
 * @param[in]     bitn  bit posiiton
 *
 * @return T sized field with read bit at LSB
 */
template <typename T>
inline T read_bit(const T &x, unsigned bitn)
{
    return (x >> bitn) & 1u;
}

/**
 * @brief Clear a bitmask
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     msk  bitmask
 */
template <typename T>
inline void set_msk(T &x, unsigned msk)
{
    x |= msk;
}

/**
 * @brief Clear a bitmask
 *
 * @tparam        T    type to use for operations
 * @param[in,out] x    reference of value to perform bitop on
 * @param[in]     msk  bitmask
 */
template <typename T>
inline void clr_msk(T &x, unsigned msk)
{
    x &= ~msk;
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
inline void update_msk(T &x, unsigned msk, unsigned val)
{
    x = ((x & ~msk) | (val & msk));
}

}  // namespace bitop

#endif  // UTIL_BITOP_HPP_
