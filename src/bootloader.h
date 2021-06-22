//
// Created by steve on 6/17/21.
//

#ifndef STM32F4_BOOTLOADER_BOOTLOADER_H
#define STM32F4_BOOTLOADER_BOOTLOADER_H

#include "ihexcommandparser.h"

void bootloader_process_ihexcommand(IHexCommand_t * ihexcmd);

void bootloader_print_welcome(void);
void bootloader_print_app_status(void);
#endif //STM32F4_BOOTLOADER_BOOTLOADER_H
