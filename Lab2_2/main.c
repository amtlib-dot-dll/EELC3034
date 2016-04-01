#include <reg52.h>

int main() {
	unsigned char i;
	for (i = 0; i < 0xff; i++) {
		P1 = i;
	}
	
	for (; ; );
}