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

#include "util/bitop.hpp"
#include "stm32f0xx.h"  // NOLINT

// the gpio namespace holds enums for configuration options
namespace gpio {

// port enums set to the base address for port registers
enum Port : uint32_t {
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

// pins for each gpio port (may need to be port-specific?)
enum Pin : uint32_t {
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

// modes in MODER register
enum Mode : uint32_t {
    INPUT  = 0x0,
    OUTPUT = 0x1,
    ALTFN  = 0x2,
    ANALOG = 0x3,
};

// pulls in PUPDR register
enum Pull : uint32_t {
    NO_PULL    = 0x0,
    PULL_UP    = 0x1,
    PULL_DOWN  = 0x2,
};

// output types in OTYPER register
enum OutputType : uint32_t {
    PUSH_PULL  = 0x0,
    OPEN_DRAIN = 0x1,
};

// alternate functions in AFL/AFH registers
enum AltFn : uint32_t {
    ALTFN_0 = 0x0,
    ALTFN_1 = 0x1,
    ALTFN_2 = 0x2,
    ALTFN_3 = 0x3,
    ALTFN_4 = 0x4,
    ALTFN_5 = 0x5,
    ALTFN_6 = 0x6,
    ALTFN_7 = 0x7,
};

// output speeds in OSPEEDR register
enum OutputSpeed : uint32_t {
    LOW_SPEED  = 0x0,
    MED_SPEED  = 0x1,
    HIGH_SPEED = 0x3,
};

// output/input states in ODR/IDR registers
enum PinState : uint32_t {
    CLR = 0x0,
    SET = 0x1,
};

// identification structure for each gpio pin
struct Id {
    Port port;
    Pin  pin;
};

}  // namespace gpio

/**
 * @brief Base gpio struct template
 *
 * Struct template for each gpio pin. Everything here should simply inline, and should produce
 * exactly the same code as if we were using macros
 */
struct GPIO {
    static volatile GPIO_TypeDef *regs(gpio::Id id);
    static void enable_port_clock(gpio::Id id);
    static void set_mode(gpio::Id, gpio::Mode mode);
    static void set_pull(gpio::Id, gpio::Pull pull);
    static void set_output_type(gpio::Id, gpio::OutputType type);
    static void set_altfn(gpio::Id, gpio::AltFn afn);
    static void set_output_speed(gpio::Id, gpio::OutputSpeed speed);
    static void clr_output(gpio::Id);
    static void set_output(gpio::Id);
    static void set_output_state(gpio::Id, gpio::PinState);
    static gpio::PinState read_input(gpio::Id);
};

/**
 * @brief Convert template port value to port structure
 *
 * The template `TPort` input is the address of the GPIO structure defined in the CMSIS header. This
 * struct maps the GPIO registers for each port. This method will convert this address to the
 * structure.
 *
 * @param[in] id   identification for gpio
 * @return    gpio structure pointer
 */
inline volatile GPIO_TypeDef *GPIO::regs(gpio::Id id)
{
    return reinterpret_cast<GPIO_TypeDef *>(id.port);
}

/**
 * @brief Enable the given port clock
 *
 * Unfortunately, there doesn't seem to be a good way to do this. Since pin clocks are usually only
 * set upon initialization, this is good enough.
 *
 * @param[in] id identification for gpio
 */
inline void GPIO::enable_port_clock(gpio::Id id)
{
    bitop::set_msk(RCC->AHBENR,
        #ifdef GPIOA
        (regs(id) == GPIOA) ? RCC_AHBENR_GPIOAEN :
        #endif
        #ifdef GPIOB
        (regs(id) == GPIOB) ? RCC_AHBENR_GPIOBEN :
        #endif
        #ifdef GPIOC
        (regs(id) == GPIOC) ? RCC_AHBENR_GPIOCEN :
        #endif
        #ifdef GPIOD
        (regs(id) == GPIOD) ? RCC_AHBENR_GPIODEN :
        #endif
        #ifdef GPIOE
        (regs(id) == GPIOE) ? RCC_AHBENR_GPIOEEN :
        #endif
        #ifdef GPIOF
        (regs(id) == GPIOF) ? RCC_AHBENR_GPIOFEN :
        #endif
        #ifdef GPIOG
        (regs(id) == GPIOG) ? RCC_AHBENR_GPIOGEN :
        #endif
        #ifdef GPIOH
        (regs(id) == GPIOH) ? RCC_AHBENR_GPIOHEN :
        #endif
        0);
}

/**
 * @brief Set the GPIO mode
 *
 * A GPIO can be either an input, output, alternate function, or analog.
 *
 * @param[in] id   identification for gpio
 * @param[in] mode the mode option to set
 */
inline void GPIO::set_mode(gpio::Id id, gpio::Mode mode)
{
    bitop::update_msk(regs(id)->MODER, 0x3 << id.pin*2, mode << id.pin*2);
}

/**
 * @brief Set the GPIO pull
 *
 * A GPIO can have a pull up, pull down, or neither.
 *
 * @param[in] id   identification for gpio
 * @param[in] pull the pull option to set
 */
inline void GPIO::set_pull(gpio::Id id, gpio::Pull pull)
{
    bitop::update_msk(regs(id)->PUPDR, 0x3 << id.pin*2, pull << id.pin*2);
}

/**
 * @brief Set the GPIO output type
 *
 * A GPIO can be set to push/pull or open drain output.
 *
 * @param[in] id   identification for gpio
 * @param[in] type the output type option to set
 */
inline void GPIO::set_output_type(gpio::Id id, gpio::OutputType type)
{
    bitop::update_msk(regs(id)->OTYPER, 0x3 << id.pin*2, type << id.pin*2);
}

/**
 * @brief Set the GPIO alternative function
 *
 * A GPIO can be set to any available alternate function, which is different for every pin.
 *
 * @param[in] id  identification for gpio
 * @param[in] afn the alternate function option to set
 */
inline void GPIO::set_altfn(gpio::Id id, gpio::AltFn afn)
{
    bitop::update_msk(regs(id)->AFR[id.pin < 8 ? 0 : 1], 0xF << (id.pin % 8)*4,
            afn << (id.pin % 8)*4);
}

/**
 * @brief Set the GPIO output speed
 *
 * A GPIO can have low, medium, or fast output.
 *
 * @param[in] id    identification for gpio
 * @param[in] speed the output speed option to set
 */
inline void GPIO::set_output_speed(gpio::Id id, gpio::OutputSpeed speed)
{
    bitop::update_msk(regs(id)->OSPEEDR, 0x3 << id.pin*2, speed << id.pin*2);
}

/**
 * @brief Clear the GPIO output
 *
 * The output state is set low.
 *
 * @param[in] id identification for gpio
 */
inline void GPIO::clr_output(gpio::Id id)
{
    bitop::clr_bit(regs(id)->ODR, id.pin);
}

/**
 * @brief Set the GPIO output
 *
 * The output state is set high.
 *
 * @param[in] id identification for gpio
 */
inline void GPIO::set_output(gpio::Id id)
{
    bitop::set_bit(regs(id)->ODR, id.pin);
}

/**
 * @brief Set the GPIO output state
 *
 * Either set or clear the GPIO state. If the desired state is known at compile-time, `set_output`
 * or `clr_output` should be used instead.
 *
 * @param[in] id    identification for gpio
 * @param[in] state gpio output state
 */
inline void GPIO::set_output_state(gpio::Id id, gpio::PinState state)
{
    bitop::update_bit(regs(id)->ODR, id.pin, state);
}

/**
 * @brief Read the GPIO input state
 *
 * Returns the state of the pin in the IDR register.
 *
 * @param[in] id identification for gpio
 * @return read pin state
 */
inline gpio::PinState GPIO::read_input(gpio::Id id)
{
    return static_cast<gpio::PinState>(bitop::read_bit(regs(id)->IDR, id.pin));
}

#endif  // CORE_GPIO_HPP_
