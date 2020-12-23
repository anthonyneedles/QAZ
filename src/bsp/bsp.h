/**
 * @file      bsp.h
 * @brief     Loads correct BSP header for given selection
 * 
 * @author    Anthony Needles
 * @date      2020/12/20
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Loads BSP header depending on the $BSP macro (set in user-definitions section in Makefile)
 */

#ifndef __BSP_BSP_H_
#define __BSP_BSP_H_

#if defined(QAZ_65)

#include "bsp/bsp_qaz_65.h"

#elif defined(QAZ_TESTBOARD)

#include "bsp/bsp_testboard.h"

#else

#error No valid BSP defined!

#endif

#endif /* __BSP_BSP_H_ */
