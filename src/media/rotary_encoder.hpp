/**
 * @file      rotary_encoder.hpp
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

#ifndef MEDIA_ROTARY_ENCODER_HPP_
#define MEDIA_ROTARY_ENCODER_HPP_

/**
 * @brief Rotary Encoder namespace
 *
 * This namespace pertains to the reading of the rotary encoder.
 */
namespace rotary_encoder {

/// Inits TIM3 in encoder mode for reading rotary encoder
void init(void);

/// Reads rotary encoder values
void task(void);

}  // namespace rotary_encoder

#endif  // MEDIA_ROTARY_ENCODER_HPP_
