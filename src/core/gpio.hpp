/**
 * @file      gpio.hpp
 * @brief     GPIO Control API
 *
 * @author    Anthony Needles
 * @date      2021/01/01
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Holds GPIO control API, for controlling GPIO pins in an object-oriented method.
 */

#ifndef CORE_GPIO_HPP_
#define CORE_GPIO_HPP_

#include "stm32f0xx.h"  // NOLINT

// TODO: remove
#include "util/macros.hpp"

// the gpio namespace holds enums for configuration options
namespace gpio {
    enum Port {
        #ifdef GPIOA_BASE
        A = GPIOA_BASE,
        #endif
        #ifdef GPIOB_BASE
        B = GPIOB_BASE,
        #endif
        #ifdef GPIOC_BASE
        C = GPIOC_BASE,
        #endif
        #ifdef GPIOD_BASE
        D = GPIOD_BASE,
        #endif
        #ifdef GPIOE_BASE
        E = GPIOE_BASE,
        #endif
        #ifdef GPIOF_BASE
        F = GPIOF_BASE,
        #endif
        #ifdef GPIOG_BASE
        G = GPIOG_BASE,
        #endif
        #ifdef GPIOH_BASE
        H = GPIOH_BASE,
        #endif
    };
    enum Pin {
        PIN_0  =  0,
        PIN_1  =  1,
        PIN_2  =  2,
        PIN_3  =  3,
        PIN_4  =  4,
        PIN_5  =  5,
        PIN_6  =  6,
        PIN_7  =  7,
        PIN_8  =  8,
        PIN_9  =  9,
        PIN_10 = 10,
        PIN_11 = 11,
        PIN_12 = 12,
        PIN_13 = 13,
        PIN_14 = 14,
        PIN_15 = 15,
    };
    enum Mode {
        INPUT  = 0x0,
        OUTPUT = 0x1,
        ALTFN  = 0x2,
        ANALOG = 0x3,
    };
    enum Pull {
        NO_PULL    = 0x0,
        PULL_UP    = 0x1,
        PULL_DOWN  = 0x2,
    };
    enum OutputType {
        PUSH_PULL  = 0x0,
        OPEN_DRAIN = 0x1,
    };
    enum AltFn {
        ALTFN_0 = 0x0,
        ALTFN_1 = 0x1,
        ALTFN_2 = 0x2,
        ALTFN_3 = 0x3,
        ALTFN_4 = 0x4,
        ALTFN_5 = 0x5,
        ALTFN_6 = 0x6,
        ALTFN_7 = 0x7,
    };
    enum OutputSpeed {
        LOW_SPEED  = 0x0,
        MED_SPEED  = 0x1,
        HIGH_SPEED = 0x3,
    };
    enum OutputState {
        CLR = 0x0,
        SET = 0x1,
    };
}  // namespace gpio

// struct template for each gpio pin. everything here should simply inline, and should produce
// exactly the same code as if we were using macros
template <gpio::Port port, gpio::Pin pin>
struct GPIOBase {
    static volatile GPIO_TypeDef *port_struct(void);
    static void enable_port_clock(void);
    static void set_mode(gpio::Mode mode);
    static void set_pull(gpio::Pull pull);
    static void set_output_type(gpio::OutputType type);
    static void set_altfn(gpio::AltFn afn);
    static void set_output_speed(gpio::OutputSpeed speed);
    static void clr_output(void);
    static void set_output(void);
    static void set_output_state(gpio::OutputState);
};

/**
 * @brief Convert template port value to port structure
 *
 * The template `port` input is the address of the GPIO structure defined in the CMSIS header. This
 * struct maps the GPIO registers for each port. This method will convert this address to the
 * structure.
 *
 * @return GPIO structure pointer
 */
template <gpio::Port port, gpio::Pin pin>
inline volatile GPIO_TypeDef *GPIOBase<port, pin>::port_struct(void)
{
    return reinterpret_cast<GPIO_TypeDef *>(port);
}

