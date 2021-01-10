/**
 * @file      comm_base.hpp
 * @brief     Base Communications
 *
 * @author    Anthony Needles
 * @date      2021/01/04
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Defines the base class that communications should be derived from.
 */

#ifndef COMM_COMM_BASE_HPP_
#define COMM_COMM_BASE_HPP_

#include <cstdint>

/**
 * @brief Communication namespace
 *
 * Holds values useful for all communications.
 */
namespace comm {

/// Status return codes
enum Status {
    SUCCESS,
    FAILURE,
};

/// State of the communication driver
enum State {
    RESET,
    READY,
};

}  // namespace comm

/**
 * @brief Communication base class
 *
 * A "template" for communication API that all derived classes must individually implement, in an
 * attempt to keep a consistent read/write API.
 */
class CommBase {
 public:
    /// The communication initializer (peripheral init, prepare buffers, etc.)
    virtual comm::Status init(void) = 0;

    /// Write raw bytes, can block between writes (e.g. waiting for a register flag)
    virtual comm::Status write_blocking(const std::uint8_t *data, unsigned nbytes) = 0;
};

#endif  // COMM_COMM_BASE_HPP_
