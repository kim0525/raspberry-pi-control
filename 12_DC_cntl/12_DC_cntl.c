#define CW      1
#define CCW     2
#define STOP    3
#define BREAK   4

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;

void DC_MOTOR_MODE(int mode);

int main(void)
{
    wiringPiSetupGpio();

    pinMode(pinEnable, OUTPUT);
    pinMode(pinPositive, OUTPUT);
    pinMode(pinNegative, OUTPUT);

    DC_MOTOR_MODE(CW);
    delay(3000);

    DC_MOTOR_MODE(BREAK);
    delay(3000);

    DC_MOTOR_MODE(CCW);
    delay(3000);

    DC_MOTOR_MODE(STOP);
    delay(3000);

    return 0;
}

void DC_MOTOR_MODE(int mode)
{
    switch(mode)
    {
        case CW:
            printf("CW\n");
            digitalWrite(pinPositive, HIGH);
            digitalWrite(pinNegative, LOW);
            digitalWrite(pinEnable, HIGH);
            break;
        case CCW:
            printf("CCW\n");
            digitalWrite(pinPositive, LOW);
            digitalWrite(pinNegative, HIGH);
            digitalWrite(pinEnable, HIGH);
            break;
        case STOP:
            printf("STOP\n");
            digitalWrite(pinPositive, LOW);
            digitalWrite(pinNegative, LOW);
            digitalWrite(pinEnable, LOW);
            break;
        case BREAK:
            printf("BREAK\n");
            digitalWrite(pinPositive, HIGH);
            digitalWrite(pinNegative, HIGH);
            digitalWrite(pinEnable, LOW);
            break;
    }
}