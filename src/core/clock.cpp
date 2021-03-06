/**
 * @file      clock.cpp
 * @brief     System clock initialization
 *
 * @author    Anthony Needles
 * @date      2020/10/12
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Holds any user clock configuration that should be applied before any other user initialization
 * or project execution.
 */

#include "core/clock.hpp"

#include "bsp/bsp.hpp"
#include "util/bitop.hpp"
#include "stm32f0xx.h"  // NOLINT

/**
 * @brief Init system clock
 *
 * Enable and switch system clock over to using HSE and PLL to result in 48MHz SYSCLK.
 * Also, set MCO to PA8, so that we can scope the SYSCLK. Assumes 8MHz external crystal.
 */
void clock::init(void)
{
    // enable Clock Security System and High Speed External clock
    bitop::set_msk(RCC->CR, RCC_CR_CSSON | RCC_CR_HSEON);

    // wait until HSE oscillator is stable (~512 HSE clock pulses)
    while (bitop::read_bit(RCC->CR, RCC_CR_HSERDY_Pos) != 1) {}

    // set system clock mux to HSE (SYSCLK is now 8MHz)
    bitop::update_msk(RCC->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSE);

    // turn PLL off to change parameters
    bitop::clr_msk(RCC->CR, RCC_CR_PLLON);

    // wait until PLL is unlocked (off)
    while (bitop::read_bit(RCC->CR, RCC_CR_PLLRDY_Pos) == 1) {}

    // set PLL multiplication factor to 6 (6 x 8Mhz = 48MHz) MUST NOT EXCEED 6!
    // select HSE as PLL source
    bitop::update_msk(RCC->CFGR, RCC_CFGR_PLLMUL_Msk | RCC_CFGR_PLLSRC_Msk,
            RCC_CFGR_PLLMUL6 | RCC_CFGR_PLLSRC_HSE_PREDIV);

    // turn PLL on as parameters are changed
    bitop::set_msk(RCC->CR, RCC_CR_PLLON);

    // wait until PLL is locked (on)
    while (bitop::read_bit(RCC->CR, RCC_CR_PLLRDY_Pos) != 1) {}

    // set system clock mux to PLL (SYSCLK is now 48MHz)
    bitop::update_msk(RCC->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_PLL);

    // enable Prefetch Buffer and set Flash latency
    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

    // select SYSCLK as MCO output
    bitop::update_msk(RCC->CFGR, RCC_CFGR_MCO_Msk, RCC_CFGR_MCO_SYSCLK);

    // enable MCO pin clock, set to alternate function 0, high speed
    gpio::enable_port_clock(bsp::MCO);
    gpio::set_mode(bsp::MCO, gpio::ALTFN);
    gpio::set_altfn(bsp::MCO, gpio::ALTFN_0);
    gpio::set_output_speed(bsp::MCO, gpio::HIGH_SPEED);
}
