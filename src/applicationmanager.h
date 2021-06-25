//
// Created by steve on 6/24/21.
//

#ifndef STM32F4_BOOTLOADER_APPLICATIONMANAGER_H
#define STM32F4_BOOTLOADER_APPLICATIONMANAGER_H

#include <stdbool.h>
#include <stdint.h>

void applicationmanager_jumptoapplication(void);

bool applicationmanager_is_app_loaded(void);
bool applicationmanager_is_valid_reset_vector(void);
uint32_t applicationmanager_get_reset_handler_addr(void);
#endif //STM32F4_BOOTLOADER_APPLICATIONMANAGER_H
