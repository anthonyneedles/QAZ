/**
 * @file      consumer_hid.hpp
 * @brief     USB HID Consumer device
 *
 * @author    Anthony Needles
 * @date      2021/06/27
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module will use the USB driver to send consumer reports to the USB host.
 */

#include "usb/consumer_hid.hpp"

#include <cstdint>

#include "bsp/bsp.hpp"
#include "core/time_slice.hpp"
#include "media/buttons.hpp"
#include "usb/usb.hpp"
#include "usb/usb_definitions.hpp"
#include "usb/consumer_usb_desc.hpp"
#include "util/debug.hpp"
#include "stm32f0xx.h" // NOLINT

namespace {

/// Task fuction will execute every 10ms
constexpr unsigned USB_HID_TASK_PERIOD_MS = 10;

/// USB HID transactions occur on EP1, which is configure as an Interrupt EP
constexpr unsigned INTERRUPT_EPN = 1;

// Bits in the report halfword
constexpr uint16_t REPORT_NEXT_MSK       = 0x0001;
constexpr uint16_t REPORT_PREVIOUS_MSK   = 0x0002;
constexpr uint16_t REPORT_STOP_MSK       = 0x0004;
constexpr uint16_t REPORT_PLAY_PAUSE_MSK = 0x0008;
constexpr uint16_t REPORT_MUTE_MSK       = 0x0010;
constexpr uint16_t REPORT_VOL_UP_MSK     = 0x0020;
constexpr uint16_t REPORT_VOL_DOWN_MSK   = 0x0040;

uint16_t report = 0x0000;

/**
 * @brief Handle a validated STOP button press.
 *
 * We just want to set the STOP button bit of the report halfword.
 */
void handle_stop(void)
{
    report |= REPORT_STOP_MSK;
}

/**
 * @brief Handle a validated PREVIOUS button press.
 *
 * We just want to set the PREVIOUS button bit of the report halfword.
 */
void handle_previous(void)
{
    report |= REPORT_PREVIOUS_MSK;
}

/**
 * @brief Handle a validated PLAY/PAUSE button press.
 *
 * We just want to set the PLAY/PAUSE button bit of the report halfword.
 */
void handle_play_pause(void)
{
    report |= REPORT_PLAY_PAUSE_MSK;
}

/**
 * @brief Handle a validated NEXT button press.
 *
 * We just want to set the NEXT button bit of the report halfword.
 */
void handle_next(void)
{
    report |= REPORT_NEXT_MSK;
}

/**
 * @brief Handle a validated MUTE button press.
 *
 * We want to set the MUTE button bit of the report halfword. Also set the MUTE LED.
 */
void handle_mute(void)
{
    report |= REPORT_MUTE_MSK;
    gpio::toggle_output(bsp::MUTE_LED);
}

}  // namespace

/**
 * @brief Initialize the USB Consumer HID driver
 *
 * The USB low level driver needs to be initialized for use, and we set our callback functions for
 * all of the button presses.
 */
void consumer_hid::init(void)
{
    usb::init();

    auto stat1 = buttons::set_callback(bsp::STOP, handle_stop);
    DBG_ASSERT(stat1 == buttons::SUCCESS);

    stat1 = buttons::set_callback(bsp::PREVIOUS, handle_previous);
    DBG_ASSERT(stat1 == buttons::SUCCESS);

    stat1 = buttons::set_callback(bsp::PLAY_PAUSE, handle_play_pause);
    DBG_ASSERT(stat1 == buttons::SUCCESS);

    stat1 = buttons::set_callback(bsp::NEXT, handle_next);
    DBG_ASSERT(stat1 == buttons::SUCCESS);

    stat1 = buttons::set_callback(bsp::MUTE, handle_mute);
    DBG_ASSERT(stat1 == buttons::SUCCESS);

     // enable MUTE LED GPIO port clock, set as output
    gpio::enable_port_clock(bsp::MUTE_LED);
    gpio::set_mode(bsp::MUTE_LED, gpio::OUTPUT);

    auto stat2 = timeslice::register_task(USB_HID_TASK_PERIOD_MS, consumer_hid::task);
    DBG_ASSERT(stat2 == timeslice::SUCCESS);

    debug::puts("Initialized: USB Consumer HID\r\n");
}

/**
 * @brief Send off report descriptor
 *
 * If the new report is different than the last one, we need to send it. All usages in the report
 * are OSC (one-shot control). We need to send a report when a new usage is set, then (ASAP) send
 * a report with the usage cleared in order to signal a single event of that usage.
 */
void consumer_hid::task(void)
{
    static uint16_t last_report = 0;
    if (report != last_report) {
        usb::write(INTERRUPT_EPN, reinterpret_cast<uint8_t *>(&report), sizeof(report));
        last_report = report;
        report = 0;
    }
}

/**
 * @brief Set the VOLUME UP bit in report
 *
 * When the rotary encoder is turned clockwise, this should be called.
 */
void consumer_hid::set_vol_up(void)
{
    report |= REPORT_VOL_UP_MSK;
}

/**
 * @brief Set the VOLUME DOWN bit in report
 *
 * When the rotary encoder is turned counter-clockwise, this should be called.
 */
void consumer_hid::set_vol_down(void)
{
    report |= REPORT_VOL_DOWN_MSK;
}
