#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

int main() {
	init_serial();
	EA = 1;
	EX0 = 1;

	for (; ; );
}

void int0_int(void) interrupt 0 {
	printf("interr\n");
}