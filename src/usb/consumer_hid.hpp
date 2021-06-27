/**
 * @file      consumer_hid.hpp
 * @brief     USB HID Consumer device
 *
 * @author    Anthony Needles
 * @date      2021/06/27
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#ifndef USB_CONSUMER_HID_HPP_
#define USB_CONSUMER_HID_HPP_

/**
 * @brief
 */
namespace consumer_hid {

///
void init(void);

///
void task(void);

}  // namespace consumer_hid

#endif  // USB_CONSUMER_HID_HPP_
