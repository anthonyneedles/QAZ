cmake_minimum_required(VERSION 3.16.3)

set(CXX_SOURCES
    comm/i2c.cpp
    comm/uart.cpp
    core/clock.cpp
    core/time_slice.cpp
    lp500x/lp500x.cpp
    qaz/key_matrix.cpp
    qaz/lighting.cpp
    qaz/main.cpp
    qaz/persist.cpp
    usb/kb_hid.cpp
    usb/usb.cpp
    usb/usb_descriptors.cpp
    util/debug.cpp
    util/hb.cpp
)

set(C_SOURCES
    flash/eeprom.c
    flash/stm32f0xx_flash.c
)

set(ASM_SOURCES
    core/startup_stm32f042.s
)

set(OUTPUT_TARGET ${PROJECT_NAME}.elf)
add_executable(${OUTPUT_TARGET} ${CXX_SOURCES} ${C_SOURCES} ${ASM_SOURCES})

target_include_directories(${OUTPUT_TARGET} PUBLIC
    .
    CMSIS/Core/Include
    CMSIS/Device/ST/STM32F0xx/Include
)

# add our extra debug/release compiler flags
string(REPLACE " " ";" BUILD_TYPE_FLAGS "${BUILD_TYPE_FLAGS}")
target_compile_options(${OUTPUT_TARGET} PUBLIC ${BUILD_TYPE_FLAGS})