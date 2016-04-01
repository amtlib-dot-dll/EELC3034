#include <reg52.h>

void init_serial(void) {
	SCON = 0x52;
	TMOD = 0x20;
	TCON = 0x69;
	TH1 = 0xF3;			     
	TR1 = 1;
}