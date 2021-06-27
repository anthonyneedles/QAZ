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
#include "bsp/qaz_media/bsp_qaz_media.hpp"

#include "qaz/buttons.hpp"
#include "qaz/rotary_encoder.hpp"
#include "usb/consumer_hid.hpp"

/**
 * @brief Board support package initialization
 *
 * Perform module intializations based on what our board actually needs.
 */
void bsp::init(void)
{
    buttons::init();
    rotary_encoder::init();
    consumer_hid::init();
}
