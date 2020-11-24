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

I'm not a big fan of the rubber dome keyboards that come standard stock at the
company I work for. I also spend quite a lot of my time programming. So I
wanted to get a mechanical keyboard for office use, but just buying one would
be too easy. Well there is a maker space at my work that has an acrylic
engraver and pcb fabricator. So I started this project as a way to see how
cheaply (not counting keycaps and switches) I could make a keyboard. This is
also my first personal embedded software project done entirely from command
line and in C/C++.

This firmware uses:
- `arm-none-eabi-gcc` for C/Assembly compilation
- `arm-none-eabi-g++` for C++ compilation and linking
- `make` for building the project
- `gdb-multiarch` for debugging (replaced arm-none-eabi-gdb)
- `openocd` for STLink control and gdb interfacing
- `st-flash` for flashing (and not debugging)

This project is only supported to be operated in Debian-based systems.

### File Structure

```
└── QAZ/
    ├── build/
    │   ├── bin/
    │   │   └── .bin, .hex, .elf files, from linker
    │   │ 
    │   ├── dep/
    │   │   └── .d source file dependencies, from gcc
    │   │ 
    │   ├── log/
    │   │   └── listings, symbol tables, mappings
    │   │ 
    │   ├── obj/
    │   │   └── .o object files, from gcc
    │   │ 
    │   ├── openocd/
    │   │   └── .cfg for stlink/stm32f0x
    │   │
    │   └── scripts/
    │       └── useful project scripts
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
    └── src/
        └── all source files
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

## Building

### Make

QAZ uses `make` for project building. The top level [Makefile](Makefile)
handles all building commands. These are the available commands:

**clean** - Removes all object, dependency, and bin file

**qaz** - Build complete software target

**flash** - Flash binary at 0x08000000, make blink if no binary

**tmux** - Launch tmux bootstrap shell script (only if 'QAZ' session doesn't already exist)

**help** - Display the above

Several variables can be chosen in `Makefile`, such as address to flash,
compiler/linker flags, target name, etc.

**Each source file must be specified in the `Makefile`**

While it would be easy to automatically detect all .c and .S files, explicitly
defining the sources ensures we know what exactly is being compiled. For now,
no .c/.S file can have the same name, and must be placed in `src/`.

When each source is compiled, a dependency file is generated that contains a
rule for that source with all included header files (and nested includes) as
prerequisites. Every one of these .d files are included in `Makefile` so
that any change in a source's dependency requires a recompiling of that source.

