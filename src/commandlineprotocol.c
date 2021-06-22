//
// Created by steve on 6/17/21.
//

#include "commandlineprotocol.h"
#include "bootloader.h"
#include "ihexcommandparser.h"
#include "printing_help.h"

#include <string.h>

static IHexCommand_t ihexcmd;

void commandlineprotocol_processLine(uint8_t * line){

    if(0 == strncmp(line, "erase sector", 11)){
        PRINTSTRING("Erase!\n")
    }
    else if(line[0] == ':'){
        IHexCommandParserStatus_t ihexstatus = ihexcommandparser_parse(line, &ihexcmd);

        if(INTELHEXCOMMAND_OK == ihexstatus){
            bootloader_process_ihexcommand(&ihexcmd);
        }
        else{
            PRINTSTRING("INVALID IHEX COMMAND!!\n");
        }
    }
    else if(0 == strncmp(line, "verify", 6)){
        PRINTSTRING("Verify!\n")
    }
    else if(0 == strncmp(line, "help", 4)){
        PRINTSTRING("Help!\n")
    }
    else{
        PRINTSTRING("Invalid Command!\n")
    }
}