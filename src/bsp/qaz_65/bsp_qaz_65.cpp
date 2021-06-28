/**
 * @file      bsp_qaz_65.cpp
 * @brief     BSP for the QAZ 65% board
 *
 * @author    Anthony Needles
 * @date      2021/06/24
 * @copyright (c) 2021 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * BSP source level declarations.
 */

#include "bsp/bsp.hpp"
#include "bsp/qaz_65/bsp_qaz_65.hpp"

#include "keyboard/key_matrix.hpp"
#include "keyboard/lighting.hpp"
#include "usb/kb_hid.hpp"

/**
 * @brief Board support package initialization
 *
 * Perform module intializations based on what our board actually needs.
 */
void bsp::init(void)
{
    keymatrix::init();
    lighting::init();
    kb_hid::init();
}
