#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

unsigned char x _at_ 0x30;
unsigned char y _at_ 0x31;

int main() {
	init_serial();
	x = 0x58;
	y = 0x9b;

	x = ((x & 0xf0) >> 4) | ((y & 0x0f) << 4);

	printf("x = %#bX\n", x);

	for (; ; );
}
