/**
 * @file      usb_definitions.hpp
 * @brief     USB constants
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Define values in packets, HID usages, etc.
 */

#ifndef USB_USB_DEFINITIONS_HPP_
#define USB_USB_DEFINITIONS_HPP_

// SETUP packet bmRequestType[7]
#define REQ_DIR_IN   (0x80U)
#define REQ_DIR_OUT  (0x00U)

// SETUP packet bmRequestType[6:5]
#define REQ_TYP_STD  (0x00U)
#define REQ_TYP_CLS  (0x20U)
#define REQ_TYP_VDR  (0x40U)

// SETUP packet bmRequestType[4:0]
#define REQ_RCP_DEV  (0x00U)
#define REQ_RCP_ITF  (0x01U)
#define REQ_RCP_EP   (0x02U)

// Entire bmRequestType field
#define REQ_IN_STD_DEV  (REQ_DIR_IN  | REQ_TYP_STD | REQ_RCP_DEV)
#define REQ_IN_STD_ITF  (REQ_DIR_IN  | REQ_TYP_STD | REQ_RCP_ITF)
#define REQ_OUT_CLS_ITF (REQ_DIR_OUT | REQ_TYP_CLS | REQ_RCP_ITF)
#define REQ_OUT_STD_DEV (REQ_DIR_OUT | REQ_TYP_STD | REQ_RCP_DEV)
#define REQ_OUT_STD_EP  (REQ_DIR_OUT | REQ_TYP_STD | REQ_RCP_EP)

// SETUP packet bRequest
#define REQ_GET_STAT (0x00U)
#define REQ_CLR_STAT (0x01U)
#define REQ_SET_ADDR (0x05U)
#define REQ_GET_DESC (0x06U)
#define REQ_SET_CFG  (0x09U)
#define REQ_SET_IDLE (0x0AU)
#define REQ_SET_RPT  (0x09U)

// Combines SETUP packet bRequest/bmRequestType fields
#define REQ(type, req) (((uint16_t)(type) << 8) | ((uint16_t)(req) & 0xFF))

// Keyboard/Keypad Page (0x07)

// User-defined (not sent)
// HID Usage codes are interpreted as 16-bit unsigned integers, but 0x00E8-0xFFFF is "reserved"
#define HID_USAGE_KEYBOARD_FN    ( -1)  // alt function
#define HID_USAGE_KEYBOARD_BRTUP ( -2)  // brightness up
#define HID_USAGE_KEYBOARD_BRTDN ( -3)  // brightness down
#define HID_USAGE_KEYBOARD_PROF  ( -4)  // cycle profiles
#define HID_USAGE_KEYBOARD_SPDUP ( -5)  // profile speed up
#define HID_USAGE_KEYBOARD_SPDDN ( -6)  // profile speed down
#define HID_USAGE_KEYBOARD_R_UP  ( -7)  // increment red color
#define HID_USAGE_KEYBOARD_G_UP  ( -8)  // increment green color
#define HID_USAGE_KEYBOARD_B_UP  ( -9)  // increment blue color
#define HID_USAGE_KEYBOARD_R_DN  (-10)  // decrement red color
#define HID_USAGE_KEYBOARD_G_DN  (-11)  // decrement green color
#define HID_USAGE_KEYBOARD_B_DN  (-12)  // decrement blue color

// Errors
#define HID_USAGE_KEYBOARD_NOEVT (0x00)
#define HID_USAGE_KEYBOARD_NONE  (HID_USAGE_KEYBOARD_NOEVT)
#define HID_USAGE_KEYBOARD_ROVER (0x01)
#define HID_USAGE_KEYBOARD_POSTF (0x02)
#define HID_USAGE_KEYBOARD_UNDEF (0x03)

// Letters
#define HID_USAGE_KEYBOARD_A     (0x04)
#define HID_USAGE_KEYBOARD_B     (0x05)
#define HID_USAGE_KEYBOARD_C     (0x06)
#define HID_USAGE_KEYBOARD_D     (0x07)
#define HID_USAGE_KEYBOARD_E     (0x08)
#define HID_USAGE_KEYBOARD_F     (0x09)
#define HID_USAGE_KEYBOARD_G     (0x0A)
#define HID_USAGE_KEYBOARD_H     (0x0B)
#define HID_USAGE_KEYBOARD_I     (0x0C)
#define HID_USAGE_KEYBOARD_J     (0x0D)
#define HID_USAGE_KEYBOARD_K     (0x0E)
#define HID_USAGE_KEYBOARD_L     (0x0F)
#define HID_USAGE_KEYBOARD_M     (0x10)
#define HID_USAGE_KEYBOARD_N     (0x11)
#define HID_USAGE_KEYBOARD_O     (0x12)
#define HID_USAGE_KEYBOARD_P     (0x13)
#define HID_USAGE_KEYBOARD_Q     (0x14)
#define HID_USAGE_KEYBOARD_R     (0x15)
#define HID_USAGE_KEYBOARD_S     (0x16)
#define HID_USAGE_KEYBOARD_T     (0x17)
#define HID_USAGE_KEYBOARD_U     (0x18)
#define HID_USAGE_KEYBOARD_V     (0x19)
#define HID_USAGE_KEYBOARD_W     (0x1A)
#define HID_USAGE_KEYBOARD_X     (0x1B)
#define HID_USAGE_KEYBOARD_Y     (0x1C)
#define HID_USAGE_KEYBOARD_Z     (0x1D)

