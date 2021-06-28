/**
 * @file      kb_hid.cpp
 * @brief     USB HID control
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module will use the USB driver to send HID keycodes to the USB host.
 */

#include "usb/kb_hid.hpp"

#include <cstdint>

#include "core/time_slice.hpp"
#include "keyboard/key_matrix.hpp"
#include "usb/usb.hpp"
#include "usb/usb_definitions.hpp"
#include "usb/kb_usb_desc.hpp"
#include "util/debug.hpp"
#include "stm32f0xx.h" // NOLINT

/// we need to ensure that our key buffer size is equal to what we describe in the report descriptor
static_assert(keymatrix::KEY_BUF_SIZE == 6, "USB HID: Key buffer size must be == 6");

namespace {

/// Task fuction will execute every 20ms
constexpr unsigned USB_HID_TASK_PERIOD_MS = 20;

/// USB HID transactions occur on EP1, which is configure as an Interrupt EP
constexpr unsigned INTERRUPT_EPN = 1;

// Bits in modifier byte in HID report
constexpr uint8_t MODIFIER_LCTRL_MSK  = 0x01;
constexpr uint8_t MODIFIER_LSHIFT_MSK = 0x02;
constexpr uint8_t MODIFIER_LALT_MSK   = 0x04;
constexpr uint8_t MODIFIER_LGUI_MSK   = 0x08;
constexpr uint8_t MODIFIER_RCTRL_MSK  = 0x10;
constexpr uint8_t MODIFIER_RSHIFT_MSK = 0x20;
constexpr uint8_t MODIFIER_RALT_MSK   = 0x40;
constexpr uint8_t MODIFIER_RGUI_MSK   = 0x80;

/// Both previous key buffer and current key buffer so we can detect a change
struct KeyBuf {
    keymatrix::Key curr[keymatrix::KEY_BUF_SIZE];
    keymatrix::Key prev[keymatrix::KEY_BUF_SIZE];
};

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

/// Where we hold hold current and previous key buffer copies
KeyBuf key_buf;

}  // namespace

/**
 * @brief Populate HID report and send it off
 *
 * The report buffer has been defined in the report descriptor that was requested from the device
 * by the host (handled in the usb driver).
 *
 * Technically we don't need to include the key codes for modifier keys (e.g. LCTRL = 0xE0) since
 * drivers just ignore them, but we do anyways because it would involve more logic and we wouldn't
 * gain anything from excluding them.
 */
static void send_report(void)
{
    HIDKBReport report;

    report.modifiers = 0x00;
    for (unsigned i = 0; i < keymatrix::KEY_BUF_SIZE; ++i) {
        switch (key_buf.curr[i]) {
        case KEY(LCTRL):
            report.modifiers |= MODIFIER_LCTRL_MSK;
            break;
        case KEY(LSHFT):
            report.modifiers |= MODIFIER_LSHIFT_MSK;
            break;
        case KEY(LALT):
            report.modifiers |= MODIFIER_LALT_MSK;
            break;
        case KEY(LGUI):
            report.modifiers |= MODIFIER_LGUI_MSK;
            break;
        case KEY(RCTRL):
            report.modifiers |= MODIFIER_RCTRL_MSK;
            break;
        case KEY(RSHFT):
            report.modifiers |= MODIFIER_RSHIFT_MSK;
            break;
        case KEY(RALT):
            report.modifiers |= MODIFIER_RALT_MSK;
            break;
        case KEY(RGUI):
            report.modifiers |= MODIFIER_RGUI_MSK;
            break;
        default:
            break;
        }
    }
    report.reserved  = 0x00;
    report.key0      = key_buf.curr[0];
    report.key1      = key_buf.curr[1];
    report.key2      = key_buf.curr[2];
    report.key3      = key_buf.curr[3];
    report.key4      = key_buf.curr[4];
    report.key5      = key_buf.curr[5];
    usb::write(INTERRUPT_EPN, reinterpret_cast<uint8_t *>(&report), sizeof(report));
}

/**
 * @brief Intialize the USB HID module
 *
 * We only need to ready key buffers and initialize the USB driver.
 */
void kb_hid::init(void)
{
    // clear out the 'previous' key buffer
    for (unsigned i = 0; i < keymatrix::KEY_BUF_SIZE; ++i) {
        key_buf.prev[i] = KEY(NOEVT);
    }

    usb::init();

    auto status = timeslice::register_task(USB_HID_TASK_PERIOD_MS, kb_hid::task);
    DBG_ASSERT(status == timeslice::SUCCESS);

    debug::puts("Initialized: USB Keyboard HID\r\n");
}

/**
 * @brief Periodically sample key buffer, and send report if necessary
 *
 * We check the currently pressed keys, and if there has been a change then we send a new key HID
 * report.
 */
void kb_hid::task(void)
{
    keymatrix::copy_key_buffer(key_buf.curr);

    // we only want to send a report when keys states change
    for (unsigned i = 0; i < keymatrix::KEY_BUF_SIZE; ++i) {
        if (key_buf.curr[i] != key_buf.prev[i]) {
            send_report();
            break;
        }
    }

    // copy over 'current' keys to 'previous' keys
    for (unsigned i = 0; i < keymatrix::KEY_BUF_SIZE; ++i) {
        key_buf.prev[i] = key_buf.curr[i];
    }
}
