#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int pinPiezo = 13;
const int pinSwitch0 = 5;
const int aMelody[8] = {523,587,659,698,783,880,987,1046};
float delay_val = 0.0;

void change_oct(void);

int main(void)
{
    int i, j;
    wiringPiSetupGpio();

    pinMode(pinPiezo, OUTPUT);
    pinMode(pinSwitch0, INPUT);

    wiringPiISR(pinSwitch0, INT_EDGE_RISING, change_oct);

    while(1)
    {
        digitalWrite(pinPiezo, HIGH);
        delayMicroseconds((int)delay_val);
        digitalWrite(pinPiezo, LOW);
        delayMicroseconds((int)delay_val);
    }

    return 0;
}

void change_oct(void)
{
    static int cnt=0;
    delay_val = ((1.0/aMelody[cnt]) * 1000000.0) / 2.0;
    if(cnt==7)  cnt = 0;
    else cnt++;
}