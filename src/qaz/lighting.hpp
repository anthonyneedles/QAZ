/**
 * @file      lighting.h
 * @brief     Color profile manager
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Uses LP500x driver to control the RGB LEDs with backlight coloring profiles.
 */

#ifndef QAZ_LIGHTING_HPP_
#define QAZ_LIGHTING_HPP_

#define LIGHTING_TASK_PERIOD_MS (10U)

/**
 * @brief Initializes lighting profile
 *
 * Initializes the LP500x driver for control of the RGB LEDs.
 */
void LightingInit(void);

/**
 * @brief Task for updating RGB LEDs.
 *
 * Runs chosen lighting profile, unless at lowest brightness, where it will just turn off LEDs.
 */
void LightingTask(void);

/**
 * @brief BRTUP key callback
 *
 * Increases brightness setting up. Saturates at max.
 */
void KeyMatrixCallback_BRTUP(void);

/**
 * @brief BRTDN key callback
 *
 * Increases brightness setting down. Saturates at min.
 */
void KeyMatrixCallback_BRTDN(void);

/**
 * @brief COLOR key callback
 *
 * Cycles through colors
 */
void KeyMatrixCallback_COLOR(void);

/**
 * @brief PROF key callback
 *
 * Cycles through coloring profiles
 */
void KeyMatrixCallback_PROF(void);

#endif  // QAZ_LIGHTING_HPP_
