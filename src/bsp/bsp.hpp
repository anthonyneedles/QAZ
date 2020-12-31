/**
 * @file      bsp.h
 * @brief     Loads correct BSP header for given selection
 *
 * @author    Anthony Needles
 * @date      2020/12/20
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Loads BSP header depending on the $BOARD macro (set in user-definitions section in Makefile)
 */

#ifndef BSP_BSP_HPP_
#define BSP_BSP_HPP_

#if defined(QAZ_65)

#include "bsp/bsp_qaz_65.hpp"

#elif defined(QAZ_TESTBOARD)

#include "bsp/bsp_qaz_testboard.hpp"

#else

#error No valid BSP defined!

#endif

#endif  // BSP_BSP_HPP_
