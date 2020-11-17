/*
 * usb_descriptors.h
 *
 *
 * Project: QAZ
 * MCU: STM32F042K6
 * Copyright: (c) 2020 by Anthony Needles
 * License: GNU GPL v3 (see LICENSE)
 */

#ifndef __USB_DESCRIPTORS_H
#define __USB_DESCRIPTORS_H

#include <stdint.h>

static const uint8_t USBDesc_Device[] = {
      18U,        //  0/1 bLength
       1U,        //  1/1 bDescriptorType        Device
    0x00U, 0x02U, //  2/2 bcdUSB                 USB 2.0
    0x00U,        //  4/1 bDeviceClass           Interface defined
    0x00U,        //  5/1 bDeviceSubClass
    0x00U,        //  6/1 bDeviceProtocol
      64U,        //  7/1 bMaxPacketSize         64 bytes
    0x1DU, 0xC0U, //  8/2 idVendor               0xC01D
    0x22U, 0xAAU, // 10/2 idProduct              0xAA22
    0x00U, 0x01U, // 12/2 bcdDevice              0.1
       1U,        // 14/1 iManufacturer          'anthonyneedles'
       2U,        // 15/1 iProduct               'qaz keyboard'
       0U,        // 16/1 iSerialNumber
       1U,        // 17/1 bNumConfigurations
};

// TODO: boot protocol
static const uint8_t USBDesc_Config[] = {
// Configuration Descriptor
       9U,        //  0/1 bLength
       2U,        //  1/1 bDescriptorType        Configuration
      34U, 0x00U, //  2/2 wTotalLength           9 + 9 + 9 + 7
       1U,        //  4/1 bNumInterfaces
       1U,        //  5/1 bConfigurationValue    Set Configuration argument
       0U,        //  6/1 iConfiguration         No string
    0x80U,        //  7/1 bmAttributes           Bus powered, no wake-up
     250U,        //  8/1 bMaxPower              250*2 = 500 mA
// Interface Descriptor
       9U,        //  0/1 bLength
       4U,        //  1/1 bDescriptorType        Interface
       0U,        //  2/1 bInterfaceNumber
       0U,        //  3/1 bAlternateSetting
       1U,        //  4/1 bNumEndpoints
    0x03U,        //  5/1 bInterfaceClass        HID
    0x01U,        //  6/1 bInterfaceSubClass     Boot
    0x02U,        //  7/1 bInterfaceProtocol     Mouse
       0U,        //  8/1 iInterface             No string
// HID Descriptor
       9U,        //  0/1 bLength
    0x21U,        //  1/1 bDescriptorType        HID
    0x11U, 0x01U, //  2/2 bcdHID                 HID 1.11
    0x00U,        //  4/1 bCountryCode           Not localized
       1U,        //  5/1 bNumDescriptors
    0x22U,        //  6/1 bDescriptorType        Report
      52U, 0x00U, //  7/2 wDescriptorLength      52 bytes
// Endpoint 1 In Descriptor
       7U,        //  0/1 bLength
       5U,        //  1/1 bDescriptorType        Endpoint
    0x81U,        //  2/1 bEndpointAddress       1, In
    0x03U,        //  3/1 bmAttributes           Interrupt
      4U, 0x00U,  //  4/2 wMaxPacketSize         4 bytes
     10U,         //  6/1 bInterval              10 ms
};

static const uint8_t USBDesc_Lang[] = {
       4U,        //  0/1 bLength                2 + 2*2
       3U,        //  1/1 bDescriptorType        String
    0x09U, 0x04U, //  2/2 wLANGID[0]             English (US)
};

static const uint8_t USBDesc_Manufact[] = {
      30U,        //  0/1 bLength                2 + 14*2
       3U,        //  1/1 bDescriptorType        String
      'a', 0x00U, //  2/2 wString
      'n', 0x00U, //  4/2
      't', 0x00U, //  6/2
      'h', 0x00U, //  8/2
      'o', 0x00U, // 10/2
      'n', 0x00U, // 12/2
      'y', 0x00U, // 14/2
      'n', 0x00U, // 16/2
      'e', 0x00U, // 18/2
      'e', 0x00U, // 20/2
      'd', 0x00U, // 22/2
      'l', 0x00U, // 24/2
      'e', 0x00U, // 26/2
      's', 0x00U, // 28/2
};

