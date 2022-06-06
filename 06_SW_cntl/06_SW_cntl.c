#include <stdio.h>
#include <wiringPi.h>

const int pinSwitch0 = 5;
const int pinSwitch1 = 6;
const int led0 = 20;
const int led1 = 21;

int main(void)
{
    int num=0;

    wiringPiSetupGpio();

    pinMode(pinSwitch0, INPUT);
    pinMode(pinSwitch1, INPUT);
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);

    while(1)
    {
        if(digitalRead(pinSwitch0) == HIGH)
        {
            // 스위치가 눌려졌을 때
            printf("Pushed..0\n");
            digitalWrite(led0, HIGH);
            //delay(500);
        }
        else
            digitalWrite(led0, LOW);

        if(digitalRead(pinSwitch1) == HIGH)
        {
            // 스위치가 눌려졌을 때
            printf("Pushed..1\n");
            digitalWrite(led1, HIGH);
            //delay(500);
        }
        else
            digitalWrite(led1, LOW);
    }

    return 0;
}
