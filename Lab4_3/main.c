#include <reg52.h>
#include <stdio.h>
#include <intrins.h>

#include "init_serial.h"

unsigned char x _at_ 0x20;
unsigned int y _at_ 0x30;

int main() {
	init_serial();
	_nop_();

	y = x / 100;
	x %= 100;
	y <<= 4;
	y += x / 10;
	x %= 10;
	y <<= 4;
	y += x;

	printf("y = %x\n", y);

	for (; ; );
}
