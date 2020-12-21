/**
 * @file      uart.c
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

#include "comms/i2c.h"

#include "stm32f0xx.h"

#include "util/debug.h"

/**
 * UARTInit
 *
 * @brief Enables USART1 for TX at 115200 on pin PA9.
 *
 * PA9 = TX, PA10 = RX. Only using TX for now.
 */
void UARTInit(void)
{
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
    USART1->CR1 = USART_CR1_TE;

    // Set baudrate to 115200
    USART1->BRR = 0x1A1;

    // Enable USART1
    USART1->CR1 |= USART_CR1_UE;

    DbgPrintf("Initialized: UART\r\n");
}

/**
 * UARTWriteBlocking
 *
 * @brief Sends data over USART1, blocking
 *
 * Blocks until USART1 is ready to transmit, then pushes character onto output buffer.
 */
void UARTWriteBlocking(const uint8_t *data, int n)
{
    DBG_ASSERT(data);

    for (int i = 0; i < n; ++i) {
        while ((USART1->ISR & USART_ISR_TXE) == 0);
        USART1->TDR = data[i];
    }
}
