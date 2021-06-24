//
// Created by steve on 6/17/21.
//

#include <stdbool.h>
#include "bootloader.h"
#include "flash.h"

static uint32_t base_address = 0;

void bootloader_process_ihexcommand(IHexCommand_t * ihexcmd){

    switch(ihexcmd->record_type) {

        case IHEXRECORDTYPE_DATA:
            // take the address offset and add it to the base

            flash_write(base_address + ihexcmd->base_address_offset,
                        ihexcmd->record_data,
                        ihexcmd->record_length);
            break;

        case IHEXRECORDTYPE_EXTENDED_SEGMENT_ADDRESS:
            //data contains 2 bytes, big endian, base address
            //multiply by another 16 according to intel hex format
            base_address = (256*ihexcmd->record_data[0] + ihexcmd->record_data[1]);
            base_address = base_address*16;
            break;

        case IHEXRECORDTYPE_EXTENDED_LINEAR_ADDRESS:

            base_address = (256*ihexcmd->record_data[0] + ihexcmd->record_data[1]);
            base_address <<= 16;
            break;
    }
}

uint32_t bootloader_get_base_address(void) {
    return base_address;
}


bool bootloader_erase_sector(EraseSectorCommand_t * cmd){
//    PRINTSTRING("Erasing sector: ")
//    uint8_t numbyte = '0' + cmd->sector_number;
//    PRINTBYTE(numbyte)
//    PRINTSTRING("\n")

    flash_erase_sector(cmd->sector_number);
}