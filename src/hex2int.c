//
// Created by steve on 6/21/21.
//

#include "hex2int.h"

uint8_t hex2int(uint8_t digit){
    if(digit >= '0' && digit <= '9')
        return digit - '0';

    if(digit <= 'F' && digit >= 'A')
        return 10 + (digit-'A');

    return 99;
}