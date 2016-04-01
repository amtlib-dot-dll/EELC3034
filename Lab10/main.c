#include <at89x52.h>
#include <stdio.h>
#include <absacc.h>
#include <intrins.h>

#define SEGMENT (XBYTE[0x7f80])
#define BIT_LED (XBYTE[0x7f90])
#define FOSC 11.0592
#define TIME0 2500

unsigned char data display_bit, display_buffer[8], time0_h, time0_l, temp;
unsigned int idata time0_times;

unsigned char get_code(unsigned char i) {
    switch (i) {
        case 0:
            return 0x3f;
        case 1:
            return 0x06;
        case 2:
            return 0x5b;
        case 3:
            return 0x4f;
        case 4:
            return 0x66;
        case 5:
            return 0x6d;
        case 6:
            return 0x7d;
        case 7:
            return 0x07;
        case 8:
            return 0x7f;
        case 9:
            return 0x67;
        case 10:
            return 0x77;
        case 11:
            return 0x7c;
        case 12:
            return 0x39;
        case 13:
            return 0x5e;
        case 14:
            return 0x79;
        case 15:
            return 0x71;
        default:
            return 0;
    }
}

void display(void) {
    unsigned char i;
    switch (display_bit) {
        case 1:
            i = 0;
            break;
        case 2:
            i = 1;
            break;
        case 4:
            i = 2;
            break;
        case 8:
            i = 3;
            break;
        case 16:
            i = 4;
            break;
        case 32:
            i = 5;
            break;
        case 64:
            i = 6;
            break;
        case 128:
            i = 7;
            break;
        default:;
    }
    BIT_LED = 0;
    SEGMENT = get_code(display_buffer[i]);
    BIT_LED = display_bit;
    display_bit = display_bit <= 64 ? display_bit << 1 : 1;
}

sbit SCL_DS1302 = P1^0;
sbit IO_DS1302 = P1^1;
sbit RST_DS1302 = P1^2;

unsigned char bdata data_ds1302;
sbit bit_data0 = data_ds1302^0;
sbit bit_data7 = data_ds1302^7;

unsigned char bdata x;
sbit x0 = x^0;
sbit x7 = x^7;

void initial_ds1302(void) {
    unsigned char i;
    SCL_DS1302 = 0;
    _nop_();
    RST_DS1302 = 1;
    _nop_();
    _nop_();
    data_ds1302 = 0x8e;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    data_ds1302 = 0;
    IO_DS1302 = 0;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    RST_DS1302 = 0;
    _nop_();
    SCL_DS1302 = 0;
    SCL_DS1302 = 0;
    _nop_();
    RST_DS1302 = 1;
    _nop_();
    _nop_();
    data_ds1302 = 0x90;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    data_ds1302 = 0xa4;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    RST_DS1302 = 0;
    _nop_();
    SCL_DS1302 = 0;
    SCL_DS1302 = 0;
    _nop_();
    RST_DS1302 = 1;
    _nop_();
    _nop_();
    data_ds1302 = 0x8e;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    data_ds1302 = 0x80;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    RST_DS1302 = 0;
    _nop_();
    SCL_DS1302 = 0;
}

unsigned char read_ds1302(char command) {
    char i;
    data_ds1302 = (command << 1) | 0x81;
    SCL_DS1302 = 0;
    _nop_();
    RST_DS1302 = 1;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    SCL_DS1302 = 1;
    for (i = 1; i <= 8; i++) {
        data_ds1302 >>= 1;
        SCL_DS1302 = 0;
        _nop_();
        bit_data7 = IO_DS1302;
        SCL_DS1302 = 1;
    }
    RST_DS1302 = 0;
    _nop_();
    SCL_DS1302 = 0;
    return data_ds1302;
}

void write_ds1302(unsigned char address, unsigned char numb) {
    char i;
    RST_DS1302 = 0;
    SCL_DS1302 = 0;
    RST_DS1302 = 0;
    RST_DS1302 = 1;
    data_ds1302 = 0x80 | (address << 1);

    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    data_ds1302 = numb;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    RST_DS1302 = 0;
    SCL_DS1302 = 1;
}

void open_write_bit(void) {
    char i;
    SCL_DS1302 = 0;
    _nop_();
    RST_DS1302 = 1;
    _nop_();
    _nop_();
    data_ds1302 = 0x8e;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    data_ds1302 = 0;
    IO_DS1302 = 0;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
}

void close_write_bit(void) {
    char i;
    SCL_DS1302 = 0;
    _nop_();
    RST_DS1302 = 1;
    _nop_();
    _nop_();
    data_ds1302 = 0x8e;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
    data_ds1302 = 0x80;
    IO_DS1302 = 0;
    for (i = 1; i <= 8; i++) {
        SCL_DS1302 = 0;
        IO_DS1302 = bit_data0;
        _nop_();
        SCL_DS1302 = 1;
        data_ds1302 >>= 1;
    }
}

void read_time(void) {
    unsigned char second, minute, hour, d;
    second = 0;
    d = read_ds1302(second);
    display_buffer[0] = d & 0x0f;
    display_buffer[1] = d >> 4;
    minute = 1;
    d = read_ds1302(minute);
    display_buffer[2] = d & 0x0f;
    display_buffer[3] = d >> 4;
    hour = 2;
    d = read_ds1302(hour);
    display_buffer[4] = d & 0x0f;
    display_buffer[5] = d >> 4;
}

void set_time(void) {
    unsigned char data hour_address, minute_address, second_address;
    hour_address = 2;
    minute_address = 1;
    second_address = 0;
    open_write_bit();
    temp = (display_buffer[5] << 4) | display_buffer[4];
    write_ds1302(hour_address, temp);
    temp = (display_buffer[3] << 4) | display_buffer[2];
    write_ds1302(minute_address, temp);
    temp = (display_buffer[1] << 4) | display_buffer[0];
    write_ds1302(second_address, temp);
    close_write_bit();
}

int main() {
    BIT_LED = 0;
    temp = TMOD;
    temp &= 0xf0;
    TMOD = temp | 1;
    time0_times = -TIME0 * FOSC / 12;
    time0_h = time0_times / 256;
    time0_l = time0_times % 256;
    TH0 = time0_h;
    TL0 = time0_l;
    TR0 = EA = ET0 = 1;
    initial_ds1302();
    display_bit = 1;
    display_buffer[0] = 0x08;
    display_buffer[1] = 0x05;
    display_buffer[2] = 0x05;
    display_buffer[3] = 0x03;
    display_buffer[4] = 0x09;
    display_buffer[5] = 0x00;
    set_time();

    for (; ;) {
        read_time();
    }
}

void time0_int(void) interrupt 1 {
    TH0 = time0_h;
    TL0 = time0_l;
    display();
}
