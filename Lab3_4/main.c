#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

unsigned long x _at_ 0x30;
unsigned int y _at_ 0x40;
unsigned int z _at_ 0x50;
unsigned int w _at_ 0x52;

int main() {
	init_serial();
	x = 0x90000000;
	y = 0xafff;

	z = x / y;
	w = x % y;

	printf("quotient = %X remainder = %X\n", z, w);
	printf("quotient = %Ld remainder = %d\n", (long)z, w);

	for (; ; );
}
