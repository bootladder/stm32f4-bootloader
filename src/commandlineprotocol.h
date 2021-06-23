//
// Created by steve on 6/17/21.
//

#ifndef STM32F4_BOOTLOADER_COMMANDLINEPROTOCOL_H
#define STM32F4_BOOTLOADER_COMMANDLINEPROTOCOL_H

#include <stdint.h>
void commandlineprotocol_processLine(uint8_t * line);


typedef struct {
    uint8_t sector_number;
} EraseSectorCommand_t;


#endif //STM32F4_BOOTLOADER_COMMANDLINEPROTOCOL_H
