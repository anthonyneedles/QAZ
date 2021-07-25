# **QAZ Building**

## **Table of Contents**

1. [Dependencies](#dependencies)
1. [Make](#make)
1. [CMake](#cmake)
1. [Output](#output)

## **Dependencies**

Required APT packages for building:
- gcc-arm-none-eabi
- build-essential
- cmake (>= 3.16.3)

Required APT packages for utility targets and debugging:
- gdb-multiarch
- openocd
- stlink-tools
- doxygen
- graphviz
- python

Additionally, KiCad is used for PCB design.

## **Make**

QAZ uses `make` for top-level project building. This [Makefile](../../Makefile) handles all
building commands. These are the available commands:

- `QAZ` - Build complete software target

- `all` - Build software target, doxygen, and lint

- `docs` - Use Doxygen to create project documentation (with Graphviz graphs)

- `clean` - Removes all built files

- `lint` - Run cpplint.py on `src/`

- `flash` - Flash binary at 0x08000000, `make QAZ` if no binary

- `help` - Display the above

There are several variables that the user can set in the top level
[Makefile](../../Makefile).

- `BUILD_TYPE` - Debug or Release (i.e. debug print statements/asserts or not)

- `BOARD` - Which board to build for (dictates BSP)

A dummy marker file `.rebuild-marker` is used to ensure that whenever the top level
[Makefile](../../Makefile) is changed the system ALWAYS rebuilds. This ensures that partial
builds don't occur when changing the above variables.

## **CMake**

When building the output project, `cmake` will be invoked to generate the source-level
[Makefile](../../Makefile) in the `build/` directory, which will then be used to compile and
link the output executable.

The top-level [CMakeLists.txt](../../CMakeLists.txt) expects three variables: `TARGET`,
`CMAKE_BUILD_TYPE`, and `BSP`, which is nominally passed in by the top-level [Makefile](Makefile)
from the `TARGET`, `BUILD_TYPE`, and `BOARD` variables (respectively). This file also defines our
compilers/linkers, as well as all of the flags we pass to them. `src/` is added as a subdirectory.

The source-level [CMakeLists](../../src/CMakeLists.txt) expects the same variables as above. This
file defines all C++, C, and Assembly files (paths relative to `src/`), as well as include
directories.

## **Output**

After building, output targets can be found in `build/src`. The default output target is `QAZ.elf`.
This is copied and converted to `QAZ.bin`. To help tracking .elf/.bin files, both are then copied
and renamed to: `${BOARD}_${BUILD_TYPE}_${GIT_STATE}_${GIT_HASH}.*` (`GIT_STATE` is either
`CLEAN` or `DIRTY`).

The .elf output can be used to program the given board by following the
[QAZ Programming guide](Programming.md).