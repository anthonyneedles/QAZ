/**
 * @file      IS31FL3746A_regs.hpp
 * @brief     IS31FL3746A LED Driver RGB register map
 *
 * @author    Anthony Needles
 * @date      2021/05/17
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 */

#ifndef IS31FL3746A_IS31FL3746A_REGS_HPP_
#define IS31FL3746A_IS31FL3746A_REGS_HPP_

#include <cstdint>

/**
 * @brief IS31FL3746A reg namespace
 *
 * This namespace holds both the utility functions for controlling the IS31FL3746A external device
 * (via I2C), as well as the registers for that device.
 */
namespace is31fl3746a::reg {

// page 0 registers
inline constexpr uint8_t LED_PWM_START_R        = 0x01;
// for page 0, registers 0x01-0x48 corresponds to LED_PWM for LEDs 0x01-0x048

// page 1 registers
inline constexpr uint8_t LED_SCALE_START_R      = 0x01;
// for page 1, registers 0x01-0x48 corresponds to LED_SCALE for LEDs 0x01-0x048
inline constexpr uint8_t CONFIGURATION_R        = 0x50;
inline constexpr uint8_t   SWX_SETTING_MSK      =   0xF0;
inline constexpr uint8_t   SWX_SETTING_SH       =   4;
inline constexpr uint8_t   SWX_SW1_THRU_SW4     =   0x00;
inline constexpr uint8_t   SWX_SW1_THRU_SW3     =   0x01;
inline constexpr uint8_t   SWX_SW1_THRU_SW2     =   0x02;
inline constexpr uint8_t   SWX_ALL_CSY_SINK     =   0x03;
inline constexpr uint8_t   OS_DETECTION_MSK     =   0x06;
inline constexpr uint8_t   OS_DETECTION_SH      =   1;
inline constexpr uint8_t   OS_DET_DISABLE       =   0x00;
inline constexpr uint8_t   OPEN_DET_ENABLE      =   0x01;
inline constexpr uint8_t   CLOSE_DET_ENABLE     =   0x02;
inline constexpr uint8_t   SW_NORMAL_OPERATION  =   0x01;
inline constexpr uint8_t   SW_SHUTDOWN          =   0x00;
inline constexpr uint8_t GBL_CURRENT_CTRL_R     = 0x51;
inline constexpr uint8_t PULL_UP_DOWN__R        = 0x52;
inline constexpr uint8_t   PHASE_DELAY_180      =   0x80;
inline constexpr uint8_t   SWX_PDR_MSK          =   0x70;
inline constexpr uint8_t   SWX_PDR_SH           =   4;
inline constexpr uint8_t   SWX_PDR_NONE         =   0x00;
inline constexpr uint8_t   SWX_PDR_0_5K_OFFTIME =   0x01;
inline constexpr uint8_t   SWX_PDR_1K_OFFTIME   =   0x02;
inline constexpr uint8_t   SWX_PDR_2K_OFFTIME   =   0x03;
inline constexpr uint8_t   SWX_PDR_1K_ALWAYS    =   0x04;
inline constexpr uint8_t   SWX_PDR_2K_ALWAYS    =   0x05;
inline constexpr uint8_t   SWX_PDR_4K_ALWAYS    =   0x06;
inline constexpr uint8_t   SWX_PDR_8K_ALWAYS    =   0x07;
inline constexpr uint8_t   CSY_PUR_MSK          =   0x07;
inline constexpr uint8_t   CSY_PUR_SH           =   0;
inline constexpr uint8_t   CSY_PUR_NONE         =   0x00;
inline constexpr uint8_t   CSY_PUR_0_5K_OFFTIME =   0x01;
inline constexpr uint8_t   CSY_PUR_1K_OFFTIME   =   0x02;
inline constexpr uint8_t   CSY_PUR_2K_OFFTIME   =   0x03;
inline constexpr uint8_t   CSY_PUR_1K_ALWAYS    =   0x04;
inline constexpr uint8_t   CSY_PUR_2K_ALWAYS    =   0x05;
inline constexpr uint8_t   CSY_PUR_4K_ALWAYS    =   0x06;
inline constexpr uint8_t   CSY_PUR_8K_ALWAYS    =   0x07;
inline constexpr uint8_t OPEN_SHORT_START_R     = 0x53;
inline constexpr uint8_t TEMP_STATUS_R          = 0x5F;
inline constexpr uint8_t   TEMP_ROLLOFF_MSK     =   0x0C;
inline constexpr uint8_t   TEMP_ROLLOFF_SH      =   2;
inline constexpr uint8_t   TEMP_ROLLOFF_140C    =   0x00;
inline constexpr uint8_t   TEMP_ROLLOFF_120C    =   0x01;
inline constexpr uint8_t   TEMP_ROLLOFF_100C    =   0x02;
inline constexpr uint8_t   TEMP_ROLLOFF_90C     =   0x03;
inline constexpr uint8_t   CURRENT_DROP_MSK     =   0x0C;
inline constexpr uint8_t   CURRENT_DROP_SH      =   0;
inline constexpr uint8_t   CURRENT_DROP_100     =   0x00;
inline constexpr uint8_t   CURRENT_DROP_75      =   0x01;
inline constexpr uint8_t   CURRENT_DROP_55      =   0x02;
inline constexpr uint8_t   CURRENT_DROP_30      =   0x03;
inline constexpr uint8_t SPREAD_SPECTRUM_R      = 0x60;
inline constexpr uint8_t   SS_FUNCTION_EN       =   0x10;
inline constexpr uint8_t   SS_RANGE_MSK         =   0xC0;
inline constexpr uint8_t   SS_RANGE_SH          =   2;
inline constexpr uint8_t   SS_RANGE_5           =   0x00;
inline constexpr uint8_t   SS_RANGE_15          =   0x01;
inline constexpr uint8_t   SS_RANGE_24          =   0x02;
inline constexpr uint8_t   SS_RANGE_34          =   0x03;
inline constexpr uint8_t   SS_CYCLE_MSK         =   0xC0;
inline constexpr uint8_t   SS_CYCLE_SH          =   0;
inline constexpr uint8_t   SS_CYCLE_1980US      =   0x00;
inline constexpr uint8_t   SS_CYCLE_1200US      =   0x01;
inline constexpr uint8_t   SS_CYCLE_820US       =   0x02;
inline constexpr uint8_t   SS_CYCLE_660US       =   0x03;
inline constexpr uint8_t RESET_R                = 0x8F;
inline constexpr uint8_t   RESET_CODE           =   0xAE;
inline constexpr uint8_t PWM_FREQ_EN_R          = 0xE0;
inline constexpr uint8_t   PWM_EN               =   0x01;
inline constexpr uint8_t PWM_FREQ_SETTING_R     = 0xE2;
inline constexpr uint8_t   PWM_FREQ_MSK         =   0xE0;
inline constexpr uint8_t   PWM_FREQ_SH          =   5;
inline constexpr uint8_t   PWM_FREQ_29KHZ       =   0x00;
inline constexpr uint8_t   PWM_FREQ_14_5KHZ     =   0x01;
inline constexpr uint8_t   PWM_FREQ_7_25KHZ     =   0x02;
inline constexpr uint8_t   PWM_FREQ_3_63KHZ     =   0x03;
inline constexpr uint8_t   PWM_FREQ_1_81KHZ     =   0x04;
inline constexpr uint8_t   PWM_FREQ_906HZ       =   0x05;
inline constexpr uint8_t   PWM_FREQ_453HZ       =   0x06;

// page 0 & 1 registers
inline constexpr uint8_t ID_R                   = 0xFC;
inline constexpr uint8_t PAGE_SEL_R             = 0xFD;
inline constexpr uint8_t   PAGE_0               =   0x00;
inline constexpr uint8_t   PAGE_1               =   0x01;
inline constexpr uint8_t PAGE_SEL_WR_LOCK_R     = 0xFE;
inline constexpr uint8_t   UNLOCK_CODE          =   0xC5;

}  // namespace is31fl3746a::reg

#endif  // IS31FL3746A_IS31FL3746A_REGS_HPP_
