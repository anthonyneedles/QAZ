/**
 * @file      lp500x_regs.hpp
 * @brief     LP500x LED Driver RGB register map
 *
 * @author    Anthony Needles
 * @date      2020/10/31
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#ifndef LP500X_LP500X_REGS_HPP_
#define LP500X_LP500X_REGS_HPP_

#include <cstdint>

/**
 * @brief LP500x namespace
 *
 * This namespace holds both the utility functions for controlling the LP500x external device (via
 * I2C), as well as the registers for that device.
 */
namespace lp500x {

inline constexpr uint8_t DEVICE_CONFIG0_R  = 0x00;
inline constexpr uint8_t   CHIP_EN         =  0x40;
inline constexpr uint8_t DEVICE_CONFIG1_R  = 0x01;
inline constexpr uint8_t   LOG_SCALE_EN    =  0x20;
inline constexpr uint8_t   POWER_SAVE_EN   =  0x10;
inline constexpr uint8_t   AUTO_INCR_EN    =  0x08;
inline constexpr uint8_t   PWM_DITHER_EN   =  0x04;
inline constexpr uint8_t   MAX_CURR_35MA   =  0x02;
inline constexpr uint8_t   MAX_CURR_25MA   =  0x00;
inline constexpr uint8_t   LED_GLOBAL_OFF  =  0x01;
inline constexpr uint8_t LED_CONFIG0_R     = 0x02;
inline constexpr uint8_t   LED3_BANK_EN    =  0x08;
inline constexpr uint8_t   LED2_BANK_EN    =  0x04;
inline constexpr uint8_t   LED1_BANK_EN    =  0x02;
inline constexpr uint8_t   LED0_BANK_EN    =  0x01;
inline constexpr uint8_t BANK_BRIGHTNESS_R = 0x03;
inline constexpr uint8_t BANK_A_COLOR_R    = 0x04;
inline constexpr uint8_t BANK_B_COLOR_R    = 0x05;
inline constexpr uint8_t BANK_C_COLOR_R    = 0x06;
inline constexpr uint8_t LED0_BRIGHTNESS_R = 0x07;
inline constexpr uint8_t LED1_BRIGHTNESS_R = 0x08;
inline constexpr uint8_t LED2_BRIGHTNESS_R = 0x09;
inline constexpr uint8_t LED3_BRIGHTNESS_R = 0x0A;
inline constexpr uint8_t OUT0_COLOR_R      = 0x0B;
inline constexpr uint8_t OUT1_COLOR_R      = 0x0C;
inline constexpr uint8_t OUT2_COLOR_R      = 0x0D;
inline constexpr uint8_t OUT3_COLOR_R      = 0x0E;
inline constexpr uint8_t OUT4_COLOR_R      = 0x0F;
inline constexpr uint8_t OUT5_COLOR_R      = 0x10;
inline constexpr uint8_t OUT6_COLOR_R      = 0x11;
inline constexpr uint8_t OUT7_COLOR_R      = 0x12;
inline constexpr uint8_t OUT8_COLOR_R      = 0x13;
inline constexpr uint8_t OUT9_COLOR_R      = 0x14;
inline constexpr uint8_t OUT10_COLOR_R     = 0x15;
inline constexpr uint8_t OUT11_COLOR_R     = 0x16;
inline constexpr uint8_t RESET_R           = 0x17;

}  // namespace lp500x

#endif  // LP500X_LP500X_REGS_HPP_
