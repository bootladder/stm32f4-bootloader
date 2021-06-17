//
// Created by steve on 6/17/21.
//

#include <src/target/usart.h>
#include "commandlineprotocol.h"
#include "printing_help.h"
void commandlineprotocol_processLine(uint8_t * line){

    if(line[0] == 'a'){
       PRINTSTRING("Good Comamand!\n")
    }
    else{
        PRINTSTRING("Commands must start with 'a', not ... ")
        outbyte(line[0]);
    }
}