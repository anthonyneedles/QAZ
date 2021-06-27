/**
 * @file      buttons.hpp
 * @brief     Implements button debouncing
 *
 * @author    Anthony Needles
 * @date      2021/06/25
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Each button must be set up in a low-side switch configuration. When a button is validated as
 * pressed, a callback is called for performing a desired action.
 */

#ifndef QAZ_BUTTONS_HPP_
#define QAZ_BUTTONS_HPP_

#include "bsp/bsp.hpp"

/**
 * @brief Buttons namespace
 *
 * This namespace pertains to the debouncing of discrete buttons.
 */
namespace buttons {

// the status of a buttons routine
enum Status {
    SUCCESS,
    FAILURE,
};

/// initializes button inputs and button controls
void init(void);

/// Runs debounce routine for all buttons
void task(void);

/// Set a callback for a button, fails is callback already exists
Status set_callback(bsp::ButtonId id, void (*cb)(void));

}  // namespace buttons

#endif  // QAZ_BUTTONS_HPP_
