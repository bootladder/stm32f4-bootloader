//
// Created by steve on 6/17/21.
//

#include "commandlineprotocol.h"
#include "bootloader.h"
#include "ihexcommandparser.h"

#include "printing_help.h"
#include <string.h>
#include <stdbool.h>

static bool parse_erasesector_command(uint8_t * line, EraseSectorCommand_t * cmd);


static IHexCommand_t ihexcmd;
static EraseSectorCommand_t erasesectorcmd;
static uint32_t number_of_commands_processed = 0;



void commandlineprotocol_processLine(uint8_t * line){
    number_of_commands_processed++;
    ////////////////////////////////////////////////
    if(0 == strncmp(line, "erase sector", 11)){
        if(parse_erasesector_command(line, &erasesectorcmd)){

            if(bootloader_erase_sector(&erasesectorcmd)){
                PRINTSTRING("OK\n")
            }
            else{
                PRINTSTRING("FAIL\n")
            }
        }
        else{
            PRINTSTRING("INVALID ERASE SECTOR COMMAND")
        }
    }
    ////////////////////////////////////////////////
    else if(line[0] == ':'){
        IHexCommandParserStatus_t ihexstatus = ihexcommandparser_parse(line, &ihexcmd);

        if(INTELHEXCOMMAND_OK == ihexstatus){

            if(bootloader_process_ihexcommand(&ihexcmd)){
                PRINTSTRING("OK\n")
            }
            else{
                PRINTSTRING("FAIL IHEX COMMAND\n")
            }
        }
        else if(INTELHEXCOMMAND_INVALID_LENGTH == ihexstatus){
            PRINTSTRING("INVALID IHEX LENGTH!!\n")
        }
        else if(INTELHEXCOMMAND_INVALID_COMMAND == ihexstatus){
            PRINTSTRING("INVALID IHEX COMMANDTYPE!\n")
        }
        else if(INTELHEXCOMMAND_BAD_CHECKSUM == ihexstatus){
            PRINTSTRING("INVALID IHEX CHECKSUM!\n")
        }
    }
    ////////////////////////////////////////////////
    else if(0 == strncmp(line, "verify", 6)){
        PRINTSTRING("Verify!\n")
    }
     ////////////////////////////////////////////////
        else if(0 == strncmp(line, "jump", 4)){
            PRINTSTRING("JUMP!\n")
            bootloader_jump_to_application();
        }

    ////////////////////////////////////////////////
    else if(0 == strncmp(line, "help", 4)){
        PRINTSTRING("Help!\n")
    }
    else{
        PRINTSTRING("Invalid Command!\n")
    }
}



static bool parse_erasesector_command(uint8_t * line, EraseSectorCommand_t * cmd){
    //erase sector 4
    if(line[13] < '0' || line[13] >= '9')
        return false;

    cmd ->sector_number = line[13] - '0';
    return true;
}