/**
 * @file      clock.c
 * @brief     System clock initialization
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Holds any user clock configuration that should be applied before any other user initialization
 * or project execution. 
 */

#include "core/clock.h"

#include "stm32f0xx.h"  // NOLINT

/**
 * @brief Init system clock
 *
 * Enable and switch system clock over to using HSE and PLL to result in 48MHz SYSCLK.
 * Also, set MCO to PA8, so that we can scope the SYSCLK. Assumes 8MHz external crystal.
 */
void ClockInit(void)
{
    // enable Clock Security System and High Speed External clock
    RCC->CR |= (RCC_CR_CSSON | RCC_CR_HSEON);

    // wait until HSE oscillator is stable (~512 HSE clock pulses)
    while ((RCC->CR & RCC_CR_HSERDY_Msk) != RCC_CR_HSERDY) {}

    // set system clock mux to HSE (SYSCLK is now 8MHz)
    RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW_Msk) | RCC_CFGR_SW_HSE);

    // turn PLL off to change parameters
    RCC->CR &= ~RCC_CR_PLLON;

    // wait until PLL is unlocked (off)
    while ((RCC->CR & RCC_CR_PLLRDY_Msk) == RCC_CR_PLLRDY) {}

    // set PLL multiplication factor to 6 (6 x 8Mhz = 48MHz) MUST NOT EXCEED 6!
    // select HSE as PLL source
    RCC->CFGR = ((RCC->CFGR & ~(RCC_CFGR_PLLMUL_Msk | RCC_CFGR_PLLSRC_Msk))
            | RCC_CFGR_PLLMUL6
            | RCC_CFGR_PLLSRC_HSE_PREDIV);

    // turn PLL on as parameters are changed
    RCC->CR |= RCC_CR_PLLON;

    // wait until PLL is locked (on)
    while ((RCC->CR & RCC_CR_PLLRDY_Msk) != RCC_CR_PLLRDY){}

    // set system clock mux to PLL (SYSCLK is now 48MHz)
    RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW_Msk) | RCC_CFGR_SW_PLL);

    // enable Prefetch Buffer and set Flash latency
    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

    // select SYSCLK as MCO output
    RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_MCO_Msk) | RCC_CFGR_MCO_SYSCLK);

    // enable GPIOA clock (MCO pin used is PA8)
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIOA->MODER |= GPIO_MODER_MODER8_0;

    // set MCO pin to alternate function
    GPIOA->MODER = ((GPIOA->MODER & ~GPIO_MODER_MODER8_Msk)
            | (2UL << GPIO_MODER_MODER8_Pos));

    // set for high speed
    GPIOA->OSPEEDR = ((GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEEDR8_Msk)
            | (3UL << GPIO_OSPEEDR_OSPEEDR8_Pos));

    // set MCO pin to alternate function 0 (MCO)
    GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL8_Msk;
}
