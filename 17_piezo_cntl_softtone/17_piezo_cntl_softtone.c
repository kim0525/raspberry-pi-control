#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <softTone.h>

const int pinPiezo = 13;
const int aMelody[8] = {523,587,659,698,783,880,987,1046};

int main(void)
{
    int j;
    wiringPiSetupGpio();

    softToneCreate(pinPiezo);

    while(1)
    {
        int i;
        for(i=0; i<8; i++)
        {
            softToneWrite(pinPiezo, aMelody[i]);
            delay(100);
        }
        softToneWrite(pinPiezo, 0);
        delay(1000);
    }

    return 0;
}

