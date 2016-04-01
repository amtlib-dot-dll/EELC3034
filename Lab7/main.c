#include <reg52.h>
#include <stdio.h>
#include <absacc.h>

#include "init_serial.h"

#define INPUT_IO (XBYTE[0x7fd0])

int main() {
	unsigned char x;
	init_serial();

	for (; ; ) {
		x = INPUT_IO;
		P1 = x;
		printf("x = %bu\n", x);
		while (x == INPUT_IO);
	}
}
