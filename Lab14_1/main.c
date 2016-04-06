#include <reg52.h>
#include <stdio.h>
#include <intrins.h>
#include <absacc.h>

#define OUTPUT 0
#define INPUT 0xff
#define OUT_IN 0xf
#define WR 0
#define RD 1
#define INVERT 0xff
#define NOINVERT 0
#define Input_reg 0
#define Output_reg 1
#define Polar_reg 2
#define Config_reg 3

sbit SCL_PCA9557 = P3^3;
sbit SDA_PCA9557 = P3^2;
bdata char com_data;
sbit mos_bit = com_data^7;
sbit low_bit = com_data^0;

unsigned char slave_addr = 0x30;

void delay(int n) {
    int i;
    for (i = 0; i < n; i++);
}

void start() {
    SDA_PCA9557 = 1;
    SCL_PCA9557 = 1;
    SDA_PCA9557 = 0;
    SCL_PCA9557 = 0;
}

void stop() {
    SDA_PCA9557 = 0;
    SCL_PCA9557 = 1;
    SDA_PCA9557 = 1;
}

void ack() {
    SCL_PCA9557 = 1;
    SCL_PCA9557 = 0;
}

void shift8(char a) {
    unsigned char i;
    com_data = a;
    for (i = 0; i < 8; i++) {
        SDA_PCA9557 = mos_bit;
        SCL_PCA9557 = 1;
        SCL_PCA9557 = 0;
        com_data *= 2;
    }
}

void WR_PCA9557(char slave_addr, char command, char data_in) {
    _nop_();
    SDA_PCA9557 = 1;
    SCL_PCA9557 = 0;
    start();
    shift8(slave_addr);
    ack();
    shift8(command);
    ack();
    shift8(data_in);
    ack();
    stop();
    _nop_();
}

void main() {
    unsigned char data_wr;
    data_wr = 1;
    for (; ;) {
        WR_PCA9557(slave_addr, Config_reg, OUTPUT);
        WR_PCA9557(slave_addr, Output_reg, ~data_wr);
        delay(20000);
        if (data_wr < 0x80) {
            data_wr <<= 1;
        } else {
            data_wr = 1;
        }
    }
}
