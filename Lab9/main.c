#define WAVEFORM_SINE 0
#define WAVEFORM_RECTANGULAR 1
#define WAVEFORM_SAW 2
#define WAVEFORM_TRIANGLE 3
#define WAVEFORM WAVEFORM_SINE

#define EXTRA 1
#define TIME 100

#include <reg52.h>
#include <stdio.h>
#include <absacc.h>
#include <intrins.h>

#if WAVEFORM == WAVEFORM_SINE
#include <math.h>
#endif

#include "init_serial.h"

#define FOSC 11.0592
#define N_CONSTENT 10
#define NUMBER (360 / N_CONSTENT)
#define DA0832 (XBYTE[0x7fc0])

unsigned char data x[NUMBER];

#if EXTRA
void time0_int(void) interrupt 1 {
	static unsigned char i;
	i++;
	i %= NUMBER;
	DA0832 = x[i];
}
#endif

int main() {
    unsigned char i;

    init_serial();

#if WAVEFORM == WAVEFORM_SINE
    for (i = 0; i < NUMBER; i++) {
        x[i] = 100 * sin(i * N_CONSTENT * 3.1415926535897932384626433832795 / 180) + 128;
    }
#elif WAVEFORM == WAVEFORM_RECTANGULAR
    for (i = 0; i < NUMBER / 2; i++) {
        x[i] = 0;
    }
    for (i = NUMBER / 2; i < NUMBER; i++) {
        x[i] = 2 * NUMBER;
    }
#elif WAVEFORM == WAVEFORM_SAW
    for (i = 0; i < NUMBER; i++) {
        x[i] = 2 * i;
    }
#elif WAVEFORM == WAVEFORM_TRIANGLE
    for (i = 0; i < NUMBER / 2; i++) {
        x[i] = 4 * i;
    }
    for (i = NUMBER / 2; i < NUMBER; i++) {
        x[i] = 4 * (NUMBER - i);
    }
#endif

#if EXTRA
	TMOD = (TMOD & 0xf0) | 0x2;
	TH0 = TL0 = (unsigned char)(0xff - 1.0 * TIME * FOSC / 12);
	printf("%u\n", (unsigned int)(0xff - 1.0 * TIME * FOSC / 12));
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	for (; ;);
#else
    for (; ;) {
        for (i = 0; i < NUMBER; i++) {
            DA0832 = x[i];
            printf("x[%bd] = %bd\n", i, x[i]);
        }
    }
#endif
}
