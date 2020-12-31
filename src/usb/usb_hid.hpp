/**
 * @file      usb_hid.h
 * @brief     USB HID control
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module will use the USB driver to send keycodes to the USB host.
 */

#ifndef USB_USB_HID_HPP_
#define USB_USB_HID_HPP_

#define USB_HID_TASK_PERIOD_MS (20U)

/**
 * @brief Intialize the USB HID module
 *
 * We only need to ready key buffers and initialize the USB driver.
 */
void USBHIDInit(void);

/**
 * @brief Periodically sample key buffer, and send report if necessary
 *
 * We check the currently pressed keys, and if there has been a change then we send a new key HID
 * report.
 */
void USBHIDTask(void);

#endif  // USB_USB_HID_HPP_
