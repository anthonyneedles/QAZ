/**
 * @file      usb_hid.cpp
 * @brief     USB HID control
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module will use the USB driver to send keycodes to the USB host.
 */
#include "usb/usb_hid.hpp"

#include <stdint.h>

#include  "qaz/key_matrix.hpp"
#include "usb/usb.hpp"
#include "usb/usb_descriptors.hpp"
#include "usb/usb_hid_usages.hpp"
#include "util/debug.hpp"
#include "stm32f0xx.h" // NOLINT

#define INTERRUPT_EPN (1)

static_assert(KEY_BUF_SIZE >= 6, "USB HID: Key buffer size must be >= 6");

// both previous key buffer and current key buffer
typedef struct {
    keys_t curr[KEY_BUF_SIZE];
    keys_t prev[KEY_BUF_SIZE];
} key_buf_t;

static key_buf_t key_buf;

static void usbhidSendReport(void);

/**
 * @brief Intialize the USB HID module
 *
 * We only need to ready key buffers and initialize the USB driver.
 */
void USBHIDInit(void)
{
    // clear out the 'previous' key buffer
    for (int i = 0; i < KEY_BUF_SIZE; ++i) {
        key_buf.prev[i] = KEY(NOEVT);
    }

    USBInit();

    DbgPrintf("Initialized: USB HID\r\n");
}

/**
 * @brief Periodically sample key buffer, and send report if necessary
 *
 * We check the currently pressed keys, and if there has been a change then we send a new key HID
 * report.
 */
void USBHIDTask(void)
{
    KeyMatrixGetKeyBuffer(key_buf.curr);

    // we only want to send a report when keys states change
    for (int i = 0; i < KEY_BUF_SIZE; ++i) {
        if (key_buf.curr[i] != key_buf.prev[i]) {
            usbhidSendReport();
            break;
        }
    }

    // copy over 'current' keys to 'previous' keys
    for (int i = 0; i < KEY_BUF_SIZE; ++i) {
        key_buf.prev[i] = key_buf.curr[i];
    }
}

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
static void usbhidSendReport(void)
{
    hid_keyboard_report_t report;

    report.modifiers = 0x00;
    for (int i = 0; i < KEY_BUF_SIZE; ++i) {
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
    USBWrite(INTERRUPT_EPN, (uint8_t  *)(&report), sizeof(report));
}