static const uint8_t USBDesc_Product[] = {
      26U,        //  0/1 bLength                2 + 14*2
       3U,        //  1/1 bDescriptorType        String
      'q', 0x00U, //  2/2 wString
      'a', 0x00U, //  4/2
      'z', 0x00U, //  6/2
      ' ', 0x00U, //  8/2
      'k', 0x00U, // 10/2
      'e', 0x00U, // 12/2
      'y', 0x00U, // 14/2
      'b', 0x00U, // 16/2
      'o', 0x00U, // 18/2
      'a', 0x00U, // 20/2
      'r', 0x00U, // 22/2
      'd', 0x00U, // 24/2
};

static const uint8_t USBDesc_HIDReport[] = {
    0x05, 0x01,
    0x09, 0x02,
    0xA1, 0x01,
    0x09, 0x01,
    0xA1, 0x00,
    0x05, 0x09,
    0x19, 0x01,
    0x29, 0x05,
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x05,
    0x75, 0x01,
    0x81, 0x02,
    0x95, 0x01,
    0x75, 0x03,
    0x81, 0x01,
    0x05, 0x01,
    0x09, 0x30,
    0x09, 0x31,
    0x09, 0x38,
    0x15, 0x81,
    0x25, 0x7F,
    0x75, 0x08,
    0x95, 0x03,
    0x81, 0x06,
    0xC0,
    0xC0,
//     0x05U, 0x01U, //  0/2 Usage Page   = Desktop,          bTag = 0, GLOBAL, 1B
//     0x09U, 0x06U, //  2/2 Usage        = Keyboard,         bTag = 0,  LOCAL, 1B
//     0xA1U, 0x01U, //  4/2 Collection   = Application,      bTag = A,   MAIN, 1B
//     0x05U, 0x07U, //  6/2 Usage Page   = Keyboard,         bTag = 0, GLOBAL, 1B
// // Keyboard Input, Byte 0: Modifier bitmap (Ctrl, Shift, Alt, etc.)
//     0x19U, 0xE0U, //  8/2 Usage Min    = KB LCtrl,         bTag = 1,  LOCAL, 1B
//     0x29U, 0xE7U, // 10/2 Usage Max    = KB RGui,          bTag = 2,  LOCAL, 1B
//     0x15U, 0x00U, // 12/2 Logical Min  = 0,                bTag = 1, GLOBAL, 1B
//     0x25U, 0x01U, // 14/2 Logical Max  = 1,                bTag = 2, GLOBAL, 1B
//     0x75U, 0x01U, // 16/2 Report Size  = 1,                bTag = 7, GLOBAL, 1B
//     0x95U, 0x08U, // 18/2 Report Count = 8,                bTag = 9, GLOBAL, 1B
//     0x81U, 0x02U, // 20/2 Input = Data, Var, Abs, BF,      bTag = 8,   MAIN, 1B
// // Keyboard Input, Byte 1: Reserved
//     0x95U, 0x01U, // 22/2 Report Count = 1,                bTag = 9, GLOBAL, 1B
//     0x75U, 0x08U, // 24/2 Report Size  = 8,                bTag = 7, GLOBAL, 1B
//     0x81U, 0x01U, // 26/2 Input = Cnst, Arr, Abs, BF,      bTag = 8,   MAIN, 1B
// // Keyboard Input, BBytes 2-7: Pressed Key Keycodes
//     0x95U, 0x06U, // 28/2 Report Count = 6,                bTag = 9, GLOBAL, 1B
//     0x75U, 0x08U, // 30/2 Report Size  = 8,                bTag = 7, GLOBAL, 1B
//     0x19U, 0x00U, // 32/2 Usage Min    = No Event,         bTag = 1,  LOCAL, 1B
//     0x2AU,        // 34/3 Usage Max    = Max Keycode,      bTag = 2,  LOCAL, 2B
//     0xFFU, 0x00U,
//     0x15U, 0x00U, // 37/2 Logical Min  = 0,                bTag = 1, GLOBAL, 1B
//     0x26U,        // 39/3 Logical Max  = 255,              bTag = 2, GLOBAL, 2B
//     0xFFU, 0x00U,
//     0x81U, 0x00U, // 42/2 Input = Data, Arr, Abs, BF,      bTag = 8,   MAIN, 1B
//     0xC0U, 0x00U  // 44/2 End Collection
};

#endif /* __USB_DESCRIPTORS_H */
