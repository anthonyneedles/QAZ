/**
 * @file      kb_usb_desc.hpp
 * @brief     USB descriptor management
 *
 * @author    Anthony Needles
 * @date      2020/11/26
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module defines all of the USB descriptors (device, config, report, etc.) for a given device.
 * The information for a descriptor can then be obtained via API.
 */

#ifndef USB_KB_USB_DESC_HPP_
#define USB_KB_USB_DESC_HPP_

#include <cstdint>

/**
 * @brief Keyboard descriptor namespace
 *
 * This namespace holds the means to obtain the interal USB descriptors.
 */
namespace usb_desc {

/// Each valid descriptor gets an ID
constexpr uint16_t DEVICE_ID    = 0x0100;
constexpr uint16_t CONFIG_ID    = 0x0200;
constexpr uint16_t LANG_ID      = 0x0300;
constexpr uint16_t MANUFACT_ID  = 0x0301;
constexpr uint16_t PRODUCT_ID   = 0x0302;
constexpr uint16_t HIDREPORT_ID = 0x2200;

/// Descriptor information struct
struct USBDesc {
    const uint8_t *buf_ptr;
    uint16_t size;
};

/// Obtain a USB descriptor from ID
int get_desc(uint16_t desc_id, USBDesc *desc);

}  // namespace usb_desc

#endif  // USB_KB_USB_DESC_HPP_
