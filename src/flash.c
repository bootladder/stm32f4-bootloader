//
// Created by steve on 6/22/21.
//

#include "flash.h"
#include "stm32f4xx_flash.h"
#include "printing_help.h"

static FLASH_Status status;

bool flash_write(uint32_t addr, uint8_t * data, uint8_t len){

    FLASH_Unlock();

    for(int i=0; i<len; i++){
        status = FLASH_ProgramByte(addr+i, data[i]);
        if(status != FLASH_COMPLETE)
            return false;
    }

    FLASH_Lock();
    return true;
}


bool flash_erase_sector(uint8_t sectornum){

    uint16_t sector_enum;

    switch(sectornum){
        case 0: sector_enum = FLASH_Sector_0; break;
        case 1: sector_enum = FLASH_Sector_1; break;
        case 2: sector_enum = FLASH_Sector_2; break;
        case 3: sector_enum = FLASH_Sector_3; break;
        case 4: sector_enum = FLASH_Sector_4; break;
        case 5: sector_enum = FLASH_Sector_5; break;
        case 6: sector_enum = FLASH_Sector_6; break;
        case 7: sector_enum = FLASH_Sector_7; break;
        case 8: sector_enum = FLASH_Sector_8; break;
    }

    FLASH_Unlock();

    status = FLASH_EraseSector(sector_enum, VoltageRange_3);

    FLASH_Lock();

    return (status == FLASH_COMPLETE);
}