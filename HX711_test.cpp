#include "mbed.h"
#include <stdio.h>
#include <math.h>

// Serial connection to pc
Serial pc(USBTX, USBRX);

// Serial connection to Nucleo F334R8
RawSerial dev(PA_2, PA_3);

// LED to display status
DigitalOut led1(LED1);

AnalogOut aout1(PA_4);
AnalogOut aout2(PA_6);

DigitalInOut dio1(PA_0);
DigitalInOut dio2(PA_1);

int main()
{   
    pc.baud(38400);
    dev.baud(38400);
    aout1=0.5f;
    aout2=0.5f;
    led1=1;
    dio1.output();
    dio2.input();
    dio1.mode(PullUp);
    dio2.mode(PullUp);
    int counter=0;
    while(1) {
        if(dio2.read()) {
            continue;
        }
        int a = 0;
        for(int i = 0; i < 27; i++) {
            dio1=1;
            wait_us(1);
            dio1=0;
            if (i<24) {
                a*=2;
                a+=dio2.read();
            }
            wait_us(1);
        }
        counter+=1;
        aout2=0.5+0.0075f*sin(0.02*counter);
        wait_ms(10);
        pc.printf("%8.8x\n\r",a);            
        dio1=0;
    }
}
