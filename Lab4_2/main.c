#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

sbit T = P1^0;
sbit U = P1^1;
sbit V = P1^2;
sbit W = P1^3;
sbit X = P1^4;
sbit Y = P1^5;
sbit Z = P1^6;

unsigned char bdata F _at_ 0x24;
sbit Q = F^0;

int main() {
	init_serial();
	P1 = 0xff;
	Q = (U && (!(V || W))) || (X && Y) || Z || !T;

	printf("x = %#bX\n", (char)F);

	for (; ; );
}
