#include <reg52.h>
#include <stdio.h>
#include <intrins.h>
#include <absacc.h>

#include "init_serial.h"

void delay(int x) {
	while (x >= 0) {
		x--;
	}
}

unsigned char d[6] _at_ 0x50;

#define SEGMENT XBYTE[0x7f80]
#define BIT_LED XBYTE[0x7f90]

unsigned char code seg_code[] = {
	0x3f,
	0x06,
	0x5b,
	0x4f,
	0x66,
	0x6d,
	0x7d,
	0x07,
	0x7f,
	0x67,
	0x77,
	0x7c,
	0x39,
	0x5e,
	0x79,
	0x71,
	0x00
};


int main() {
	unsigned char i, display_bit;
	init_serial();

	for (i = 0; i <= 5; i++) {
		d[i] = i + 1;
	}

	_nop_();

	display_bit = 1;
	i = 0;

	while (i <= 5) {
		SEGMENT = seg_code[d[i]];
		BIT_LED = display_bit;
		printf("%bx", d[i]);
		delay(3);
		BIT_LED = 0;
		display_bit <<= 1;
		if (display_bit > 32) {
			display_bit = 1;
		}
		i++;
		if (i >= 6) {
			i = 0;
			printf("\n");
		}
	}
}
