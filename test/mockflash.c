//
// Created by steve on 6/22/21.
//

#include "mockflash.h"


static uint32_t lastcalled_addr;
static uint8_t * lastcalled_data;
static uint8_t lastcalled_len;

void flash_write(uint32_t addr, uint8_t * data, uint8_t len){
    lastcalled_addr = addr;
    lastcalled_data = data;
    lastcalled_len = len;
}

void flash_erase_sector(uint8_t sectornum){

}


bool mockflash_verify_flashwrite(uint32_t addr, uint8_t * data, uint8_t len ){
    if(addr == lastcalled_addr && data == lastcalled_data && len == lastcalled_len)
        return true;

    return false;
}

void mockflash_reset(void){
    lastcalled_len = 0;
    lastcalled_data = 0;
    lastcalled_addr = 0;
}