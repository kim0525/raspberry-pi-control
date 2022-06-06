#include <stdio.h>
#include <wiringPi.h>

const int pinSwitch0 = 5;
const int pinSwitch1 = 6;
const int led0 = 20;
const int led1 = 21;

int main(void)
{
    int num=0;
    int ledState0 = 0;   // 0:OFF, 1:ON
    int ledState1 = 0;   // 0:OFF, 1:ON

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
            if(ledState0 == 0)        // LED 상태에 따라 실행
            {
                // LED가 꺼져 있을 때
                digitalWrite(led0, HIGH);
                ledState0 = 1;
            }
            else
            {
                // LED가 켜져 있을 때
                digitalWrite(led0, LOW);
                ledState0 = 0;
            }
            delay(500);
        }

        if(digitalRead(pinSwitch1) == HIGH)
        {
            // 스위치가 눌려졌을 때
            printf("Pushed..1\n");
            if(ledState1 == 0)        // LED 상태에 따라 실행
            {
                // LED가 꺼져 있을 때
                digitalWrite(led1, HIGH);
                ledState1 = 1;
            }
            else
            {
                // LED가 켜져 있을 때
                digitalWrite(led1, LOW);
                ledState1 = 0;
            }
            delay(500);
        }
    }

    return 0;
}
