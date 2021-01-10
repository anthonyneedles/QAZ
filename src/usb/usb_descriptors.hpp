/**
 * @file      usb_descriptors.hpp
 * @brief     USB descriptor management
 *
 * @author    Anthony Needles
 * @date      2020/11/26
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module defines all of the USB descriptors (device, config, report, etc.) for a given device.
 * The information for a descriptor can then be obtained via API.
 */

#ifndef USB_USB_DESCRIPTORS_HPP_
#define USB_USB_DESCRIPTORS_HPP_

#include <cstdint>

/**
 * @brief Keyboard descriptor namespace
 *
 * This namespace holds the means to obtain the interal USB descriptors.
 */
namespace usb_desc {

/// Each valid descriptor gets an ID
enum USBDescId {
    DEVICE_ID,
    CONFIG_ID,
    LANG_ID,
    MANUFACT_ID,
    PRODUCT_ID,
    HIDREPORT_ID,
};

/// Descriptor information struct
struct USBDesc {
    const std::uint8_t *buf_ptr;
    std::uint16_t size;
};

/// Obtain a USB descriptor from ID
int get_desc(USBDescId desc_id, USBDesc *desc);

}  // namespace usb_desc

#endif  // USB_USB_DESCRIPTORS_HPP_
