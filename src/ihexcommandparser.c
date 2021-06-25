//
// Created by steve on 6/21/21.
//

#include "ihexcommandparser.h"
#include "ihexcommandparser_private.h"
#include "hex2int.h"
#include <string.h>

static uint8_t _get_record_length(uint8_t * line);
static IHexRecordType_t _get_record_type(uint8_t * line);
static uint16_t _get_base_address_offset(uint8_t * line);
static uint8_t _get_specified_checksum(uint8_t * line);
static void _load_record_data(uint8_t * line, IHexCommand_t * cmd);

static int32_t strlen_to_newline(uint8_t * line);

IHexCommandParserStatus_t
ihexcommandparser_parse(uint8_t * line, IHexCommand_t * cmd){

    if(line[0] != ':')
        return INTELHEXCOMMAND_INVALID_COMMAND;

    uint8_t linelength = strlen_to_newline(line);
    if(linelength % 2 != 0)  //must be even length, INCLUDES NEWLINE
        return INTELHEXCOMMAND_INVALID_COMMAND;

    if(false == _is_valid_data_length(line))
        return INTELHEXCOMMAND_INVALID_LENGTH;

    if(false == _is_valid_checksum(line))
        return INTELHEXCOMMAND_BAD_CHECKSUM;

    cmd->record_length = _get_record_length(line);
    cmd->record_type = _get_record_type(line);
    cmd->base_address_offset = _get_base_address_offset(line);
    cmd->checksum = _get_specified_checksum(line);
    _load_record_data(line, cmd);

    return INTELHEXCOMMAND_OK;
}


bool _is_valid_checksum(uint8_t * line){
    uint8_t linelength = strlen_to_newline(line);
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

    uint8_t line_length = strlen_to_newline(line);
    // colon + length + address + record type + data + checksum + newline
    uint8_t expected_line_length = 1 + 2 + 4 + 2 + expected_data_length + 2 + 1;

    return (expected_line_length == line_length);
}

bool _is_valid_record_type(uint8_t * line){
    uint8_t record_type =  16 * hex2int(line[7])
                                    + hex2int(line[8]);
    return (record_type <= 5);
}

static uint8_t _get_record_length(uint8_t * line){
    uint8_t len =  16 * hex2int(line[1])
                                    + hex2int(line[2]);

    return len;
}

static IHexRecordType_t _get_record_type(uint8_t * line){
    uint8_t record_type =  16 * hex2int(line[7])
                           + hex2int(line[8]);
    return record_type;
}

static uint16_t _get_base_address_offset(uint8_t * line){
    uint16_t address_offset =
                    4096 * hex2int(line[3])
                   + 256 * hex2int(line[4])
                    + 16 * hex2int(line[5])
                         + hex2int(line[6]);

    return address_offset;
}

static uint8_t _get_specified_checksum(uint8_t * line){
    uint8_t linelength = strlen_to_newline(line);
    //newline is len-1, cheksum is len-2, len-3
    uint8_t expectedchecksum = 16 * hex2int(line[linelength-3]);
    expectedchecksum += hex2int(line[linelength-2]);

    return expectedchecksum;
}

static void _load_record_data(uint8_t * line, IHexCommand_t * cmd) {
    uint8_t linelength = strlen_to_newline(line);
    //newline is len-1, cheksum is len-2, len-3

    // start after colon,
    // skip byte count, address, record type
    // skip newline and checksum
    for(int i= 1+2+4+2 , zz=0; i<linelength - 3; i+=2, zz++){
        uint8_t bytevalue = 16*hex2int(line[i]) + hex2int(line[i+1]);
        cmd->record_data[zz] = bytevalue;
    }
}

/*
 * ASSUMES STRING MAX LENGTH
 */
static int32_t strlen_to_newline(uint8_t * line){
    for(uint8_t i = 0; i< 200; i++){
        if(line[i] == '\n')
            return i+1;
    }
    return 0;
}
