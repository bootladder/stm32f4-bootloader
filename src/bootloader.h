//
// Created by steve on 6/17/21.
//

#ifndef STM32F4_BOOTLOADER_BOOTLOADER_H
#define STM32F4_BOOTLOADER_BOOTLOADER_H

#include "ihexcommandparser.h"
#include "commandlineprotocol.h"
#include <stdbool.h>

void bootloader_process_ihexcommand(IHexCommand_t * ihexcmd);
uint32_t bootloader_get_base_address(void);

bool bootloader_erase_sector(EraseSectorCommand_t * cmd);

void bootloader_print_welcome(void);
void bootloader_print_app_status(void);
#endif //STM32F4_BOOTLOADER_BOOTLOADER_H
