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

#ifndef USB_CONSUMER_HID_HPP_
#define USB_CONSUMER_HID_HPP_

/**
 * @brief Consumer HID namespace
 *
 * This namespace holds the USB HID Consumer device init and task routines.
 */
namespace consumer_hid {

/// Init USB driver and set button callbacks
void init(void);

/// Send and clear report if needed
void task(void);

/// Set the VOLUME UP report bit
void set_vol_up(void);

/// Set the VOLUME DOWN report bit
void set_vol_down(void);

}  // namespace consumer_hid

#endif  // USB_CONSUMER_HID_HPP_
