/**
 * @file      consumer_hid.hpp
 * @brief     USB HID Consumer device
 *
 * @author    Anthony Needles
 * @date      2021/06/27
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#include "usb/consumer_hid.hpp"

#include <cstdint>

#include "core/time_slice.hpp"
#include "usb/usb.hpp"
#include "usb/usb_definitions.hpp"
#include "usb/usb_descriptors.hpp"
#include "util/debug.hpp"
#include "stm32f0xx.h" // NOLINT

namespace {

/// Task fuction will execute every 20ms
constexpr unsigned USB_HID_TASK_PERIOD_MS = 20;

/// USB HID transactions occur on EP1, which is configure as an Interrupt EP
constexpr unsigned INTERRUPT_EPN = 1;

/// HID report structure defined by HID Report Descriptor
struct HIDKBReport{
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t key0;
    uint8_t key1;
    uint8_t key2;
    uint8_t key3;
    uint8_t key4;
    uint8_t key5;
} __PACKED;

/**
 * @brief
 */
static void send_report(void)
{
    static int count = 0;

    HIDKBReport report;

    report.modifiers = 0x00;
    report.reserved  = 0x00;
    report.key0      = 0x00;
    report.key1      = 0x00;
    report.key2      = 0x00;
    report.key3      = 0x00;
    report.key4      = 0x00;
    report.key5      = 0x00;

    usb::write(INTERRUPT_EPN, reinterpret_cast<uint8_t *>(&report), sizeof(report));
}

}  // namespace

/**
 * @brief
 */
void consumer_hid::init(void)
{
    usb::init();

    auto status = timeslice::register_task(USB_HID_TASK_PERIOD_MS, consumer_hid::task);
    DBG_ASSERT(status == timeslice::SUCCESS);

    debug::puts("Initialized: USB Consumer HID\r\n");
}

/**
 * @brief
 */
void consumer_hid::task(void)
{
    send_report();
}
