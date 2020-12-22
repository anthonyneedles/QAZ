# QAZ

*STM32F042K6 Firmware for my 'QAZ' keyboard*

1. [About This Project](#about-this-project)
    1. [File Structure](#file-structure)
    1. [Dependencies](#dependencies)
1. [Building](#building)
    1. [Make](#make)
    1. [Useful Commands](#useful-commands)
1. [Operation](#operation)
    1. [Clocks](#clocks)
    1. [Time Slice Loop](#time-slice-loop)
1. [Hardware](#hardware)
    1. [Kicad Project](#kicad-project)

## About This Project

The QAZ project was created as a way for me to learn the USB protocol by
writing a bare-metal USB driver. Since a keyboard is a relatively simple
USB device, and I like mechanical keyboards, I decided that it would be
a perfect project. The QAZ project is planned to support various different
keyboard layouts (only 65% and a testboard for now)

This repository holds files for both the software and hardware portions
of this project. The software consists of C source and header files, 
built using Make. Building is only supported in Debian-based systems.
CMSIS is used for some MCU hardware abstraction.

The software uses:
- `arm-none-eabi-gcc` for C/Assembly compilation
- `arm-none-eabi-g++` for C++ compilation and linking
- `make` for building the project
- `gdb-multiarch` for debugging (replaced arm-none-eabi-gdb)
- `openocd` for STLink control and gdb interfacing
- `st-flash` for flashing (and not debugging)

The PCB(s) for the different board versions have their schematic and
layouts designed in KiCad, which are contained in this library and can
be manufactured in any generic fabrication house.

There is a maker space at my work that has a laser cutter that can cut
acrylic, so decided to try to keep costs down and make a "sandwitch" case,
which consists of several stacked layers of acrylic. The vector design 
files are included in this repo.

### File Structure

```
└── QAZ/
    ├── build/
    │   ├── bin/
    │   │   └── .bin, .elf files (and copies with git hashes)
    │   │ 
    │   ├── dep/
    │   │   └── .d source file dependencies (mirrors src/ directory)
    │   │ 
    │   ├── log/
    │   │   └── listings, symbol tables, mappings
    │   │ 
    │   ├── obj/
    │   │   └── .o object files (mirrors src/ directory)
    │   │ 
    │   ├── openocd/
    │   │   └── .cfg for stlink/stm32f0x
    │   │
    │   ├── scripts/
    │   │   └── useful project scripts
    │   │
    │   └── other build files (linker script, etc.)
    │
    ├── CMSIS/
    │   └── Cortex Microcontroller Software Interface Standard HAL
    │
    ├── hardware/
    │   ├── common/
    │   │   └── hardware utility used by both (e.g. KiCad libraries) 
    │   │ 
    │   └── QAZ_*/
    │       └── PCB/case layer subdirectories for each QAZ configuration
    │
    ├── src/
    │   └── all source files, with module subdirectories
    │
    └── LICENSE, README, top-level Makefile
```

The `bin/`, `dep/`, `log/`, and `obj/` directories are not tracked, and get made when the
project is built. The files in these directories are removed when the project
is cleaned with `make clean`.

### Dependencies

The following APT packages are required:
- gcc-arm-none-eabi
- build-essential
- gdb-multiarch
- openocd
- stlink-tools

Additionally, KiCad is used for PCB design.

## Building

### Make

QAZ uses `make` for project building. The top level [Makefile](Makefile)
handles all building commands. These are the available commands:

**clean** - Removes all object, dependency, and bin file

**qaz** - Build complete software target

**flash** - Flash binary at 0x08000000, make blink if no binary

**tmux** - Launch tmux bootstrap shell script (only if 'QAZ' session doesn't already exist)

**help** - Display the above

There are several variables that the user can set in `Makefile`. This includes
all C (`C_SRC`), C++ (`CXX_SRC`), Assembly (`S_SRC`) files (paths relative to
`src/`), as well as:

`BUILD_TYPE` - DEBUG or RELEASE (i.e. debug print statements/asserts or not)

`BOARD` - Which board to build for (dictates BSP)

**Each source file must be specified in the `Makefile`**

When each source is compiled, a dependency file is generated that contains a
rule for that source with all included header files (and nested includes) as
prerequisites. Every one of these .d files are included in `Makefile` so
that any change in a source's dependency requires a recompiling of that source.

## Operation

### Clocks

The STM32F042C6T6 has a default HS clock of 8MHz, and a HSI48 48MHz clock,
which is specifically for the USB peripheral. This clock has a terrible
accuracy of +/-3% at room temperature, which is out of spec of USB 2.0
tolerance. However, the USB peripheral has a special Clock Recovery System
(CRS) which dynamically adjusts the oscillator an adequate amount.

In the intial steps of this design, this HSI48 was used, but as of QAZ board 
v0.1 an external 8MHz crystal supplies the HSE oscillator, which gets
multiplied to 48MHz from the PLL, then finaly feeds the system core and USB
peripheral.

### Time Slice Loop

The QAZ firmware does not operate on an RTOS, because it doesn't require
stringent timing, but rather a time slice superloop. The configuration of
this is defined in [core/time_slice.h](src/core/time_slice.h)

Every task is defined in the `TASK_TABLE`, where the execution period
and task functions is entered. While running, the interal 'time slice mananger
task' will make sure that each task gets a chance to run every loop period.
Specific task period is created by only calling the task function every N time
slices (where N = Task Period / Loop Period).

**Task periods must be multiples of of the timeslice period. For a given set
of task periods, the timeslice period should be as large as possible.**

Curently, the time slice loop (`LOOP_PERIOD_MS`) is 10ms.

Task periods:
- LED Heartbeat Task:   500ms (resulting in 1Hz HB)
- Key Matrix Scan Task:  10ms
- RGB LED Task:          20ms 
- USB HID Task:          20ms 

