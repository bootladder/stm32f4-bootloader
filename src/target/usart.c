/*
 * usart.c -usart support for STM32F405 Codec V2
 * 06-26-2014 E. Brombaugh
 */
/*
 *
		//int c = inbyte();
        //usart_input_value = (uint8_t)c;
		//outbyte(c);

 */

#include "usart.h"
#include "stm32f4xx.h"
#include <stdbool.h>

volatile bool usart_rx_byte_received = false;
volatile uint8_t usart_rx_byte_value ;

/* USART setup */
void setup_usart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Setup USART */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Connect PB6 to USART1_Tx */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

	/* Connect PB7 to USART1_Rx */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART configuration */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* USART = 115k-8-N-1 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	/* Enable USART */
	USART_Cmd(USART1, ENABLE);


	// Interupts
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART1_IRQn);

}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int outbyte(int ch)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, (uint8_t) ch);

	/* Loop until transmit data register is empty */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	{}

	return ch;
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int inbyte(void)
{
    //blocking wait for byte.  While the "not empty flag" is "not set", the buffer is "empty"
    while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_RXNE));

    uint16_t c = USART_ReceiveData(USART1);
    return c;
}


int hexdigit_2_asciichar(int hex) {
    if(hex < 10)
        return '0' + hex;
    return 'A' + (hex - 10);
}



void USART1_IRQHandler(void){
    usart_rx_byte_received = true;
    USART_ClearFlag(USART1, USART_FLAG_RXNE);

    usart_rx_byte_value = USART_ReceiveData(USART1);
}
