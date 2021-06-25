cmake_minimum_required(VERSION 3.16.3)

# needed to pass cmake's compiler check when cross-compiling
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER   "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")

# COMMON_FLAGS gets applied to all compiled sources. set language-specific flags
set(COMMON_FLAGS    "-Werror -Wall -Wextra -pedantic -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -msoft-float")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -std=gnu99")
set(CMAKE_C_FLAGS   "${COMMON_FLAGS} -std=gnu99")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++17 -fno-rtti -fno-exceptions -fno-threadsafe-statics -Wshadow -Wlogical-op \
                                     -Wsuggest-override -Wsuggest-final-types -Wsuggest-final-methods")

# linker and linker flags
set(CMAKE_LINKER "arm-none-eabi-g++")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/STM32F042C6Tx_FLASH.ld --specs=nosys.specs -Wl,-gc-sections -mcpu=cortex-m0 -mthumb -msoft-float")

# we want different compile options when building for Debug vs. Release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    set(BUILD_TYPE_FLAGS "-Og -ggdb3")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(RELEASE)
    set(BUILD_TYPE_FLAGS "-O2")
    # get outta here, -03
    string(REPLACE "-03" "" CMAKE_ASM_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "-03" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "-03" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
else()
    message(FATAL_ERROR "CMAKE_BUILD_TYPE must be Debug or Release")
endif()

# our code needs to know our BSP
add_compile_definitions(${BSP})

project(${TARGET})

enable_language(CXX C ASM)

add_subdirectory(src)
