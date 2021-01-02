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

/**
 * @brief Performs USB port, clock, and peripheral initialization
 *
 * USB port is used in startup (for DFU), so the ports come up configured. Host detects device upon
 * DP pullup enable.
 */
void USBInit(void);

/**
 * @brief Write data from input buffer into PMA, set TX byte count, and set TX STATUS to VALID
 *
 * Due to a bug when writing bytes into the PMA, only halfword accesses work. So `len` will
 * need to always be even (and `buf` an even number of bytes).
 *
 * Only works because MCU architecture and USB protocol is little endian.
 *
 * @param[in] ep  the endpoint to write with
 * @param[in] buf input buffer that contains data to be tranmitted
 * @param[in] len number of bytes in `buf`
 */
void USBWrite(int ep, const uint8_t *buf, uint16_t len);

#endif  // USB_USB_HPP_
