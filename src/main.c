#include "target/led.h"
#include "target/usart.h"
#include "printing_help.h"

void main(void){
    led_init();
    led_red_on();
    setup_usart();
    PRINTSTRING("STM32F4 BOOTLOADER\n")
}