#include <reg52.h>
#include <stdio.h>

sbit clk = P1^0;
sbit sda = P1^1;

void time0_int(void) interrupt 1 {
	clk = !clk;
	sda = !sda;
}

int main() {
	TMOD = (TMOD & 0xf0) | 0x2;
	TH0 = 0;
	TL0 = 0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	
	clk = 1;
	sda = 0;
 
	for (; ; );
}
