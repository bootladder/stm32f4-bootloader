//
// Created by steve on 1/4/21.
//

#ifndef SHREDDINGERSBOX_PRINTING_HELP_H
#define SHREDDINGERSBOX_PRINTING_HELP_H

#include <stdint.h>
#define NEWLINE (uint8_t *)"\n"
#define PRINTSTRING(a) printbuf((uint8_t *)a , sizeof(a) - 1); //null terminator
#define PRINTBYTE(a) printbuf((uint8_t *) &a , 1);

void printbuf(uint8_t * buf, int size);
void printfloat(float f);
void printint(int i);
void printnewline();

#endif //SHREDDINGERSBOX_PRINTING_HELP_H
