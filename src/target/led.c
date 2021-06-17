#include "stm32f4xx.h"


void led_red_on() {
    GPIO_SetBits(GPIOC, GPIO_Pin_10);
}

void led_red_off() {
    GPIO_ResetBits(GPIOC, GPIO_Pin_10);
}



void led_init() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef gpioCDef;
    gpioCDef.GPIO_Mode = GPIO_Mode_OUT;
    gpioCDef.GPIO_OType = GPIO_OType_PP;
    gpioCDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioCDef.GPIO_Pin = GPIO_Pin_10;
    gpioCDef.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &gpioCDef);

    GPIO_ResetBits(GPIOC, GPIO_Pin_10);

    gpioCDef.GPIO_Mode = GPIO_Mode_OUT;
    gpioCDef.GPIO_OType = GPIO_OType_PP;
    gpioCDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioCDef.GPIO_Pin = GPIO_Pin_11;
    gpioCDef.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &gpioCDef);

    GPIO_ResetBits(GPIOC, GPIO_Pin_11);

    gpioCDef.GPIO_Mode = GPIO_Mode_OUT;
    gpioCDef.GPIO_OType = GPIO_OType_PP;
    gpioCDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioCDef.GPIO_Pin = GPIO_Pin_12;
    gpioCDef.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &gpioCDef);

    GPIO_ResetBits(GPIOC, GPIO_Pin_12);
}