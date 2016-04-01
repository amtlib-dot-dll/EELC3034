#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

int main() {
	init_serial();

	TMOD = (TMOD & 0xf0) | 0x2;
	TH0 = -200;
	TL0 = -200;
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	for (; ; );
}

void time0_int(void) interrupt 1 {
	printf("interr\n");
}