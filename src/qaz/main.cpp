/**
 * @file      main.cpp
 * @brief     QAZ init and loop entry
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * The QAZ Keyboard project.
 *
 * https://github.com/anthonyneedles/QAZ
 */

#include "core/clock.hpp"
#include "core/time_slice.hpp"
#include "qaz/key_matrix.hpp"
#include "qaz/lighting.hpp"
#include "usb/usb_hid.hpp"
#include "util/debug.hpp"
#include "util/hb.hpp"

int main(void)
{
    // inits - specifically ordered
    ClockInit();
    DebugInit();
    TimeSliceInit();

    // inits - no required order
    HeartbeatInit();
    KeyMatrixInit();
    LightingInit();
    // USBHIDInit();

    // enter the loop - no return
    TimeSliceLoop();

    while (1) {}
}
