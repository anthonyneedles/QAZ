cmake_minimum_required(VERSION 3.16.3)

set(CXX_SOURCES
    comm/i2c.cpp
    comm/uart.cpp
    core/clock.cpp
    core/main.cpp
    core/time_slice.cpp
    flash/persist.cpp
    usb/usb.cpp
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

# append our bsp source to source list
if(BSP STREQUAL "QAZ_65")
    set(CXX_SOURCES ${CXX_SOURCES}
        bsp/qaz_65/bsp_qaz_65.cpp
        is31fl3746a/is31fl3746a.cpp
        keyboard/key_matrix.cpp
        keyboard/lighting.cpp
        usb/kb_hid.cpp
        usb/kb_usb_desc.cpp
    )
elseif(BSP STREQUAL "QAZ_MEDIA")
    set(CXX_SOURCES ${CXX_SOURCES}
        bsp/qaz_media/bsp_qaz_media.cpp
        media/buttons.cpp
        media/rotary_encoder.cpp
        usb/consumer_hid.cpp
        usb/consumer_usb_desc.cpp
    )
else()
    message(FATAL_ERROR "Unknown BSP: '${BSP}'\n")
endif()

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
