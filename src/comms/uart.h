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

#include "stm32f0xx.h"

// status code returned by UART API
typedef enum {
    UART_SUCCESS,
    UART_FAILURE,
} uart_status_t;

// state of a given UART instance
typedef enum {
    UART_RESET = 0,
    UART_READY,
} uart_state_t;

// handle for a UART instance, holds control information
typedef struct {
    USART_TypeDef *regs;
    uart_state_t state;
} uart_handle_t;

/**
 * UARTInit
 *
 * @brief Enables USART for TX at 115200 baud, 8-N-1.
 *
 * @param[in] uart handle for uart to init
 * @return UART_SUCCCESS - successfully initialized uart
 *         UART_FAILURE  - failed uart init (already initialized)
 */
uart_status_t UARTInit(uart_handle_t *uart);

/**
 * UARTWriteBlocking
 *
 * @brief Sends data over USART, blocking on write ready
 *
 * Blocks until USART is ready to transmit, then pushes character onto output buffer.
 *
 * @param[in] uart handle for uart to write with
 * @param[in] data buffer to transmit
 * @param[in] n    number of bytes to transmit
 * @return UART_SUCCCESS - successful uart write
 *         UART_FAILURE  - failed uart write (not ready, invalid buf)
 */
uart_status_t UARTWriteBlocking(uart_handle_t *uart, const char *data, int n);

#endif /* __COMMS_UART_H_ */
