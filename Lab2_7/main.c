#include <reg52.h>

sbit clk = P1^0;
sbit sda = P1^1;

int main() {
	clk = 1;
	sda = 0;
	for (; ; ) {
		clk = !clk;
		sda = !sda;
	}
}