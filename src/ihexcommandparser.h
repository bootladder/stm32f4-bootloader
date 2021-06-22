//
// Created by steve on 6/21/21.
//

#ifndef STM32F4_BOOTLOADER_IHEXCOMMANDPARSER_H
#define STM32F4_BOOTLOADER_IHEXCOMMANDPARSER_H
#include <stdint.h>

typedef struct {

    uint8_t ihr_length;   //!< Length of the record in bytes.
    uint8_t ihr_type;     //!< Record type (see ihex_rtype_t).
    uint16_t  ihr_address;  //!< Base address offset.
    uint8_t ihr_data[32];     //!< Record data.
    uint8_t ihr_checksum; //!< The record's checksum.

} IHexCommand_t;

typedef enum {
    INTELHEXCOMMAND_OK,
    INTELHEXCOMMAND_INVALID_COMMAND,
    INTELHEXCOMMAND_BAD_CHECKSUM,
    INTELHEXCOMMAND_INVALID_LENGTH,
} IHexCommandParserStatus_t;

IHexCommandParserStatus_t
ihexcommandparser_parse(uint8_t * line, IHexCommand_t * cmd);

#endif //STM32F4_BOOTLOADER_IHEXCOMMANDPARSER_H
