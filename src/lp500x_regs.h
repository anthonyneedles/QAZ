/**
 * @file    lp500x_regs.h
 * @author  Anthony Needles
 * @date    2020/10/31
 * @brief   LP500x LED Driver RGB regiser map
 */

#ifndef __LP500X_REGS_H_
#define __LP500X_REGS_H_

#define DEVICE_CONFIG0_R       (0x00)
#define   CHIP_EN                (0x40)
#define DEVICE_CONFIG1_R       (0x01)
#define   LOG_SCALE_EN           (0x20)
#define   POWER_SAVE_EN          (0x10)
#define   AUTO_INCR_EN           (0x08)
#define   PWM_DITHER_EN          (0x04)
#define   MAX_CURR_35MA          (0x02)
#define   MAX_CURR_25MA          (0x00)
#define   LED_GLOBAL_OFF         (0x01)
#define LED_CONFIG0_R          (0x02)
#define   LED3_BANK_EN           (0x08)
#define   LED2_BANK_EN           (0x04)
#define   LED1_BANK_EN           (0x02)
#define   LED0_BANK_EN           (0x01)
#define BANK_BRIGHTNESS_R      (0x03)
#define BANK_A_COLOR_R         (0x04)
#define BANK_B_COLOR_R         (0x05)
#define BANK_C_COLOR_R         (0x06)
#define LED0_BRIGHTNESS_R      (0x07)
#define LED1_BRIGHTNESS_R      (0x08)
#define LED2_BRIGHTNESS_R      (0x09)
#define LED3_BRIGHTNESS_R      (0x0A)
#define OUT0_COLOR_R           (0x0B)
#define OUT1_COLOR_R           (0x0C)
#define OUT2_COLOR_R           (0x0D)
#define OUT3_COLOR_R           (0x0E)
#define OUT4_COLOR_R           (0x0F)
#define OUT5_COLOR_R           (0x10)
#define OUT6_COLOR_R           (0x11)
#define OUT7_COLOR_R           (0x12)
#define OUT8_COLOR_R           (0x13)
#define OUT9_COLOR_R           (0x14)
#define OUT10_COLOR_R          (0x15)
#define OUT11_COLOR_R          (0x16)
#define RESET_R                (0x17)

#endif /* __LP500X_REGS_H_ */
