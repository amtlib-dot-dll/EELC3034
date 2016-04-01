#include <reg52.h>
#include <stdio.h>
#include <intrins.h>

#include "init_serial.h"

unsigned char (*read_key)();

unsigned char x _at_ 0x20;
unsigned char y _at_ 0x21;
unsigned int z _at_ 0x30;

int main() {
	unsigned char w;
	init_serial();
	read_key = 0x135a;

	for (; ; ) {
		x = 0xed;
		y = 0x5a;
		read_key();
		w = ACC;
		switch (w) {
			case 0:
				z = x + y;
				break;
			case 1:
				z = x - y;
				break;
			case 2:
				z = x * y;
				break;
			case 3:
				z = x / y;
				break;
			default:
				z = 0;
		}
		printf("z = %x\n", z);
	}
}