/**
 * @brief Enable the given port clock
 *
 * Unfortunately, there doesn't seem to be a good way to do this. Since pin clocks are usually only
 * set upon initialization, this is good enough.
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::enable_port_clock(void)
{
    RCC->AHBENR |=
        #ifdef GPIOA
        (port_struct() == GPIOA) ? RCC_AHBENR_GPIOAEN :
        #endif
        #ifdef GPIOB
        (port_struct() == GPIOB) ? RCC_AHBENR_GPIOBEN :
        #endif
        #ifdef GPIOC
        (port_struct() == GPIOC) ? RCC_AHBENR_GPIOCEN :
        #endif
        #ifdef GPIOD
        (port_struct() == GPIOD) ? RCC_AHBENR_GPIODEN :
        #endif
        #ifdef GPIOE
        (port_struct() == GPIOE) ? RCC_AHBENR_GPIOEEN :
        #endif
        #ifdef GPIOF
        (port_struct() == GPIOF) ? RCC_AHBENR_GPIOFEN :
        #endif
        #ifdef GPIOG
        (port_struct() == GPIOG) ? RCC_AHBENR_GPIOGEN :
        #endif
        #ifdef GPIOH
        (port_struct() == GPIOH) ? RCC_AHBENR_GPIOHEN :
        #endif
        0;
}

/**
 * @brief Set the GPIO mode
 *
 * A GPIO can be either an input, output, alternate function, or analog.
 *
 * @param[in] mode the mode option to set
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::set_mode(gpio::Mode mode)
{
    BITMASK_UPDATE(port_struct()->MODER, 0x3 << pin*2, mode << pin*2);
}

/**
 * @brief Set the GPIO pull
 *
 * A GPIO can have a pull up, pull down, or neither.
 *
 * @param[in] pull the pull option to set
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::set_pull(gpio::Pull pull)
{
    BITMASK_UPDATE(port_struct()->PUPDR, 0x3 << pin*2, pull << pin*2);
}

/**
 * @brief Set the GPIO output type
 *
 * A GPIO can be set to push/pull or open drain output.
 *
 * @param[in] type the output type option to set
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::set_output_type(gpio::OutputType type)
{
    BITMASK_UPDATE(port_struct()->OTYPER, 0x3 << pin*2, type  << pin*2);
}

/**
 * @brief Set the GPIO alternative function
 *
 * A GPIO can be set to any available alternate function, which is different for every pin.
 *
 * @param[in] afn the alternate function option to set
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::set_altfn(gpio::AltFn afn)
{
    BITMASK_UPDATE(port_struct()->AFR[pin < 8 ? 0 : 1], 0xF << (pin % 8)*4, afn << (pin % 8)*4);
}

/**
 * @brief Set the GPIO output speed
 *
 * A GPIO can have low, medium, or fast output.
 *
 * @param[in] speed the output speed option to set
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::set_output_speed(gpio::OutputSpeed speed)
{
    BITMASK_UPDATE(port_struct()->OSPEEDR, 0x3 << pin*2, speed << pin*2);
}

/**
 * @brief Clear the GPIO output
 *
 * The output state is set low.
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::clr_output(void)
{
    port_struct()->ODR &= ~(1 << pin);
}

/**
 * @brief Set the GPIO output
 *
 * The output state is set high.
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::set_output(void)
{
    port_struct()->ODR |=  (1 << pin);
}

/**
 * @brief Set the GPIO output state
 *
 * Either set or clear the GPIO state. If the desired state is known at compile-time, `set_output`
 * or `clr_output` should be used instead.
 */
template <gpio::Port port, gpio::Pin pin>
inline void GPIOBase<port, pin>::set_output_state(gpio::OutputState state)
{
    BITMASK_UPDATE(port_struct()->ODR, 0x1 << pin, state << pin);
}

#endif  // CORE_GPIO_HPP_
