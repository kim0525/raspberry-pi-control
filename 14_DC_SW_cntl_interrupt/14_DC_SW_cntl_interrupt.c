#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;
const int pinSwitch0 = 5;
const int pinSwitch1 = 6;

void motorSpin(void);
void motorStop(void);

int main(void)
{
    wiringPiSetupGpio();

    pinMode(pinEnable, OUTPUT);
    pinMode(pinPositive, OUTPUT);
    pinMode(pinNegative, OUTPUT);
    pinMode(pinSwitch0, INPUT);
    pinMode(pinSwitch1, INPUT);

    wiringPiISR(pinSwitch0, INT_EDGE_RISING, motorSpin);
    wiringPiISR(pinSwitch1, INT_EDGE_RISING, motorStop);

    while(1);

    return 0;
}

void motorSpin(void)
{
    //printf("CW\n");
    digitalWrite(pinPositive, HIGH);
    digitalWrite(pinNegative, LOW);
    digitalWrite(pinEnable, HIGH);
}
void motorStop(void)
{
    digitalWrite(pinEnable, LOW);
}