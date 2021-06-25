//
// Created by steve on 6/22/21.
//

#include "bootloader_messages.h"
#include "applicationmanager.h"
#include "printing_help.h"
#include <stdbool.h>

static void u32_to_str(uint32_t addr, uint8_t str[8]);

void bootloader_print_welcome(void){
    PRINTSTRING("STM32F4 BOOTLOADER\n")
}
void bootloader_print_app_status(void){
    PRINTSTRING("App Status: ")

    if(false == applicationmanager_is_app_loaded()){
        PRINTSTRING("No app loaded\n")
    }

    else if(applicationmanager_is_valid_reset_vector()){
        PRINTSTRING("Loaded, reset at ")
        uint32_t appresethandleraddr = applicationmanager_get_reset_handler_addr();
        static uint8_t addrstring[8];
        u32_to_str(appresethandleraddr, addrstring);
        PRINTSTRING("0x")
        printbuf(addrstring, 8);
        PRINTSTRING("\n")
    }
    else{
        PRINTSTRING("Loaded, INVALID RESET VECTOR")
    }
}


static uint8_t digit_to_char(uint8_t digit);

static void u32_to_str(uint32_t addr, uint8_t str[8]){

    uint8_t digit0 = (addr & 0x0000000F) >> 0;
    uint8_t digit1 = (addr & 0x000000F0) >> 4;
    uint8_t digit2 = (addr & 0x00000F00) >> 8;
    uint8_t digit3 = (addr & 0x0000F000) >> 12;
    uint8_t digit4 = (addr & 0x000F0000) >> 16;
    uint8_t digit5 = (addr & 0x00F00000) >> 20;
    uint8_t digit6 = (addr & 0x0F000000) >> 24;
    uint8_t digit7 = (addr & 0xF0000000) >> 28;

    uint8_t char0 = digit_to_char(digit0);
    uint8_t char1 = digit_to_char(digit1);
    uint8_t char2 = digit_to_char(digit2);
    uint8_t char3 = digit_to_char(digit3);
    uint8_t char4 = digit_to_char(digit4);
    uint8_t char5 = digit_to_char(digit5);
    uint8_t char6 = digit_to_char(digit6);
    uint8_t char7 = digit_to_char(digit7);

    // printing big endian, most significant first
    str[0] = char7;
    str[1] = char6;
    str[2] = char5;
    str[3] = char4;
    str[4] = char3;
    str[5] = char2;
    str[6] = char1;
    str[7] = char0;
}

static uint8_t digit_to_char(uint8_t digit){
    uint8_t c = 0;
    if(digit <= 0x9)
        c = '0' + digit;
    else if(digit <= 0xF)
        c = 'A' + (digit-10);
    else
        c = 'X';
    return c;
}