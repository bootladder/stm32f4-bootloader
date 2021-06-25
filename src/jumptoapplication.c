//
// Created by steve on 6/24/21.
//

#include "jumptoapplication.h"
#include "stm32f4xx.h"

#define APP_START_ADDRESS   0x08004000

//set msp and reset handler, jump
void jumptoapplication_jumptoapplication(void){
    __set_MSP(* ( (volatile uint32_t*) APP_START_ADDRESS));

    int32_t JumpAddress = *((volatile uint32_t *) (APP_START_ADDRESS + 4));

    void(*reset_handler)(void) = (void *) JumpAddress;
    reset_handler();
}
