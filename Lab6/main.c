#include <reg52.h>
#include <stdio.h>
#include <intrins.h>

#include "init_serial.h"

void delay(int x) {
	while (x >= 0) {
		x--;
	}
}

sbit clk = P3^3;

int main() {
	unsigned char x = 1, i;
	clk = 0;
	P1 = 0;
	init_serial();

	for (; ; ) {
		for (i = 0; i <= 7; i++) {
			P1 = x;
			clk = 1;
			_nop_();
			clk = 0;
			printf("x = %bu\n", x);
			x <<= 1;
			delay(1000);
			delay(1000);
			delay(1000);
		}
		x = 1;
	}
}
