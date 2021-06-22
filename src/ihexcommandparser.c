//
// Created by steve on 6/21/21.
//

#include "ihexcommandparser.h"
#include <string.h>
#include <stdbool.h>

IHexCommandParserStatus_t
ihexcommandparser_parse(uint8_t * line, IHexCommand_t * cmd){

    if(line[0] != ':')
        return INTELHEXCOMMAND_INVALID_COMMAND;

    uint8_t linelength = strlen(line);
    if(linelength % 2 == 0)  //must be odd length
        return INTELHEXCOMMAND_INVALID_COMMAND;

    if(false == _is_valid_checksum(line))
        return INTELHEXCOMMAND_BAD_CHECKSUM;
}
