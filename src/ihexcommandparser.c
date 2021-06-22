//
// Created by steve on 6/21/21.
//

#include "ihexcommandparser.h"
#include "ihexcommandparser_private.h"
#include "hex2int.h"
#include <string.h>


IHexCommandParserStatus_t
ihexcommandparser_parse(uint8_t * line, IHexCommand_t * cmd){

    if(line[0] != ':')
        return INTELHEXCOMMAND_INVALID_COMMAND;

    uint8_t linelength = strlen(line);
    if(linelength % 2 != 0)  //must be even length, INCLUDES NEWLINE
        return INTELHEXCOMMAND_INVALID_COMMAND;

    if(false == _is_valid_data_length(line))
        return INTELHEXCOMMAND_INVALID_LENGTH;

    if(false == _is_valid_checksum(line))
        return INTELHEXCOMMAND_BAD_CHECKSUM;

}


bool _is_valid_checksum(uint8_t * line){
    uint8_t linelength = strlen(line);
    uint8_t runningtotal = 0;
    //newline is len-1, cheksum is len-2, len-3
    uint8_t expectedchecksum = 16 * hex2int(line[linelength-3]);
    expectedchecksum += hex2int(line[linelength-2]);

    // start after colon, skip newline and checksum
    for(int i=1; i<linelength - 3; i+=2){
        uint8_t bytevalue = 16*hex2int(line[i]) + hex2int(line[i+1]);
        runningtotal += bytevalue;
    }

    runningtotal = ~runningtotal + 1;  // twos complement

    return (expectedchecksum == runningtotal);
}

bool _is_valid_data_length(uint8_t * line){
    uint8_t expected_data_length =  16 * hex2int(line[1])
                        + hex2int(line[2]);

    expected_data_length *= 2;  //hex chars

    uint8_t line_length = strlen(line);
    // colon + length + address + record type + data + checksum + newline
    uint8_t expected_line_length = 1 + 2 + 4 + 2 + expected_data_length + 2 + 1;

    return (expected_line_length == line_length);
}

bool _is_valid_record_type(uint8_t * line){
    uint8_t record_type =  16 * hex2int(line[7])
                                    + hex2int(line[8]);
    return (record_type <= 5);
}