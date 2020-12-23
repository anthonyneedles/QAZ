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

    // Enable clock for GPIOA and USART1
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // Set debug tx port into alt function mode
    GPIOA->MODER = ((GPIOA->MODER & ~GPIO_MODER_MODER9_Msk) | GPIO_MODER_MODER9_1);

    // Set alternate function 1 (USART1_TX)
    GPIOA->AFR[1] = ((GPIOA->AFR[1] & ~GPIO_AFRH_AFSEL9_Msk) | (1UL << GPIO_AFRH_AFSEL9_Pos));

    // Set pullup
    GPIOA->PUPDR = ((GPIOA->PUPDR  & ~GPIO_PUPDR_PUPDR9_Msk) | GPIO_PUPDR_PUPDR9_0);

    // Fast output
    GPIOA->OSPEEDR = ((GPIOA->OSPEEDR  & ~GPIO_OSPEEDR_OSPEEDR9_Msk)
            | GPIO_OSPEEDR_OSPEEDR9);

    // Enable transmitting
    uart->regs->CR1 = USART_CR1_TE;

    // Set baudrate to 115200
    uart->regs->BRR = 0x1A1;

    // Enable USART1
    uart->regs->CR1 |= USART_CR1_UE;

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
        while ((uart->regs->ISR & USART_ISR_TXE) == 0);
        uart->regs->TDR = data[i];
    }

    return UART_SUCCESS;
}
