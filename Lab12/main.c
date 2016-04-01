#include <reg52.h>

sbit CS = P1^0;
sbit CLK = P1^1;
sbit DIO = P1^2;
unsigned char rebuf, sebuf, a, b, c;
bdata unsigned char com_data;
sbit mos_bit = com_data^7;
sbit low_bit = com_data^0;

void delay_50us(void) {
    unsigned char i;
    for (i = 0; i < 6; i++);
}

void delay_8us(void) {
    unsigned char i;
    for (i = 0; i < 1; i++);
}

void send(unsigned char sebuf) {
    unsigned char i;
    CS = 0;
    delay_50us();
    for (i = 0; i < 8; i++) {
        com_data = sebuf;
        sebuf = com_data << 1;
        DIO = mos_bit;
        CLK = 1;
        delay_8us();
        CLK = 0;
        delay_8us();
    }
    DIO = 0;
}

void receive(void) {
    unsigned char i;
    DIO = 1;
    delay_50us();
    for (i = 0; i < 8; i++) {
        CLK = 1;
        delay_8us();
        low_bit = DIO;
        com_data <<= 1;
        rebuf = com_data;
        CLK = 0;
        delay_8us();
    }
    DIO = 0;
    CS = 1;
}

int main() {
	EA = 1;
	EX0 = 1;
	IT0 = 1;

    sebuf = 0xbf;
    send(sebuf);
    delay_50us();
    CS = 1;
    send(0xa4);
    delay_50us();
    CS = 1;
    for (; ;);
}

void key_int(void) interrupt 0 {
    send(0x15);
    delay_50us();
    receive();
    delay_50us();
    CS = 1;
    rebuf >>= 1;

	switch (rebuf % 4) {
		case 0:
			a = 1;
			b = 2;
			break;
		case 1:
			a = 0;
			b = 8;
			break;
		case 2:
			a = 2;
			b = 0;
			break;
		case 3:
			a = 0;
			b = 5;
			break;
	}

    send(0xa1);
    delay_50us();
    CS = 1;
    send(0xa1);
    delay_50us();
    CS = 1;
    send(0x81);
    delay_50us();
    send(a);
    delay_50us();
    CS = 1;
    send(0x80);
    delay_50us();
    send(b);
    delay_50us();
    CS = 1;
    send(0x88);
    delay_50us();
    send(0);
    CS = 1;
    send(0x88);
    delay_50us();
    send(0xfc);
    CS = 1;
}
