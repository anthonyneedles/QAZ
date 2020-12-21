/**
 * @file      uart.h
 * @brief     UART driver
 *
 * @author    Anthony Needles
 * @date      2020/12/21
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * This source file handles all UART communications. Configured for 115200 baud.
 *
 * Assumes SYSCLK = 48MHz
 */

#ifndef __COMMS_UART_H_
#define __COMMS_UART_H_

#include <stdint.h>

/**
 * UARTInit
 *
 * @brief Enables USART1 for TX at 115200 on pin PA9.
 *
 * PA9 = TX, PA10 = RX. Only using TX for now.
 */
void UARTInit(void);

/**
 * UARTWriteBlocking
 *
 * @brief Sends data over USART1, blocking
 *
 * Blocks until USART1 is ready to transmit, then pushes character onto output buffer.
 */
void UARTWriteBlocking(const char *data, int n);

#endif /* __COMMS_UART_H_ */
