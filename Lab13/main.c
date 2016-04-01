#include <reg52.h>
#include <stdio.h>
#include <absacc.h>
#include <intrins.h>

#include "init_serial.h"

sbit SCL_IC_CARD = P1^0;
sbit SDA_IC_CARD = P1^1;
sbit WP_IC_CARD = P1^2;

bdata char com_data;
sbit mos_bit = com_data^7;
sbit low_bit = com_data^0;

unsigned char data display_buffer[3] _at_ 0x40;

unsigned char data b_buffer[3] _at_ 0x50;
unsigned char idata a_buffer[6] _at_ 0xc5;

void delay(int n) {
    int i;
    for (i = 0; i < n; i++);
}

void start(void) {
    SDA_IC_CARD = 1;
    SCL_IC_CARD = 1;
    SDA_IC_CARD = 0;
    SCL_IC_CARD = 0;
}

void stop(void) {
    SDA_IC_CARD = 0;
    SCL_IC_CARD = 1;
    SDA_IC_CARD = 1;
}

void ack(void) {
    SCL_IC_CARD = 1;
    SCL_IC_CARD = 0;
}

void shift8(char a) {
    data unsigned char i;
    com_data = a;
    for (i = 0; i < 8; i++) {
        SDA_IC_CARD = mos_bit;
        SCL_IC_CARD = 1;
        SCL_IC_CARD = 0;
        com_data *= 2;
    }
}

unsigned char rd_24c01(char a) {
    data unsigned char i, command;
    SDA_IC_CARD = 1;
    SCL_IC_CARD = 0;
    start();
    command = 0xa0;
    shift8(command);
    ack();
    shift8(a);
    ack();
    start();
    command = 0xa1;
    shift8(command);
    ack();
    SDA_IC_CARD = 1;
    for (i = 0; i < 8; i++) {
        com_data *= 2;
        SCL_IC_CARD = 1;
        low_bit = SDA_IC_CARD;
        SCL_IC_CARD = 0;
    }
    stop();
    return com_data;
}

void wr_24c01(char a, char b) {
    data unsigned char command;
    WP_IC_CARD = 0;
    _nop_();
    SDA_IC_CARD = 1;
    SCL_IC_CARD = 0;
    start();
    command = 0xa0;
    shift8(command);
    ack();
    shift8(a);
    ack();
    shift8(b);
    ack();
    stop();
    _nop_();
    WP_IC_CARD = 1;
}

int main() {
    unsigned char i;
    unsigned char (*r)();
    init_serial();
    WP_IC_CARD = 1;
    r = 0x13c1;
    printf("\n");

    for (i = 0; i <= 2; i++) {
        wr_24c01(i, display_buffer[i]);
        delay(250);
    }

    printf("\nData read: ");
    for (i = 0; i <= 2; i++) {
        b_buffer[i] = rd_24c01(i);
        printf("%bX", b_buffer[i]);
        delay(250);
    }

    for (; ;) {
        for (i = 0; i <= 2; i++) {
            a_buffer[2 * i] = (b_buffer[i] & 0xf0) >> 4;
            a_buffer[2 * i + 1] = b_buffer[i] & 0xf;
        }
        r();
    }
}
