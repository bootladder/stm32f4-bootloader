//
// Created by steve on 6/22/21.
//

#include "bootloader.h"
#include "mockflash.h"
#include <stdio.h>
#include <stdbool.h>

static void address_then_data_writes_correct_address(){
    mockflash_reset();

    IHexCommand_t ihexcmd_set_addr;
    ihexcmd_set_addr.record_type = IHEXRECORDTYPE_EXTENDED_SEGMENT_ADDRESS;
    ihexcmd_set_addr.base_address_offset = 0;
    ihexcmd_set_addr.record_length = 8;
    ihexcmd_set_addr.record_data[0] =0x20;
    ihexcmd_set_addr.record_data[1] =0x00;  //0x2000 * 16 = 0x20000

    IHexCommand_t ihexcmd_data;
    ihexcmd_data.record_type = IHEXRECORDTYPE_DATA;
    ihexcmd_data.base_address_offset = 0x1234;
    ihexcmd_data.record_length = 8;

    bootloader_process_ihexcommand(&ihexcmd_set_addr);
    bootloader_process_ihexcommand(&ihexcmd_data);

    if(false == mockflash_verify_flashwrite(0x21234, ihexcmd_data.record_data, 8))
        printf("incorrect flash write after setting address and then data\n");
}


static void address_changes_address(){
    IHexCommand_t ihexcmd;
    ihexcmd.record_type = IHEXRECORDTYPE_EXTENDED_SEGMENT_ADDRESS;
    ihexcmd.base_address_offset = 0;
    ihexcmd.record_length = 8;
    ihexcmd.record_data[0] =0x20;
    ihexcmd.record_data[1] =0x00;  //0x2000 * 16 = 0x20000

    bootloader_process_ihexcommand(&ihexcmd);

    uint32_t addr =  bootloader_get_base_address();

    if(0x20000 != addr)
        printf("Bad base address after extended seg addr record: %08X\n", addr);
}

static void data_calls_flashwrite(){
    mockflash_reset();

    IHexCommand_t ihexcmd;
    ihexcmd.record_type = IHEXRECORDTYPE_DATA;
    ihexcmd.base_address_offset = 0x1234;
    ihexcmd.record_length = 8;


    bootloader_process_ihexcommand(&ihexcmd);

    if(false == mockflash_verify_flashwrite(0x1234,(uint8_t*) &(ihexcmd.record_data),8))
        printf("mockflash verify failed");
}

void test_bootloader(){

    data_calls_flashwrite();
    address_changes_address();
    address_then_data_writes_correct_address();
}