#include "target/led.h"
#include "target/usart.h"
#include "printing_help.h"

#include "stm32f4xx_flash.h"
#include "commandlineprotocol.h"
#include "bootloader.h"

#include <stdint.h>
#include <stdbool.h>

FLASH_Status status;

extern volatile bool usart_rx_byte_received;
extern volatile uint8_t usart_rx_byte_value;

static uint32_t readLineIndex = 0;

static void readLine(uint8_t * buf);

void main(void){
    led_init();
    led_red_on();
    setup_usart();

    FLASH_Unlock();

//    status = FLASH_EraseSector(FLASH_Sector_1, VoltageRange_3);
//
//    if(status == FLASH_COMPLETE)
//        PRINTSTRING("ERASE COMPLETE\n")
//    else
//        PRINTSTRING("ERASE  NOT COMPLETE\n")
//
//    status =
//            FLASH_ProgramWord(0x08004000, 0x12345678);
//
//    if(status == FLASH_COMPLETE)
//        PRINTSTRING("WRITE COMPLETE\n")
//    else
//        PRINTSTRING("WRITE NOT COMPLETE\n")
//

//    FLASH_Lock();
//    PRINTSTRING("Done\n")


    bootloader_print_welcome();  // name, version, config
    bootloader_print_app_status();  //description, validity, sizes, checksum
//    bootloader_print_initial_prompt();  // "press any key"

//    if(NO_USER_INPUT == prompt_and_wait_for_any_input(1000)){
//        bootloader_run_user_application();
//    }

    // else serve CLI interface

    static uint8_t lineBuf[256];

    while(1){
        readLine(lineBuf);
        commandlineprotocol_processLine(lineBuf);
    }

}

static void readLine(uint8_t * buf){

    while(1){
        while(false == usart_rx_byte_received)
            ;

        usart_rx_byte_received = false;
        outbyte(usart_rx_byte_value);

        if(usart_rx_byte_value == '\n'){
            buf[readLineIndex++] = usart_rx_byte_value;
            readLineIndex = 0;
            break;
        }

        buf[readLineIndex++] = usart_rx_byte_value;
        if(readLineIndex == 256)
            readLineIndex = 0;
    }

}
