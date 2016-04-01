#include <reg52.h>
#include <stdio.h>
#include <intrins.h>

#include "init_serial.h"

unsigned char a _at_ 0x20;
unsigned char b _at_ 0x21;
unsigned char x _at_ 0x22;

#ifdef SECTION
#error
#endif
#if 0
#define SECTION code
#else
#define SECTION xdata
#endif
unsigned char SECTION square[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
#undef SECTION

int main() {
	init_serial();
	a = 5;
	b = 8;
	_nop_();

	x = square[a] + square[b];

	printf("a * a + b * b = %bd\n", x);

	for (; ; );
}
