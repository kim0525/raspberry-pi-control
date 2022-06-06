#include <stdio.h>
#include <wiringPi.h>

const int pinSwitch0 = 5;
const int pinSwitch1 = 6;
const int led0 = 20;
const int led1 = 21;

// 사용자 함수
void edge_SW_LED(int pre_sw_state, int now_sw_state, int ledPin, int *ledState);

int main(void)
{
    int num=0;
    int ledState0 = 0;   // 0:OFF, 1:ON
    int ledState1 = 0;   // 0:OFF, 1:ON
    int pre_sw_state0 = 0, now_sw_state0 = 0;
    int pre_sw_state1 = 0, now_sw_state1 = 0;

    wiringPiSetupGpio();

    pinMode(pinSwitch0, INPUT);
    pinMode(pinSwitch1, INPUT);
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);

    while(1)
    {
        // 현재값
        now_sw_state0 = digitalRead(pinSwitch0);
        now_sw_state1 = digitalRead(pinSwitch1);

        // 기술
        edge_SW_LED(pre_sw_state0, now_sw_state0, led0, &ledState0);
        edge_SW_LED(pre_sw_state1, now_sw_state1, led1, &ledState1);

        // 이전값에 현재값 대입
        pre_sw_state0 = now_sw_state0;
        pre_sw_state1 = now_sw_state1;
    }

    return 0;
}

void edge_SW_LED(int pre_sw_state, int now_sw_state, int ledPin, int *ledState)
{
    if(pre_sw_state == 0 && now_sw_state == 1)  // 0에서 1이 되는 조건(상승엣지)
    {
        // 스위치가 눌려졌을 때
        printf("Pushed..!!\n");
        if(*ledState == 0)        // LED 상태에 따라 실행
        {
            // LED가 꺼져 있을 때
            digitalWrite(ledPin, HIGH);
            *ledState = 1;
        }
        else
        {
            // LED가 켜져 있을 때
            digitalWrite(ledPin, LOW);
            *ledState = 0;
        }
    }
}
