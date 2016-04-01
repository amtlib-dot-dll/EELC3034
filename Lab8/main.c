#include <reg52.h>
#include <stdio.h>
#include <intrins.h>

#include "init_serial.h"

unsigned char xdata* AD_0809;
unsigned char bdata x, y;
sbit bit_x = x^7;
sbit bit_y = y^7;

sbit EOC = P1^0;

int main() {
	unsigned char (*p)();
	unsigned char* display_buffer;
	unsigned char n;

	init_serial();

	display_buffer = 0xc5;
	AD_0809 = 0x7fd0;
	p = 0x13c1;
	EOC = 1;

	for (n = 0; n <= 5; n++) {
		display_buffer[n] = 0x10;
	}

	for (; ; ) {
		*AD_0809 = 5;  
		while (EOC);
		while (!EOC);
		n = *AD_0809;
		display_buffer[0] = n >> 4;
		display_buffer[1] = n & 0xf;
		printf("n = %bx\n", n);
		p();
		p();
	}
}
