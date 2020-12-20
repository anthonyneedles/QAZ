/**
 * @file    bsp.h
 * @author  Anthony Needles
 * @date    2020/12/20
 * @brief   Loads correct BSP header for given selection
 *
 * Loads BSP header depending on the $BSP macro (set in user-definitions section in Makefile)
 */

#ifndef __BSP_BSP_H_
#define __BSP_BSP_H_

#if defined(BSP_QAZ_65)

#include "bsp/bsp_qaz_65.h"

#elif defined(BSP_TESTBOARD)

#include "bsp/bsp_testboard.h"

#else

#error No valid BSP defined!

#endif

#endif /* __BSP_BSP_H_ */
