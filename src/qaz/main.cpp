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
#include "qaz/persist.hpp"
#include "usb/kb_hid.hpp"
#include "util/debug.hpp"
#include "util/hb.hpp"

int main(void)
{
    // inits - specifically ordered
    clock::init();
    debug::init();
    timeslice::init();
    persist::init();

    // inits - no required order
    heartbeat::init();
    keymatrix::init();
    lighting::init();
    kb_hid::init();

    // enter the loop - no return
    timeslice::enter_loop();

    while (1) {}
}
