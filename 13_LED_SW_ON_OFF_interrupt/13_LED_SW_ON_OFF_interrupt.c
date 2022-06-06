#include <stdio.h>
#include <wiringPi.h>

const int pinSwitch0 = 5;
const int pinSwitch1 = 6;
const int pinPir = 24;
const int led0 = 20;
const int led1 = 21;
int ledState0 = 0;   // 0:OFF, 1:ON
int ledState1 = 0;   // 0:OFF, 1:ON
int cnt = 0;

void LED0_Toggle(void);
void LED1_Toggle(void);
void PIR_Decteced(void);

int main(void)
{
    int num=0;
    wiringPiSetupGpio();

    pinMode(pinSwitch0, INPUT);
    pinMode(pinSwitch1, INPUT);
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);

    wiringPiISR(pinSwitch0, INT_EDGE_RISING, LED0_Toggle);  // ISR(Interrupt Service Routine)
    wiringPiISR(pinSwitch1, INT_EDGE_RISING, LED1_Toggle);
    wiringPiISR(pinPir, INT_EDGE_RISING, PIR_Decteced);

    while(1);

    return 0;
}

void LED0_Toggle(void)
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
}

void LED1_Toggle(void)
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
}

void PIR_Decteced(void)
{
    cnt++;
    printf("Detected..%d\n", cnt);
}