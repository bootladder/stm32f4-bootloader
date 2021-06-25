//
// Created by steve on 6/22/21.
//

#include "bootloader_messages.h"
#include "applicationmanager.h"
#include "printing_help.h"
#include <stdbool.h>

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
        PRINTSTRING("Don't know\n")
    }
    else{
        PRINTSTRING("Loaded, INVALID RESET VECTOR")
    }
}