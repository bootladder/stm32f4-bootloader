//
// Created by steve on 6/21/21.
//

#ifndef STM32F4_BOOTLOADER_IHEXCOMMANDPARSER_PRIVATE_H
#define STM32F4_BOOTLOADER_IHEXCOMMANDPARSER_PRIVATE_H

#include <stdbool.h>
#include <stdint.h>
bool _is_valid_checksum(uint8_t * line);
bool _is_valid_data_length(uint8_t * line);
bool _is_valid_record_type(uint8_t * line);

#endif //STM32F4_BOOTLOADER_IHEXCOMMANDPARSER_PRIVATE_H
