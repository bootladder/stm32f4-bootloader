//
// Created by steve on 6/21/21.
//

#include "test_ihexcommandparser.h"

#include <stdint.h>
#include <stdio.h>
#include "ihexcommandparser.h"
#include "ihexcommandparser_private.h"
#include "hex2int.h"

static void good_ones(){
    uint8_t * line;
    IHexCommand_t * cmd;
    IHexCommandParserStatus_t status;

    line = ":10010000214601360121470136007EFE09D2190140\n";
    status = ihexcommandparser_parse(line, cmd);

    if(status != INTELHEXCOMMAND_OK)
        printf("FAIL NOT GOOD, status is %d\n", status);

    line = ":100130003F0156702B5E712B722B732146013421C7\n";
    status = ihexcommandparser_parse(line, cmd);

    if(status != INTELHEXCOMMAND_OK)
        printf("FAIL NOT GOOD, status is %d\n", status);

    line = ":00000001FF\n";
    status = ihexcommandparser_parse(line, cmd);

    if(status != INTELHEXCOMMAND_OK)
        printf("FAIL NOT GOOD, status is %d\n", status);

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
    good_ones();
}