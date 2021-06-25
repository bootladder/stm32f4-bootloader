//
// Created by steve on 6/24/21.
//

#include "applicationmanager.h"
#include "stm32f4xx.h"
#include <stdbool.h>

#define APP_START_ADDRESS   0x08004000

//set msp and reset handler, jump
void applicationmanager_jumptoapplication(void){
    __set_MSP(* ( (volatile uint32_t*) APP_START_ADDRESS));

    int32_t JumpAddress = *((volatile uint32_t *) (APP_START_ADDRESS + 4));

    void(*reset_handler)(void) = (void *) JumpAddress;
    reset_handler();
}


bool applicationmanager_is_app_loaded(void){
    //check the first parts of sector 1, start of app,
    //for non-erased bits
    volatile uint32_t * app_start = ((volatile uint32_t *) (APP_START_ADDRESS));
    for(int i=0; i<16; i++){
        if(app_start[i] != 0xFFFFFFFF)
            return true;
    }

    return false;
}

bool applicationmanager_is_valid_reset_vector(void){
    // if the reset vector points into a valid flash address,
    // outside of sector 0, bootloader region
    int32_t JumpAddress = *((volatile uint32_t *) (APP_START_ADDRESS + 4));
    if(JumpAddress >= 0x08000000 && JumpAddress < 0x08004000)
        return false;

    if(JumpAddress < 0x08000000)
        return false;

    return true;
}

uint32_t applicationmanager_get_reset_handler_addr(void){
    int32_t JumpAddress = *((volatile uint32_t *) (APP_START_ADDRESS + 4));
    return JumpAddress;
}