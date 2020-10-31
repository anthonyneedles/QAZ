/**
 * @file    key_matrix.h
 * @author  Anthony Needles
 * @date    2020/10/31
 * @brief   Keyboard/Keypad Page (0x07) HID usages
 *
 * HID usages keys to be sent to the USB HID host
 */

#ifndef __USB_HID_USAGES_H
#define __USB_HID_USAGES_H

// Keyboard/Keypad Page (0x07)

// User-defined (not sent)
// HID Usage codes are interpreted as 16-bit unsigned integers, but 0x00E8-0xFFFF is "reserved"
#define HID_USAGE_KEYBOARD_FN    (-1)  // alt function
#define HID_USAGE_KEYBOARD_BRTUP (-2)  // brightness up
#define HID_USAGE_KEYBOARD_BRTDN (-3)  // brightness down
#define HID_USAGE_KEYBOARD_COLOR (-4)  // cycle colors
#define HID_USAGE_KEYBOARD_PROF  (-5)  // cycle profiles

// Errors
#define HID_USAGE_KEYBOARD_NOEVT (0x00)
#define HID_USAGE_KEYBOARD_ROVER (0x01)
#define HID_USAGE_KEYBOARD_POSTF (0x02)
#define HID_USAGE_KEYBOARD_UNDEF (0x03)

// Letters
#define HID_USAGE_KEYBOARD_a     (0x04)
#define HID_USAGE_KEYBOARD_b     (0x05)
#define HID_USAGE_KEYBOARD_c     (0x06)
#define HID_USAGE_KEYBOARD_d     (0x07)
#define HID_USAGE_KEYBOARD_e     (0x08)
#define HID_USAGE_KEYBOARD_f     (0x09)
#define HID_USAGE_KEYBOARD_g     (0x0A)
#define HID_USAGE_KEYBOARD_h     (0x0B)
#define HID_USAGE_KEYBOARD_i     (0x0C)
#define HID_USAGE_KEYBOARD_j     (0x0D)
#define HID_USAGE_KEYBOARD_k     (0x0E)
#define HID_USAGE_KEYBOARD_l     (0x0F)
#define HID_USAGE_KEYBOARD_m     (0x10)
#define HID_USAGE_KEYBOARD_n     (0x11)
#define HID_USAGE_KEYBOARD_o     (0x12)
#define HID_USAGE_KEYBOARD_p     (0x13)
#define HID_USAGE_KEYBOARD_q     (0x14)
#define HID_USAGE_KEYBOARD_r     (0x15)
#define HID_USAGE_KEYBOARD_s     (0x16)
#define HID_USAGE_KEYBOARD_t     (0x17)
#define HID_USAGE_KEYBOARD_u     (0x18)
#define HID_USAGE_KEYBOARD_v     (0x19)
#define HID_USAGE_KEYBOARD_w     (0x1A)
#define HID_USAGE_KEYBOARD_x     (0x1B)
#define HID_USAGE_KEYBOARD_y     (0x1C)
#define HID_USAGE_KEYBOARD_z     (0x1D)

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
#define HID_USAGE_KEYBOARD_CAPS  (0x39)
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
#define HID_USAGE_KEYBOARD_RETRN (0x28)
#define HID_USAGE_KEYBOARD_ESC   (0x29)
#define HID_USAGE_KEYBOARD_BCKSP (0x2A)
#define HID_USAGE_KEYBOARD_TAB   (0x2B)
#define HID_USAGE_KEYBOARD_SPACE (0x2C)
#define HID_USAGE_KEYBOARD_PRSCR (0x46)
#define HID_USAGE_KEYBOARD_INSRT (0x49)
#define HID_USAGE_KEYBOARD_PGEUP (0x4B)
#define HID_USAGE_KEYBOARD_DELET (0x4C)
#define HID_USAGE_KEYBOARD_PGEDN (0x4E)

#endif /* __USB_HID_USAGES_H */
