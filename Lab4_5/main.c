#include <reg52.h>
#include <stdio.h>
#include <intrins.h>

#include "init_serial.h"

unsigned char x _at_ 0x20;
unsigned char y _at_ 0x30;

int main() {
	init_serial();
	_nop_();

	x = 0x05;

	x &= 0x0f;
	y = x + (x > 9 ? 0x37 : 0x30);

	printf("y = %bx\n", y);

	for (; ; );
}
