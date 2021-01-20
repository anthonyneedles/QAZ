/**
 * @file      persist.cpp
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
 * There are the last two 2KB of flash memory, leaving 30KB for the actual program.
 */

#include "qaz/persist.hpp"

#include "flash/eeprom.h"
#include "util/debug.hpp"

/// Macro expand entry in virtual address array, for eeprom.c
/// "Virtual Address" value doesn't matter (except 0xFFFF), used like an ID for the EEPROM emulator
uint16_t VirtAddVarTab[NB_OF_VAR] = {
#define ENTRY(name, value) \
    value,
    PERSIST_DATA_TABLE(ENTRY)
#undef ENTRY
};

/**
 * @brief Initializes Persist module
 *
 * Validates `VirtAddVarTab` extern variable that the EEPROM emulator uses to find data words. There
 * cannot be any duplicate values, and 0xFFFF is illegal (erased flash has this value, so the
 * emulator uses it to determine where to write the next variable).
 *
 * Also unlocks the flash and initializes the EEPROM emulator.
 */
void persist::init(void)
{
    // validate the virtual address table
    for (unsigned i = 0; i < NB_OF_VAR; ++i) {
        // no virtual address can be 0xFFFF as per EEPROM emulator documentation
        if (VirtAddVarTab[i] == 0xFFFFu) {
            debug::printf("ERROR: virtual address #%d invalid value (0xFFFF)\r\n", i);
            DBG_ASSERT(debug::FORCE_ASSERT);
            return;
        }

        // no duplicate virtual addresses
        for (unsigned j = i + 1; j < NB_OF_VAR; ++j) {
            if (VirtAddVarTab[i] == VirtAddVarTab[j]) {
                debug::printf("ERROR: virtual addresses #%d and #%d duplicates\r\n", i, j);
                DBG_ASSERT(debug::FORCE_ASSERT);
                return;
            }
        }
    }

    FLASH_Unlock();

    // initialize EEPROM emulator
    uint16_t stat = EE_Init();
    if (stat != FLASH_COMPLETE) {
        debug::printf("ERROR: EEPROM emulator flash init failed (%d)\r\n", stat);
        DBG_ASSERT(debug::FORCE_ASSERT);
        return;
    }

    debug::puts("Initialized: Persist Data\r\n");
}

/**
 * @brief Reads a data word in flash
 *
 * Uses the EEPROM emulator to read the most recently written value to a given data word. If the
 * data word doesn't "exist" in flash yet, this function will fail.
 *
 * `buf` does not get written to if the read fails
 *
 * @param[in]     id  identifier for a data word
 * @param[in,out] buf buffer that will be written into
 *
 * @return persist::NONEXISTENT_DATA if data word has not been "created" in memory yet
 *         persist::PAGE_ERROR       if there was no valid page for the emulator
 *         persist::SUCCESS          if the data word was written into the buffer
 */
persist::Status persist::read_data(persist::DataId id, uint16_t &buf)
{
    uint16_t stat = EE_ReadVariable(static_cast<uint16_t>(id), &buf);
    if (stat == 1) {
        debug::printf("WARNING: persist data id 0x%04x does not exist\r\n", id);
        return persist::NONEXISTENT_DATA;
    } else if (stat == NO_VALID_PAGE) {
        debug::printf("ERROR: no valid page for persist data id 0x%04x\r\n", id);
        return persist::PAGE_ERROR;
    } else {
        return persist::SUCCESS;
    }
}

/**
 * @brief Writes data word in flash
 *
 * Uses the EEPROM emulator to write a data word. This basically just writes to the next 32-bit word
 * of the flash, with one half-word being the value and the other being the "virtual address". When
 * reading the data word, the most recently written value of the data word is returned.
 *
 * @param[in] id  identifier for a data word
 * @param[in] val value that will be written into the data word
 *
 * @return persist::FLASH_ERROR an error occurred in the flash driver
 *         persist::PAGE_ERROR  if there was no valid page for the emulator or the page was full
 *         persist::SUCCESS     if the data word was written with the value
 */
persist::Status persist::write_data(persist::DataId id, uint16_t val)
{
    uint16_t stat = EE_WriteVariable(static_cast<uint16_t>(id), val);
    if (stat == FLASH_COMPLETE) {
        return persist::SUCCESS;
    } else if ((stat == PAGE_FULL) || (stat == NO_VALID_PAGE)) {
        debug::printf("ERROR: page error for persist data id 0x%04x (%d)\r\n", id, stat);
        return persist::PAGE_ERROR;
    } else {
        debug::printf("ERROR: flash error for persist data id 0x%04x (%d)\r\n", id, stat);
        return persist::FLASH_ERROR;
    }
}
