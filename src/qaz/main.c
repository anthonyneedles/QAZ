/**
 * @file      main.c
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

#include "core/clock.h"
#include "core/time_slice.h"
#include "qaz/key_matrix.h"
#include "qaz/rgb_led.h"
#include "usb/usb_hid.h"
#include "util/debug.h"
#include "util/hb.h"

int main(void)
{
    // inits - specifically ordered
    ClockInit();
    DebugInit();
    TimeSliceInit();

    // inits - no required order
    HeartbeatInit();
    KeyMatrixInit();
    RGBLEDInit();
    USBHIDInit();

    // enter the loop - no return
    TimeSliceLoop();

    while (1) {}
}
