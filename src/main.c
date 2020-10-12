/**
 * @file      main.c
 * @brief     QAZ init and loop entry
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * The QAZ Keyboard project.
 *
 * https://github.com/anthonyneedles/QAZ
 */

#include "time_slice.h"
#include "clock.h"
#include "hb.h"

int main(void)
{
    // inits - specifically ordered
    ClockInit();
    TimeSliceInit();

    // inits - no required order
    HeartbeatInit();

    // enter the loop - no return
    TimeSliceLoop();
    
    while(1) {}
}
