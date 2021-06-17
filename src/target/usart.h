/*
 * usart.h -usart support for STM32F405 Codec V2
 * 06-26-2014 E. Brombaugh
 */

#ifndef __usart__
#define __usart__

void setup_usart(void);
int outbyte(int ch);
int inbyte(void);
int hexdigit_2_asciichar(int hex);

#endif
