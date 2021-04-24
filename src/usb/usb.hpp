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

/**
 * @brief USB driver namespace
 *
 * This namespace holds the means to communicate using USB.
 */
namespace usb {

/// Init the USB module and enter USB RESET
void init(void);

/// Write via USB with a given endpoint
void write(uint16_t ep, const uint8_t *buf, uint16_t len);

/// Read via USB with a given endpoint
void read(uint16_t ep, uint8_t *in_buf);

}  // namespace usb

#endif  // USB_USB_HPP_
