/**
 * @file      persist.hpp
 * @brief     Managing persist configuration data
 *
 * @author    Anthony Needles
 * @date      2021/18/01
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * Two pages of flash memory in the STM32F042 are used to hold data that is desired to persist
 * between power cycles (for instance, the coloring profile). The ST EEPROM emulator driver is used
 * to perform reads and writes to flash.
 *
 * Each data word is of type uint16_t.
 *
 * The pages chosen are PAGE 30 (0x80007800 - 0x80007BFF) and PAGE 31 (0x80007C00 - 0x80008000).
 * There are the last two 2KB of FLASH memory, leaving 30KB for the actual program.
 */

#ifndef FLASH_PERSIST_HPP_
#define FLASH_PERSIST_HPP_

#include <stdint.h>

/// Identifier for each data word. Valid values = 0x0000 - 0xFFFE, no duplicates.
/// # of entries must be equal to NB_OF_VAR in flash/eeprom.h
#define PERSIST_DATA_TABLE(ENTRY) \
    ENTRY(HASH_BYTE3,  0x0000) \
    ENTRY(HASH_BYTE2,  0x0001) \
    ENTRY(HASH_BYTE1,  0x0002) \
    ENTRY(HASH_BYTE0,  0x0003) \
    ENTRY(BRIGHT_IDX,  0x0004) \
    ENTRY(COLOR_IDX,   0x0005) \
    ENTRY(PROFILE_IDX, 0x0006) \
    ENTRY(SPEED_IDX,   0x0007)

/**
 * @brief Persist data management namespace
 *
 * This namespace holds the API for getting/setting persist variables.
 */
namespace persist {

/// Macro expand an enum for each data word
enum DataId : uint16_t {
#define ENTRY(name, value) \
    name = value,
    PERSIST_DATA_TABLE(ENTRY)
#undef ENTRY
};

/// Status of the data read/write
enum Status {
    FLASH_ERROR,
    NONEXISTENT_DATA,
    PAGE_ERROR,
    SUCCESS,
};

/// Unlock flash and init EEPROM emulator
void init(void);

/// Read the current data word value into buffer
Status read_data(DataId id, uint16_t &buf);

/// Write value to data word
Status write_data(DataId id, uint16_t val);

/// Read data word into buffer if it exists, else "create" it with default value
inline void read_or_create_data(DataId id, uint16_t &buf, uint16_t default_val);

}  // namespace persist

/**
 * @brief Helper function for reading a data word that may not exist
 *
 * If a persistent data word does not exist, the read for it will fail. When this happens, we will
 * usually want to then "create" it in flash with a default value so that we can later properly
 * read/write the data.
 *
 * @param[in]     id          identifier for a data word
 * @param[in,out] buf         buffer that will be written into (with flash data or `default_val`)
 * @param[in]     default_val value used if data word doesn't yet exist in flash
 */
inline void persist::read_or_create_data(persist::DataId id, uint16_t &buf, uint16_t default_val)
{
    persist::Status pstat = persist::read_data(id, buf);
    if (pstat != persist::SUCCESS) {
        // if the reading failed, we need to set the "default" value
        buf = default_val;
        if (pstat == persist::NONEXISTENT_DATA) {
            // the data doesn't exist in flash: either first time, or it got erased
            persist::write_data(persist::PROFILE_IDX, buf);
        }
    }
}

#endif  // FLASH_PERSIST_HPP_
