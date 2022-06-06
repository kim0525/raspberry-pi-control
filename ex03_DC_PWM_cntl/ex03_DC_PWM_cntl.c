#define period  100
#define unit    period/10

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <softPwm.h>

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;
const int pinSwitch0 = 5;
const int pinSwitch1 = 6;

int duty = 10;

void DC_MOTOR_DN(void);
void DC_MOTOR_UP(void);

int main(void)
{
    wiringPiSetupGpio();

    pinMode(pinSwitch0, INPUT);
    pinMode(pinSwitch1, INPUT);

    pinMode(pinEnable, OUTPUT);
    pinMode(pinPositive, OUTPUT);
    pinMode(pinNegative, OUTPUT);

    digitalWrite(pinEnable, HIGH);
    digitalWrite(pinPositive, HIGH);
    digitalWrite(pinNegative, LOW);

    wiringPiISR(pinSwitch0, INT_EDGE_RISING, DC_MOTOR_DN);
    wiringPiISR(pinSwitch1, INT_EDGE_RISING, DC_MOTOR_UP);

    softPwmCreate(pinEnable, duty, period);   //(핀번호, 초기설정값, 주기값(100us))

    while(1);

    return 0;
}

void DC_MOTOR_DN(void)
{
    if(duty > 0)
        duty -= unit;
    else
        duty = 0;

    softPwmWrite(pinEnable, duty);
    printf("dyty = %d\n", duty);
}

void DC_MOTOR_UP(void)
{
    if(duty < period)
        duty += unit;
    else
        duty = period;

    softPwmWrite(pinEnable, duty);
    printf("dyty = %d\n", duty);
}