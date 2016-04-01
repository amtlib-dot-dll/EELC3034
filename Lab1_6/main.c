#include <reg52.h>

sbit clk = P1^0;

int main() {
	for (; ; ) {
		clk = !clk;	
	}
}