#define CW      1
#define CCW     2
#define STOP    3
#define BREAK   4

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int pinSwitch0 = 5;
const int pinSwitch1 = 6;

const int pinEnable = 12;
const int pinPositive = 4;
const int pinNegative = 25;

void DC_MOTOR_MODE(int mode);
void DC_MOTOR_MODE_if(int mode);

int main(void)
{
    int pre_sw_state0 = 0, now_sw_state0 = 0;
    int pre_sw_state1 = 0, now_sw_state1 = 0;

    wiringPiSetupGpio();

    pinMode(pinSwitch0, INPUT);
    pinMode(pinSwitch1, INPUT);

    pinMode(pinEnable, OUTPUT);
    pinMode(pinPositive, OUTPUT);
    pinMode(pinNegative, OUTPUT);

    while(1)
    {
        // 현재값
        now_sw_state0 = digitalRead(pinSwitch0);
        now_sw_state1 = digitalRead(pinSwitch1);

        // 기술
        if(pre_sw_state0 == 0 && now_sw_state0 == 1)  // 0에서 1이 되는 조건(상승엣지)
        {
            printf("CW\n");
            digitalWrite(pinPositive, HIGH);
            digitalWrite(pinNegative, LOW);
            digitalWrite(pinEnable, HIGH);
        }

        if(pre_sw_state1 == 0 && now_sw_state1 == 1)  // 0에서 1이 되는 조건(상승엣지)
        {
            printf("STOP\n");
            digitalWrite(pinPositive, LOW);
            digitalWrite(pinNegative, LOW);
            digitalWrite(pinEnable, LOW);
        }

        // 이전값에 현재값 대입
        pre_sw_state0 = now_sw_state0;
        pre_sw_state1 = now_sw_state1;
    }

    return 0;
}

void DC_MOTOR_MODE(int mode)
{
    switch(mode)
    {
        case 1:
            printf("CW\n");
            digitalWrite(pinPositive, HIGH);
            digitalWrite(pinNegative, LOW);
            digitalWrite(pinEnable, HIGH);
            break;
        case 2:
            printf("CCW\n");
            digitalWrite(pinPositive, LOW);
            digitalWrite(pinNegative, HIGH);
            digitalWrite(pinEnable, HIGH);
            break;
        case 3:
            printf("STOP\n");
            digitalWrite(pinPositive, LOW);
            digitalWrite(pinNegative, LOW);
            digitalWrite(pinEnable, LOW);
            break;
        case 4:
            printf("BREAK\n");
            digitalWrite(pinPositive, HIGH);
            digitalWrite(pinNegative, HIGH);
            digitalWrite(pinEnable, LOW);
            break;
    }
}

void DC_MOTOR_MODE_if(int mode)
{
    if(mode == 1)
    {       
        printf("CW\n");
        digitalWrite(pinPositive, HIGH);
        digitalWrite(pinNegative, LOW);
        digitalWrite(pinEnable, HIGH);
    }
    else if(mode == 2)
    {
        printf("CCW\n");
        digitalWrite(pinPositive, LOW);
        digitalWrite(pinNegative, HIGH);
        digitalWrite(pinEnable, HIGH);
    }
    else if(mode == 3)
    {
        printf("STOP\n");
        digitalWrite(pinPositive, LOW);
        digitalWrite(pinNegative, LOW);
        digitalWrite(pinEnable, LOW);
    }
    else if(mode == 4)
    {
        printf("BREAK\n");
        digitalWrite(pinPositive, HIGH);
        digitalWrite(pinNegative, HIGH);
        digitalWrite(pinEnable, LOW);
    }
}