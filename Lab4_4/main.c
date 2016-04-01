#include <reg52.h>
#include <stdio.h>
#include <intrins.h>

#include "init_serial.h"

unsigned long x _at_ 0x20;

int main() {
	unsigned char* y = 0x30;

	init_serial();
	_nop_();

	x = 0xfd19ab7f;

	while (x) {
		*y = x % 10;
		x /= 10;
		*y += (x % 10) << 4;
		x /= 10;
		y++;
	}

	for (; ; );
}
