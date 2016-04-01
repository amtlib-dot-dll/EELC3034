#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

int main() {
	init_serial();

	TMOD = (TMOD & 0xf0) | 0x6;
	TH0 = 0xff;
	TL0 = 0xff;
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	for (; ; );
}

void counter0_int(void) interrupt 1 {
	printf("interr\n");
}