#define EXTRA 1
#include <reg51.h>
#include <stdio.h>
#include <absacc.h>
#include <intrins.h>

#include "init_serial.h"

sbit TMDAT = P1^0;

#define SEGMENT (XBYTE[0x7f80])
#define BIT_LED (XBYTE[0x7f90])

unsigned char code seg_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00};

void dmsec(unsigned int count) {
    unsigned int i;
    while (count--) {
        for (i = 0; i < 125; i++);
    }
}

void tmreset(void) {
    unsigned int i;
    TMDAT = 0;
    i = 103;
    for (; i > 0; i--);
    TMDAT = 1;
    i = 4;
    for (; i > 0; i--);
}

void tmpre(void) {
    unsigned int i;
    while (TMDAT);
    while (~TMDAT);
    i = 4;
    for (; i > 0; i--);
}

bit tmrbit(void) {
    unsigned int i;
    bit dat;
    TMDAT = 0;
    i++;
    TMDAT = 1;
    i++;
    i++;
    dat = TMDAT;
    i = 8;
    for (; i > 0; i--);
    return dat;
}

unsigned char tmrbyte(void) {
    unsigned char i, j, dat;
    dat = 0;
    for (i = 0; i < 8; i++) {
        j = tmrbit();
        dat = j << 7 | dat >> 1;
    }
    return dat;
}

void tmwbyte(unsigned char dat) {
    unsigned int i;
    unsigned char j;
    bit testb;
    for (j = 0; j < 8; j++) {
        testb = dat & 1;
        dat >>= 1;
        if (testb) {
            TMDAT = 0;
            i++;
            i++;
            TMDAT = 1;
            i = 8;
            for (; i > 0; i--);
        } else {
            TMDAT = 0;
            i = 8;
            for (; i > 0; i--);
            TMDAT = 1;
            i++;
            i++;
        }
    }
}

void tmstart(void) {
    tmreset();
    tmpre();
    dmsec(1);
    tmwbyte(0xcc);
    tmwbyte(0x44);
}

unsigned int tmrtemp(void) {
    unsigned char a, b;
    tmreset();
    tmpre();
    dmsec(1);
    tmwbyte(0xcc);
    tmwbyte(0xbe);
    a = tmrbyte();
    b = tmrbyte();
    return b << 8 | a;
}

int main() {
    unsigned int last;
	unsigned char (*p)();
	unsigned char* display_buffer;

	display_buffer = 0xc5;
	p = 0x13c1;

    init_serial();

    for (; ;) {
        dmsec(1);
        tmstart();
        dmsec(1);
        last = tmrtemp();
#if !EXTRA
        printf("The current temperature: %u\n", last);
#endif
		display_buffer[2] = (char)((double)(last % 16) / 16 * 10);
		last /= 16;
		display_buffer[1] = (last % 10) | 0x80;
		last /= 10;
		display_buffer[0] = last % 10;
		last /= 10;
		p();
    }
}
