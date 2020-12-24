/**
 * @file      usb_descriptors.h
 * @brief     USB descriptor management
 *
 * @author    Anthony Needles
 * @date      2020/11/26
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module defines all of the USB descriptors (device, config, report, etc.) for a given device.
 * The information for a descriptor can then be obtained via API.
 */

#ifndef USB_USB_DESCRIPTORS_H_
#define USB_USB_DESCRIPTORS_H_

#include <stdint.h>

#include "stm32f0xx.h"  // NOLINT

// Bits in modifier byte in HID report
#define MODIFIER_LCTRL_MSK  (0x01)
#define MODIFIER_LSHIFT_MSK (0x02)
#define MODIFIER_LALT_MSK   (0x04)
#define MODIFIER_LGUI_MSK   (0x08)
#define MODIFIER_RCTRL_MSK  (0x10)
#define MODIFIER_RSHIFT_MSK (0x20)
#define MODIFIER_RALT_MSK   (0x40)
#define MODIFIER_RGUI_MSK   (0x80)

// Each valid descriptor gets an ID
typedef enum {
    DESCRIPTOR_DEVICE_ID,
    DESCRIPTOR_CONFIG_ID,
    DESCRIPTOR_LANG_ID,
    DESCRIPTOR_MANUFACT_ID,
    DESCRIPTOR_PRODUCT_ID,
    DESCRIPTOR_HIDREPORT_ID,
} usb_desc_id_t;

// Descriptor information struct
typedef struct {
    const uint8_t *buf_ptr;
    uint16_t size;
} usb_desc_t;

// HID report structure defined by HID Report Descriptor
typedef struct {
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t key0;
    uint8_t key1;
    uint8_t key2;
    uint8_t key3;
    uint8_t key4;
    uint8_t key5;
} __PACKED hid_keyboard_report_t;

/**
 * @brief For obtaining descriptors
 *
 * Information for a given descriptor can be requested with this, and (if exists) a pointer to the
 * desc buffer and the size (in bytes) is returned via `desc`.
 *
 * @param[in]     desc_id ID of requested descriptor
 * @param[in,out] desc    Descriptor information struct that will be populated (if `desc_id` valid)
 * @return 0 if success, -1 if descriptor is not defined
 */
int USBGetDescriptor(usb_desc_id_t desc_id, usb_desc_t *desc);

#endif  // USB_USB_DESCRIPTORS_H_
