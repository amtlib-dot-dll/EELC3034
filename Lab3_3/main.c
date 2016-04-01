#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

unsigned long x _at_ 0x30;
unsigned long y _at_ 0x40;

int main() {
	init_serial();
	x = 0xf012;
	y = 0x5678;

	x *= y;

	printf("x = %lX and x = %ld", x, x);

	for (; ; );
}
