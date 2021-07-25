# **QAZ**

![QAZ 65% Side](https://i.postimg.cc/tCssjYhx/QAZ-65-Side.png)

## Table of Contents

1. [Boards](#boards)
1. [About This Project](#about-this-project)
    1. [File Structure](#file-structure)
    1. [Dependencies](#dependencies)
1. [Programming](#programming)
1. [Software](#software)
1. [Building](#building)

## **Boards**

### [**QAZ 65%**](docs/guides/QAZ_65.md)

### [**QAZ Media**](docs/guides/QAZ_Media.md)

## **About This Project**

The QAZ project was created as a way for me to learn the USB protocol by writing a bare-metal USB
driver. Since a keyboard is a relatively simple USB device, and I like mechanical keyboards, I
decided that it would be a perfect project. The QAZ project is planned to support various different
keyboard layouts (only 65% and a Media board for now).

This repository holds files for both the software and hardware portions of this project. The
software consists of C++ source and header files, built using Make. Building is only supported
in Debian-based systems. CMSIS is used for some MCU hardware abstraction.

The PCB(s) for the different board versions have their schematic and layouts designed in KiCad,
which are contained in this library and can be manufactured in any generic fabrication house.

There is a maker space at my work that has a laser cutter that can cut acrylic, so decided to try
to keep costs down and make a "sandwich" case, which consists of several stacked layers of acrylic.

### **File Structure**

```
└── QAZ/
    ├── build/
    │   └── CMake build directory
    │
    ├── docs/
    │   │── guides/
    │   │   └── board-specific info, software info, etc.
    │   │
    │   ├── doxygen/
    │   │   └── Doxygen html output
    │   │
    │   └── media/
    │       └── diagrams, pictures, etc.
    │
    ├── hardware/
    │   ├── common/
    │   │   └── hardware utility used by both (e.g. KiCad libraries)
    │   │
    │   └── QAZ_*/
    │       └── PCB/case layer subdirectories for each QAZ configuration
    │
    ├── scripts/
    │   └── useful project scripts (cpplint.py, Doxyfile, etc.)
    │
    ├── src/
    │   └── all source files/module subdirectories, source-level CMakeLists.txt
    │
    └── LICENSE, README, top-level Makefile/CMakeLists.txt
```

The `docs\doxygen` and `build` directories are not tracked, and get made when the project is built.
The files in these directories are removed when the project is cleaned with `make clean`.

## **Programming**

The board programming guide can be found at [`docs/guides/Programming.md`](docs/guides/Programming.md).

## **Software**

The software guide can be found at [`docs/guides/Software.md`](docs/guides/Software.md).

## **Building**

The software building guide can be found at [`docs/guides/Building.md`](docs/guides/Building.md).