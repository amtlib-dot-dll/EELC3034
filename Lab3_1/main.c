#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

unsigned long x _at_ 0x30;
unsigned long y _at_ 0x40;

int main() {
	init_serial();
	x = 0xc9f21f;
	y = 0x881809;

	y = x + y;

	printf("y = %lX and y = %ld", y, y);

	for (; ; );
}
