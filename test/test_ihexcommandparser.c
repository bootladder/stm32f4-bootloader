//
// Created by steve on 6/21/21.
//

#include "test_ihexcommandparser.h"

#include <stdint.h>
#include <stdio.h>
#include "ihexcommandparser.h"
#include "ihexcommandparser_private.h"
#include "hex2int.h"
#include <string.h>

static void extended_linear_address_populates_correctly(){
    uint8_t * line;
    IHexCommand_t cmd;
    IHexCommandParserStatus_t status;
    uint8_t * expected_data;

    line =  ":020000040800F2\n";
    status = ihexcommandparser_parse(line, &cmd);

    if(cmd.record_type != IHEXRECORDTYPE_EXTENDED_LINEAR_ADDRESS) printf("record type not linear address");
    if(cmd.base_address_offset != 0) printf("base address offset not zero");
    if(cmd.record_data[0] != 0x08) printf("wrong data 1");
    if(cmd.record_data[1] != 0x00) printf("wrong data 2");

}

static void good_ones_check_status_and_struct_content(){
    uint8_t * line;
    IHexCommand_t cmd;
    IHexCommandParserStatus_t status;
    uint8_t * expected_data;

/////////////////////////////////////////////
    line = ":10010000214601360121470136007EFE09D2190140\n";
    status = ihexcommandparser_parse(line, &cmd);

    if(status != INTELHEXCOMMAND_OK) {
        printf("1 FAIL NOT GOOD, status is %d\n", status);
    }

    if(cmd.record_length != 16) printf("record length not 16");
    if(cmd.record_type != IHEXRECORDTYPE_DATA) printf("record type not 0");
    if(cmd.base_address_offset != 256) printf("base address offset not 256");
    if(cmd.checksum != 0x40) printf("checksum not 0x40");

    expected_data = (uint8_t []) {
            0x21, 0x46, 0x01, 0x36, 0x01, 0x21, 0x47, 0x01, 0x36, 0x00, 0x7E, 0xFE, 0x09, 0xD2, 0x19, 0x01
    };
    if(memcmp(cmd.record_data, expected_data, 16) != 0) printf("Data mismatch");


/////////////////////////////////////////////
    line = ":100130003F0156702B5E712B722B732146013421C7\n";
    status = ihexcommandparser_parse(line, &cmd);

    if(status != INTELHEXCOMMAND_OK) {
        printf("2 FAIL NOT GOOD, status is %d\n", status);
    }


    if(cmd.record_length != 16) printf("record length not 16");
    if(cmd.record_type != IHEXRECORDTYPE_DATA) printf("record type not 0");
    if(cmd.base_address_offset != 0x0130) printf("base address offset not 0x0130");
    if(cmd.checksum != 0xC7) printf("checksum not 0x40");

    expected_data = (uint8_t []) {
            0x3F, 0x01, 0x56, 0x70, 0x2B, 0x5E, 0x71, 0x2B, 0x72, 0x2B, 0x73, 0x21, 0x46, 0x01, 0x34, 0x21
    };
    if(memcmp(cmd.record_data, expected_data, 16) != 0) printf("Data mismatch");


/////////////////////////////////////////////
    line = ":00000001FF\n";
    status = ihexcommandparser_parse(line, &cmd);

    if(status != INTELHEXCOMMAND_OK)
        printf("3 FAIL NOT GOOD, status is %d\n", status);

    if(cmd.record_type != IHEXRECORDTYPE_ENDOFFILE) printf("record type not 1");


//////////////////////////////
    line = ":084180005DCF00085DCF0008CF\n";
    status = ihexcommandparser_parse(line, &cmd);

    if(status != INTELHEXCOMMAND_OK)
        printf("4 FAIL NOT GOOD, status is %d\n", status);

}

static void record_type(){
    uint8_t * line = ":030001041234117D\n";

    bool res = _is_valid_record_type(line);

    if(res != true)
        printf("FAIL record type shold be good\n");

    line = ":030001091234117D\n";
    res = _is_valid_record_type(line);

    if(res != false)
        printf("FAIL record type shold be BAD\n");
}


static void record_data_length(){
    uint8_t * line = ":2000010412341111117D\n";  //7D is correct
    bool res = _is_valid_data_length(line);

    if(res != false)
        printf("FAIL data length\n");

    line = ":030001041234117D\n";

    res = _is_valid_data_length(line);

    if(res != true)
        printf("FAIL data length shold be good\n");

}


static void hex2int_works(){
    if( 0 != hex2int('0')) {
        printf("FAIL 0");
    }
    if( 9 != hex2int('9')) {
        printf("FAIL 9");
    }
    if( 10 != hex2int('A')) {
        printf("FAIL A");
    }
    if( 11 != hex2int('B')) {
        printf("FAIL B");
    }
    if( 12 != hex2int('C')) {
        printf("FAIL C");
    }
    if( 13 != hex2int('D')) {
        printf("FAIL D");
    }
    if( 14 != hex2int('E')) {
        printf("FAIL E");
    }
    if( 15 != hex2int('F'))
        printf("FAIL F");
}

static void invalidchecksum_returns_invalidchecksum(){
    uint8_t * line = ":0500010412341111117E\n";  //7D is correct
    bool res = _is_valid_checksum(line);

    if(res != false){
        printf("FAIL checksum should be bad\n");
    }

    line = ":020100102708BE\n"; //":10010000214601360121470136007EFE09D2190140\n";

    res = _is_valid_checksum(line);

    if(res != true){
        printf("FAIL checksum should be GOOD\n");
    }

}

static void even_number_of_hexchars_returns_invalid(){
    uint8_t * line = ":12345\n";
    IHexCommand_t * cmd;
    IHexCommandParserStatus_t status = ihexcommandparser_parse(line, cmd);

    if(status != INTELHEXCOMMAND_INVALID_COMMAND)
        printf("FAIL EVEN NUMBER\n");
}

static void no_colonprefix_returnsinvald(){
    uint8_t * line = "abcd";
    IHexCommand_t * cmd;
    IHexCommandParserStatus_t status = ihexcommandparser_parse(line, cmd);

    if(status != INTELHEXCOMMAND_INVALID_COMMAND)
        printf("FAIL NO COLON\n");
}

void test_ihexcommandparser(){
    no_colonprefix_returnsinvald();
    even_number_of_hexchars_returns_invalid();
    invalidchecksum_returns_invalidchecksum();
    hex2int_works();
    record_data_length();
    record_type();
    good_ones_check_status_and_struct_content();
    extended_linear_address_populates_correctly();
}