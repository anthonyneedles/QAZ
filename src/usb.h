/**
 * @file      usb.c
 * @brief     USB driver
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * This module interfaces with the USB peripheral to establish basic USB HID communications with
 * host.
 *
 * Endpoint 0 -> Control
 * Endpoint 1 -> Interrupt, TX only
 */

#ifndef __USB_H
#define __USB_H

/*
 * USBInit
 *
 * @brief: Performs USB port, clock, and peripheral initialization
 *
 * USB port is used in startup (for DFU), so the ports come up configured. Host detects device upon
 * DP pullup enable.
 */
void USBInit(void);

/*
 * USB_IRQHandler
 *
 * @brief Handle USB events
 *
 * Routes module function based on received interrupts. Most are ignored, except RESET and CTR.
 */
void USB_IRQHandler(void);

#endif /* __USB_H */
