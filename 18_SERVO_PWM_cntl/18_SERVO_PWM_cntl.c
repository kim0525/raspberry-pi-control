#define period      200
#define degree0     5.0
#define degree180   25.0
#define degree      (degree180-degree0)/180.0

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

const int pinServo = 17;

int main(void)
{
    int i; 

    wiringPiSetupGpio();

    softPwmCreate(pinServo, 0, period);   //(핀번호, 초기설정값, 주기값(100us))

    while(1)
    {
        for(i=1; i<181; i++)
        {
            softPwmWrite(pinServo, (int)degree*i);  
            delay(20);
        }
    }

    return 0;
}