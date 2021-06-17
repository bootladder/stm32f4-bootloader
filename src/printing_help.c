//
// Created by steve on 1/4/21.
//

#include "printing_help.h"
#include "target/usart.h"

static void float2string(float fVal, uint8_t * buf);
char * utox(uint32_t n);

void printbuf(uint8_t * buf, int size){
    for(int i=0; i<size; i++){
        outbyte(buf[i]);
    }
}

void printnewline(){
    printbuf(NEWLINE, 1);
}


void printfloat(float f) {
    static uint8_t buf[100];
    float2string(f, buf);
    for(int i=0; i<10; i++){
        outbyte(buf[i]);
    }
}

//stolen from stackoverflow
static void float2string(float fVal, uint8_t * buf)
{
    char result[100];
    int dVal, dec, i;

    fVal += 0.005;   // added after a comment from Matt McNabb, see below.

    dVal = fVal;
    dec = (int)(fVal * 100) % 100;

    //memset(result, 0, 100);
    for(int i=0; i<100; i++){
        result[i] = 0;
    }
    result[0] = (dec % 10) + '0';
    result[1] = (dec / 10) + '0';
    result[2] = '.';

    i = 3;
    while (dVal > 0)
    {
        result[i] = (dVal % 10) + '0';
        dVal /= 10;
        i++;
    }

    //result is in reverse order
    // load the reverse into buf

    int bufindex = 0;
    for(int j=i; j>=0; j--){
        buf[bufindex++] = result[j];
    }
//
//    for (i=strlen(buf)-1; i>=0; i--)
//        putc(buf[i], stdout);
}


void printint(int input){
    char * buf =utox(input);
    for(int i=0; i<10; i++){
        outbyte(buf[i]);
    }
}


//stolen from stackoverflow
char * utox(uint32_t n) {
    static char hexstr[sizeof(n)*2+1];
    char * p = hexstr + sizeof(hexstr) -1;
    int x;

    //memset(hexstr, '0', sizeof(hexstr));
    for(int i=0; i<sizeof(hexstr); i++){
        hexstr[i] = '0';
    }

    *p-- = '\0';

    while (n) {
        x = n % 16;
        if (x < 10)
            *p-- = '0' + x;
        else
            *p-- = 'A' + x - 10;

        n /= 16;
    }

    return hexstr;
}
