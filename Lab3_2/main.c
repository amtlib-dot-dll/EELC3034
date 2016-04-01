#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

unsigned long x _at_ 0x30;
unsigned long y _at_ 0x40;

int main() {
	init_serial();
	x = 0xf9ab2f;
	y = 0x57dc44;

	y = x - y;

	printf("y = %lX and y = %ld", y, y);

	for (; ; );
}
