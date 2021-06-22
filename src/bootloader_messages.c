//
// Created by steve on 6/22/21.
//

#include "bootloader_messages.h"

#include "printing_help.h"

void bootloader_print_welcome(void){
    PRINTSTRING("STM32F4 BOOTLOADER\n")
}
void bootloader_print_app_status(void){
    PRINTSTRING("App Status:  Not Implemented\n")
}