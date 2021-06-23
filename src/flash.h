//
// Created by steve on 6/22/21.
//

#ifndef STM32F4_BOOTLOADER_FLASH_H
#define STM32F4_BOOTLOADER_FLASH_H

#include <stdint.h>

void flash_write(uint32_t addr, uint8_t * data, uint8_t len);
void flash_erase_sector(uint8_t sectornum);
#endif //STM32F4_BOOTLOADER_FLASH_H
