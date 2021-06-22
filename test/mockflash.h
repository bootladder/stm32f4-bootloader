//
// Created by steve on 6/22/21.
//

#ifndef STM32F4_BOOTLOADER_MOCKFLASH_H
#define STM32F4_BOOTLOADER_MOCKFLASH_H
#include <stdbool.h>
#include <stdint.h>

void mockflash_reset(void);
bool mockflash_verify_flashwrite(uint32_t addr, uint8_t * data, uint8_t len );

#endif //STM32F4_BOOTLOADER_MOCKFLASH_H
