/**
 * @file      uart.c
 * @brief     UART driver
 *
 * @author    Anthony Needles
 * @date      2020/12/21
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This source file handles all UART communications. Configured for 115200 baud.
 *
 * Assumes SYSCLK = 48MHz
 */

#include "comms/uart.h"

#include "util/debug.h"
#include "util/macros.h"

#define BAUD_115200 0x1A1

/**
 * @brief Enables USART for TX at 115200 baud, 8-N-1.
 *
 * @param[in] uart handle for uart to init
 * @return UART_SUCCCESS - successfully initialized uart
 *         UART_FAILURE  - failed uart init (already initialized)
 */
uart_status_t UARTInit(uart_handle_t *uart)
{
    if (!uart) {
        DBG_ASSERT(FORCE_ASSERT);
        return UART_FAILURE;
    }

    if (uart->state != UART_RESET) {
        DbgPrintf("UART init error, not in UART_RESET (%p)\r\n", uart->regs);
        return UART_FAILURE;
    }

    // Enable clock for given USART
    if (uart->regs == USART1) {
        SET(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
    } else {
        DBG_ASSERT(FORCE_ASSERT);
        return UART_FAILURE;
    }

    // Enable transmitting
    uart->regs->CR1 = USART_CR1_TE;

    // Set baudrate to 115200
    uart->regs->BRR = BAUD_115200;

    // Enable USART1
    SET(uart->regs->CR1, USART_CR1_UE);

    uart->state = UART_READY;

    return UART_SUCCESS;
}

/**
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
uart_status_t UARTWriteBlocking(uart_handle_t *uart, const char *data, int n)
{
    if (!uart || !data || (n <= 0)) {
        DBG_ASSERT(FORCE_ASSERT);
        return UART_FAILURE;
    }

    if (uart->state != UART_READY) {
        DbgPrintf("UART write error, not in UART_READY (%p)\r\n", uart->regs);
        return UART_FAILURE;
    }

    for (int i = 0; i < n; ++i) {
        while (BIT_READ(uart->regs->ISR, USART_ISR_TXE_Pos) != 1) {}
        uart->regs->TDR = data[i];
    }

    return UART_SUCCESS;
}
