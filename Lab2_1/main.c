#include <reg52.h>
#include <stdio.h>

#include "init_serial.h"

int main() {
	unsigned char i, j;
	init_serial();
	for (i = 0; i < 0xff; i++) {
		j = P1;
		printf("j = %d\n", (int)j);
	}
	for (; ; );
}