// Numbers
#define HID_USAGE_KEYBOARD_1     (0x1E)
#define HID_USAGE_KEYBOARD_2     (0x1F)
#define HID_USAGE_KEYBOARD_3     (0x20)
#define HID_USAGE_KEYBOARD_4     (0x21)
#define HID_USAGE_KEYBOARD_5     (0x22)
#define HID_USAGE_KEYBOARD_6     (0x23)
#define HID_USAGE_KEYBOARD_7     (0x24)
#define HID_USAGE_KEYBOARD_8     (0x25)
#define HID_USAGE_KEYBOARD_9     (0x26)
#define HID_USAGE_KEYBOARD_0     (0x27)

// Symbols
#define HID_USAGE_KEYBOARD_DASH  (0x2D)
#define HID_USAGE_KEYBOARD_EQUAL (0x2E)
#define HID_USAGE_KEYBOARD_LBRKT (0x2F)
#define HID_USAGE_KEYBOARD_RBRKT (0x30)
#define HID_USAGE_KEYBOARD_BSLSH (0x31)
#define HID_USAGE_KEYBOARD_SEMI  (0x33)
#define HID_USAGE_KEYBOARD_QUOTE (0x34)
#define HID_USAGE_KEYBOARD_GRAVE (0x35)
#define HID_USAGE_KEYBOARD_COMMA (0x36)
#define HID_USAGE_KEYBOARD_PRIOD (0x37)
#define HID_USAGE_KEYBOARD_FSLSH (0x38)

// Modifier keys
#define HID_USAGE_KEYBOARD_CPLCK (0x39)
#define HID_USAGE_KEYBOARD_SCRLL (0x47)
#define HID_USAGE_KEYBOARD_LCTRL (0xE0)
#define HID_USAGE_KEYBOARD_LSHFT (0xE1)
#define HID_USAGE_KEYBOARD_LALT  (0xE2)
#define HID_USAGE_KEYBOARD_LGUI  (0xE3)
#define HID_USAGE_KEYBOARD_RCTRL (0xE4)
#define HID_USAGE_KEYBOARD_RSHFT (0xE5)
#define HID_USAGE_KEYBOARD_RALT  (0xE6)
#define HID_USAGE_KEYBOARD_RGUI  (0xE7)

// Function keys
#define HID_USAGE_KEYBOARD_F1    (0x3A)
#define HID_USAGE_KEYBOARD_F2    (0x3B)
#define HID_USAGE_KEYBOARD_F3    (0x3C)
#define HID_USAGE_KEYBOARD_F4    (0x3D)
#define HID_USAGE_KEYBOARD_F5    (0x3E)
#define HID_USAGE_KEYBOARD_F6    (0x3F)
#define HID_USAGE_KEYBOARD_F7    (0x40)
#define HID_USAGE_KEYBOARD_F8    (0x41)
#define HID_USAGE_KEYBOARD_F9    (0x42)
#define HID_USAGE_KEYBOARD_F10   (0x43)
#define HID_USAGE_KEYBOARD_F11   (0x44)
#define HID_USAGE_KEYBOARD_F12   (0x45)

// Arrows
#define HID_USAGE_KEYBOARD_RARRW (0x4F)
#define HID_USAGE_KEYBOARD_LARRW (0x50)
#define HID_USAGE_KEYBOARD_DARRW (0x51)
#define HID_USAGE_KEYBOARD_UARRW (0x52)

// Special keys
#define HID_USAGE_KEYBOARD_ENTER (0x28)
#define HID_USAGE_KEYBOARD_ESC   (0x29)
#define HID_USAGE_KEYBOARD_BKSPC (0x2A)
#define HID_USAGE_KEYBOARD_TAB   (0x2B)
#define HID_USAGE_KEYBOARD_SPACE (0x2C)
#define HID_USAGE_KEYBOARD_PRSCR (0x46)
#define HID_USAGE_KEYBOARD_INSRT (0x49)
#define HID_USAGE_KEYBOARD_PGEUP (0x4B)
#define HID_USAGE_KEYBOARD_DELET (0x4C)
#define HID_USAGE_KEYBOARD_PGEDN (0x4E)
#define HID_USAGE_KEYBOARD_VOLUP (0x80)
#define HID_USAGE_KEYBOARD_VOLDN (0x81)

#endif  // USB_USB_DEFINITIONS_HPP_
