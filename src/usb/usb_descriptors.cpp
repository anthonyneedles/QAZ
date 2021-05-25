/**
 * @file      usb_descriptors.cpp
 * @brief     USB descriptor management
 *
 * @author    Anthony Needles
 * @date      2020/11/26
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module defines all of the USB descriptors (device, config, report, etc.) for a given device.
 * The information for a descriptor can then be obtained via API.
 */

#include "usb/usb_descriptors.hpp"

#include "util/debug.hpp"
#include "util/expressions.hpp"

namespace {

/// Device descriptor. Contains basic information about the device and specify string desc indicies.
constexpr uint8_t DESCRIPTOR_DEVICE[] = {
      18,        // bLength
       1,        // bDescriptorType        Device
    0x00, 0x02,  // bcdUSB                 USB 2.0
    0x00,        // bDeviceClass           Interface defined
    0x00,        // bDeviceSubClass
    0x00,        // bDeviceProtocol
      64,        // bMaxPacketSize         64 bytes
    0x1D, 0xC0,  // idVendor               0xC01D
    0x22, 0xAA,  // idProduct              0xAA22
    0x00, 0x01,  // bcdDevice              0.1
       1,        // iManufacturer          'anthonyneedles'
       2,        // iProduct               'qaz keyboard'
       0,        // iSerialNumber
       1,        // bNumConfigurations
};

// TODO: wakeup? 2 interfaces.
/// Configuration, Interface, HID, and Endpoint  descriptors. These are eventually asked for, all at
/// once. These define the device interface as USB HID Keyboard, the report size, and the interrupt
/// endpoint config.
constexpr uint8_t DESCRIPTOR_CONFIG[] = {
// Configuration Descriptor
       9,        // bLength
       2,        // bDescriptorType        Configuration
      34, 0x00,  // wTotalLength           9 + 9 + 9 + 7
       1,        // bNumInterfaces
       1,        // bConfigurationValue    Set Configuration argument
       0,        // iConfiguration         No string
    0x80,        // bmAttributes           Bus powered, no wake-up
     250,        // bMaxPower              250*2 = 500 mA
// Interface Descriptor
       9,        // bLength
       4,        // bDescriptorType        Interface
       0,        // bInterfaceNumber
       0,        // bAlternateSetting
       1,        // bNumEndpoints
    0x03,        // bInterfaceClass        HID
    0x01,        // bInterfaceSubClass     Boot
    0x01,        // bInterfaceProtocol     Keyboard
       0,        // iInterface             No string
// HID Descriptor
       9,        // bLength
    0x21,        // bDescriptorType        HID
    0x11, 0x01,  // bcdHID                 HID 1.11
    0x00,        // bCountryCode           Not localized
       1,        // bNumDescriptors
    0x22,        // bDescriptorType        Report
      64, 0x00,  // wDescriptorLength      64 bytes
// Endpoint 1 In Descriptor
       7,        // bLength
       5,        // bDescriptorType        Endpoint
    0x81,        // bEndpointAddress       1, In
    0x03,        // bmAttributes           Interrupt
       8, 0x00,  // wMaxPacketSize         4 bytes
      10,        // bInterval              10 ms
};

/// Language String Descriptor (index 0). Our string descs are in English.
constexpr uint8_t DESCRIPTOR_LANG[] = {
       4,        // bLength                2 + 2*2
       3,        // bDescriptorType        String
    0x09, 0x04,  // wLANGID[0]             English (US)
};

/// Manufactrurer String Descriptor (index 1). In Unicode format.
constexpr uint8_t DESCRIPTOR_MANUFACT[] = {
      30,         // bLength                2 + 14*2
       3,         // bDescriptorType        String
      'a', 0x00,  // wString                anthonyneedles
      'n', 0x00,
      't', 0x00,
      'h', 0x00,
      'o', 0x00,
      'n', 0x00,
      'y', 0x00,
      'n', 0x00,
      'e', 0x00,
      'e', 0x00,
      'd', 0x00,
      'l', 0x00,
      'e', 0x00,
      's', 0x00,
};

/// Product String Descriptor (index 2). In Unicode format.
constexpr uint8_t DESCRIPTOR_PRODUCT[] = {
      26,         // bLength                2 + 14*2
       3,         // bDescriptorType        String
      'q', 0x00,  // wString                qaz keyboard
      'a', 0x00,
      'z', 0x00,
      ' ', 0x00,
      'k', 0x00,
      'e', 0x00,
      'y', 0x00,
      'b', 0x00,
      'o', 0x00,
      'a', 0x00,
      'r', 0x00,
      'd', 0x00,
};

/// HID Report Descriptor. Defines the format of key packets we send.
constexpr uint8_t DESCRIPTOR_HIDREPORT[] = {
    0x05, 0x01,  // Usage Page   = Desktop,
    0x09, 0x06,  // Usage        = Keyboard,
    0xA1, 0x01,  // Collection   = Application,
    0x05, 0x07,  // Usage Page   = Keyboard,
// Keyboard Input, Byte 0: Modifier bitmap (Ctrl, Shift, Alt, etc.)
    0x19, 0xE0,  // Usage Min    = KB LCtrl,
    0x29, 0xE7,  // Usage Max    = KB RGui,
    0x15, 0x00,  // Logical Min  = 0,
    0x25, 0x01,  // Logical Max  = 1,
    0x75, 0x01,  // Report Size  = 1,
    0x95, 0x08,  // Report Count = 8,
    0x81, 0x02,  // Input        = Data, Var, Abs
// Keyboard Input, Byte 1: Reserved
    0x95, 0x01,  // Report Count = 1,
    0x75, 0x08,  // Report Size  = 8,
    0x81, 0x01,  // Input        = Cnst, Arr, Abs
// LED Output Report
    0x95, 0x05,  // Report Count = 5
    0x75, 0x01,  // Report Size  = 1
    0x05, 0x08,  // Usage Page   = LED
    0x19, 0x01,  // Usage Min    = 1
    0x29, 0x05,  // Usage Min    = 5
    0x91, 0x02,  // Output       = Data, Var, Abs
    0x95, 0x01,  // Report Count = 1
    0x75, 0x03,  // Report Size  = 3
    0x91, 0x01,  // Output       = Cnst
// Keyboard Input, Bytes 2-7: Pressed Key Keycodes
    0x95, 0x06,  // Report Count = 6
    0x75, 0x08,  // Report Size  = 8
    0x15, 0x00,  // Logical Min  = 0
    0x26, 0x97,  // Logical Max  = 101
    0x00,
    0x05, 0x07,  // Usage Page   = Keyboard
    0x19, 0x00,  // Usage Min    = No Event,
    0x29, 0x97,  // Usage Max    = Max Keycode,
    0x81, 0x00,  // Input        = Data, Arr, Abs
    0xC0,        // End Collection
};

/// Descriptor table entry, pairing the desc ID with desc info
struct USBDescTableEntry{
    uint16_t id;
    usb_desc::USBDesc desc;
};

/// Descriptor table, with an entry for each descriptor
constexpr USBDescTableEntry desc_table[] = {
    { usb_desc::DEVICE_ID,    { DESCRIPTOR_DEVICE,    sizeof(DESCRIPTOR_DEVICE)    } },
    { usb_desc::CONFIG_ID,    { DESCRIPTOR_CONFIG,    sizeof(DESCRIPTOR_CONFIG)    } },
    { usb_desc::LANG_ID,      { DESCRIPTOR_LANG,      sizeof(DESCRIPTOR_LANG)      } },
    { usb_desc::MANUFACT_ID,  { DESCRIPTOR_MANUFACT,  sizeof(DESCRIPTOR_MANUFACT)  } },
    { usb_desc::PRODUCT_ID,   { DESCRIPTOR_PRODUCT,   sizeof(DESCRIPTOR_PRODUCT)   } },
    { usb_desc::HIDREPORT_ID, { DESCRIPTOR_HIDREPORT, sizeof(DESCRIPTOR_HIDREPORT) } },
};

}  // namespace

/**
 * @brief For obtaining descriptors
 *
 * Information for a given descriptor can be requested with this, and (if exists) a pointer to the
 * desc buffer and the size (in bytes) is returned via `desc`.
 *
 * @param[in]     desc_id  ID of requested descriptor
 * @param[in,out] desc     Descriptor information struct that will be populated (if `desc_id` valid)
 *
 * @return 0 if success, -1 if descriptor is not defined
 */
int usb_desc::get_desc(uint16_t desc_id, USBDesc *desc)
{
    int ret = -1;

    debug::printf("<<0x%04x>> ", desc_id);

    for (unsigned i = 0; i < COUNT_OF(desc_table); ++i) {
        if (desc_table[i].id == desc_id) {
            desc->buf_ptr = desc_table[i].desc.buf_ptr;
            desc->size    = desc_table[i].desc.size;
            ret = 0;
            break;
        }
    }

    if (ret == -1) {
        debug::printf("ERROR: Requested undefined descriptor (%d)\r\n", desc_id);
    }

    return ret;
}
