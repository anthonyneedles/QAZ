/**
 * @file      usb.hpp
 * @brief     USB driver
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module interfaces with the USB peripheral to establish basic USB HID communications with
 * host.
 *
 * Endpoint 0 -> Control
 * Endpoint 1 -> Interrupt, TX only
 */

#ifndef USB_USB_HPP_
#define USB_USB_HPP_

#include <stdint.h>

#define USB_TASK_PERIOD_MS (20U)

/// Init the USB module and enter USB RESET
void USBInit(void);

/// Write via USB with a given endpoint
void USBWrite(int ep, const uint8_t *buf, uint16_t len);

#endif  // USB_USB_HPP_
