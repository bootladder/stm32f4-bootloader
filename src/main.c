#include "target/led.h"
#include "target/usart.h"
#include "printing_help.h"

#include "stm32f4xx_flash.h"

#include <stdint.h>
#include <stdbool.h>

FLASH_Status status;

extern volatile bool usart_rx_byte_received;
extern volatile uint8_t usart_rx_byte_value;

void main(void){
    led_init();
    led_red_on();
    setup_usart();
    PRINTSTRING("STM32F4 BOOTLOADER\n")

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
    PRINTSTRING("Done\n")


    while(1){
        if(usart_rx_byte_received){
            usart_rx_byte_received = false;
            outbyte(usart_rx_byte_value);
        }
//        int byte = inbyte();

    }

}