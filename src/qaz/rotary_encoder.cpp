/**
 * @file      rotary_encoder.cpp
 * @brief     Implements reading of rotary encoder
 *
 * @author    Anthony Needles
 * @date      2021/06/26
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Rotary encoders can be read with the timer peripherals, when put into encoder mode.
 *
 * TIM3 is used to read the rotary encoder, using TIM3 CH1 and CH2. The CNT register is reset after
 * each read, so the value we read is a relative change in position, rather than an absolute one.
 */

#include "qaz/rotary_encoder.hpp"

#include "bsp/bsp.hpp"
#include "core/gpio.hpp"
#include "core/time_slice.hpp"
#include "util/bitop.hpp"
#include "util/debug.hpp"
#include "stm32f0xx.h"  // NOLINT

namespace {

/// Task fuction will execute every 50ms
constexpr unsigned ROT_ENC_TASK_PERIOD_MS = 50;

}  // namespace

/**
 * @brief Initializes rotary encoder reading via TIM3
 *
 * We read our rotary encoder using TIM3 CH1 and CH2. TIM3 is put into encoder mode and set to
 * increment on both TI1 and TI2 (CH1 and CH2 input).
 */
void rotary_encoder::init(void)
{
    // enable clock to TIM3 peripheral
    bitop::set_msk(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);

    // set both rotary encoder channels to ALTFN1 (TIM3_CH1/TIM3_CH2)
    gpio::enable_port_clock(bsp::ROT_ENC_A);
    gpio::set_mode(bsp::ROT_ENC_A, gpio::ALTFN);
    gpio::set_altfn(bsp::ROT_ENC_A, gpio::ALTFN_1);
    gpio::enable_port_clock(bsp::ROT_ENC_B);
    gpio::set_mode(bsp::ROT_ENC_B, gpio::ALTFN);
    gpio::set_altfn(bsp::ROT_ENC_B, gpio::ALTFN_1);

    // set our timer in encoder mode, counting on input 1/2 (SMS = 0b001)
    bitop::update_msk(TIM3->SMCR,  TIM_SMCR_SMS_Msk,   TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1);

    // input channel 1/2 is mapped to encoder incoder input 1/2. no inversion on either
    bitop::update_msk(TIM3->CCMR1, TIM_CCMR1_CC1S_Msk, TIM_CCMR1_CC1S_0);
    bitop::update_msk(TIM3->CCMR1, TIM_CCMR1_CC2S_Msk, TIM_CCMR1_CC2S_0);

    // we count from 0 - 0xFFFF, so -32768 to 32767 if we interpret the count as an int16
    TIM3->ARR = 0xFFFF;

    // enable the timer
    bitop::set_msk(TIM3->CR1, TIM_CR1_CEN);

    auto stat2 = timeslice::register_task(ROT_ENC_TASK_PERIOD_MS, rotary_encoder::task);
    DBG_ASSERT(stat2 == timeslice::SUCCESS);

    debug::puts("Initialized: Rotary Encoder\r\n");
}

/**
 * @brief Read our encoder input
 *
 * The count register will hold a value that corresponds with the movement since the last sample,
 * since we write the count register with 0 after every sample.
 *
 * Positive values correspond with clockwise rotation, and negative with counter clockwise rotation.
 */
void rotary_encoder::task(void)
{
    TIM3->CNT = 0;
}
