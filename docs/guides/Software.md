# **QAZ Software**

## **Table of Contents**

1. [Clocks](#clocks)
1. [Time Slice Loop](#time-slice-loop)
1. [USB](#usb)
1. [Keyboard](#keyboard)
1. [Persistent Data](#persistent-data)

## **Clocks**

The STM32F042C6 has a default HS clock of 8MHz, and a HSI48 48MHz clock, which is specifically for
the USB peripheral. This clock has a terrible accuracy of +/-3% at room temperature, which is out
of spec of USB 2.0 tolerance. However, the USB peripheral has a special Clock Recovery System (CRS)
which dynamically adjusts the oscillator an adequate amount.

In the initial steps of this design, this HSI48 was used, but as of QAZ board v0.1 an external 8MHz
crystal supplies the HSE oscillator, which gets multiplied to 48MHz from the PLL, then finally
feeds the system core and USB peripheral.

## **Time Slice Loop**

The QAZ firmware does not operate on an RTOS, because it doesn't require stringent timing, but
rather a time slice superloop. The configuration of this is defined in
[core/time_slice.hpp](../../src/core/time_slice.hpp).

Tasks must be registered to the timeslice scheduler by calling `timeslice::register_task()`, with
the task period and function as parameters. Registered tasks are entered in a statically defined
task registry, so the maximum number of tasks is defined by `MAX_NUM_TASKS`.

While the timeslice loop is running, the internal 'time slice manager task' will make sure that
each task gets a chance to run every loop period. Specific task periods are created by only
calling the task function every N time slices (where N = Task Period / Loop Period).

**Task periods must be multiples of of the timeslice period. For a given set of task periods,
the timeslice period should be as large as possible.**

Currently, the time slice loop (`LOOP_PERIOD_MS`) is 5ms.

Task periods:
- **LED Heartbeat Task** - 500ms
- **Key Matrix Scan Task** - 20ms
- **Lighting Task** - 5ms
- **USB HID KB Task** - 20ms
- **USB HID Consumer Task** - 10ms

## **USB**

The QAZ project uses an entirely self-written USB low-level driver, which interacts directly with
the STM32 USB hardware peripheral. Additionally, there are Keyboard device and Consumer device USB
HID drivers, which utilizes the low-level driver to perform the required HID initialization and
reporting.

In the device descriptor the following fields are set for each board:
- idVendor = `0xC01D`
- idProduct = `0xAA22`
- bcdDevice = Version of board (e.g. `1.10`)
- iManufacturer = String descriptor 1 ("`anthonyneedles`")
- iProduct =  String descriptor 2 (e.g. "`qaz media`")

## **Keyboard**

The keyboard layout for a QAZ configuration is defined in the BSP file for the board. `COLS` and
`ROWS` define the physical pins of the key matrix. The `BASE_TABLE` and `FN_TABLE` defines the
keyboard layout for a given row and column pin, with column0/row0 being the "top left" of the
keyboard.

The entries in the key layout table correspond to a given entry in the USB HID usages table, as
well as "extra" codes added that correspond not to actual codes, but actions to perform. For
instance, changing the keyboard RGB LED brightness and color. `NONE` is used when no keycode or
action corresponds to with the key on the layer.

There is a special key called `FN`, which when pressed switches the key layout layer from Base to
Fn. This means the any other key also pressed with the `FN` key will result in the `FN_TABLE`
being used to translate key presses into key codes/actions rather than `BASE_TABLE`. This allows
almost double the amount of "keys" on the keyboard.

For example, in the QAZ 65%, pressing just the "1/!" physical key results in the Base keycode
(0x1E) for that key being sent to the host. If instead the "1/!" physical key AND the "FN"
physical key were pressed, then the Fn keycode (0x3A, the F1 keycode) for that given key is
sent instead.

It important to keep in mind, that since keyboard layouts are not exact grids, not every column/row
pin corresponds to a physical pin, but must be defined in each table grid (and given a `NONE` value).

Additionally, any of the keys can also be defined in `CALLBACK_KEY_TABLE`, which (when a key with
that code is pressed) results in the key NOT being placed in the output key buffer (used by the USB
KB HID task to send keycodes to the host), but having a callback (initially defined as `weak`)
called. This allows other modules defining the callback and implementing a hook to execute when the
given key is pressed (seen in RGB LED module).

## **Persistent Data**

There are several data words that are saved in the internal flash, as it is desired that they
persist between PORs (for instance, the lighting settings). This is achieved by emulating the
flash as EEPROM.

This emulation requires two full flash pages be used. In order to maximize the available flash for
the program, the last two pages are used. Since each page is 1kB, this means that the available
flash in the STM32F042C6 for the program is 30kB, with the last 2kB being reserved.

New data words can be added by adding entries to the `PERSIST_DATA_TABLE` in
[src/qaz/persist.hpp](../../src/qaz/persist.hpp), and increasing `NB_OF_VAR` in
[src/flash/eeprom.h](../../src/flash/eeprom.h).