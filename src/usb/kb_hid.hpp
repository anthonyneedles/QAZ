/**
 * @file      kb_hid.hpp
 * @brief     USB HID Keyboard device
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module will use the USB driver to send HID keycodes to the USB host.
 */

#ifndef USB_KB_HID_HPP_
#define USB_KB_HID_HPP_

/**
 * @brief Keyboard HID namespace
 *
 * This namespace holds the USB HID Keyboard device init and task routines.
 */
namespace kb_hid {

// Inits the USB HID (which includes initializing the base USB driver)
void init(void);

// Sample the key buffer. If there is a change, send new HID report
void task(void);

}  // namespace kb_hid

#endif  // USB_KB_HID_HPP_
