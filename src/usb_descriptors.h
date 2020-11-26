/**
 * @file      usb_descriptors.h
 * @brief     USB descriptor management
 *
 * @author    Anthony Needles
 * @date      2020/11/26
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * This module defines all of the USB descriptors (device, config, report, etc.) for a given device.
 * The information for a descriptor can then be obtained via API.
 */

#ifndef __USB_DESCRIPTORS_H
#define __USB_DESCRIPTORS_H

#include <stdint.h>

#include "stm32f0xx.h"

// Each valid descriptor gets an ID
typedef enum {
    DESCRIPTOR_DEVICE,
    DESCRIPTOR_CONFIG,
    DESCRIPTOR_LANG,
    DESCRIPTOR_MANUFACT,
    DESCRIPTOR_PRODUCT,
    DESCRIPTOR_HIDREPORT,
} usb_desc_id_t;

// Descriptor information struct
typedef struct {
    const uint8_t *buf_ptr;
    uint16_t size;
} usb_desc_t;

// HID report structure defined by HID Report Descriptor
typedef struct __PACKED {
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t key0;
    uint8_t key1;
    uint8_t key2;
    uint8_t key3;
    uint8_t key4;
    uint8_t key5;
} hid_keyboard_report_t;

/*
 * USBGetDescriptor
 *
 * @brief For obtaining descriptors
 *
 * Information for a given descriptor can be requested with this, and (if exists) a pointer to the
 * desc buffer and the size (in bytes) is returned via @desc.
 *
 * @param[in]     desc_id ID of requested descriptor
 * @param[in,out] desc    Descriptor information struct that will be populated (if @desc_id valid)
 * @return 0 if success, -1 if descriptor is not defined
 */
int USBGetDescriptor(usb_desc_id_t desc_id, usb_desc_t *desc);

#endif /* __USB_DESCRIPTORS_H */
