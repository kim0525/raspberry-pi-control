#define period  100
#define unit    period/10

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

const int led0 = 20;
const int led1 = 21;
const int pinSw0 = 5;
const int pinSw1 = 6;
int duty = 0;

void LED_DN(void);
void LED_UP(void);

int main(void)
{
    wiringPiSetupGpio();

    pinMode(pinSw0, INPUT);
    pinMode(pinSw1, INPUT);

    softPwmCreate(led0, duty, period);   //(핀번호, 초기설정값, 주기값(100us))
    softPwmCreate(led1, duty, period);

    wiringPiISR(pinSw0, INT_EDGE_RISING, LED_DN);
    wiringPiISR(pinSw1, INT_EDGE_RISING, LED_UP);

    // delay를 이용한 PWM 제어
    // while(1)
    // {
    //     digitalWrite(led0, HIGH);
    //     digitalWrite(led1, HIGH);
    //     delayMicroseconds(100);
    //     digitalWrite(led0, LOW);
    //     delayMicroseconds(500);
    //     digitalWrite(led1, LOW);
    //     delayMicroseconds(400);        
    // }

    while(1);

    return 0;
}

void LED_DN(void)
{
    if(duty >= 0)
        duty -= unit;
    else
        duty = 0;

    softPwmWrite(led0, duty);
    softPwmWrite(led1, duty);
}

void LED_UP(void)
{
    if(duty <= period)
        duty += unit;
    else
        duty = period;

    softPwmWrite(led0, duty);
    softPwmWrite(led1, duty);
}