//
// Created by steve on 6/17/21.
//

#include "bootloader.h"
#include "printing_help.h"


void bootloader_process_ihexcommand(IHexCommand_t * ihexcmd){
    
}


void bootloader_print_welcome(void){
    PRINTSTRING("STM32F4 BOOTLOADER\n")
}
void bootloader_print_app_status(void){
    PRINTSTRING("App Status:  Not Implemented\n")
}