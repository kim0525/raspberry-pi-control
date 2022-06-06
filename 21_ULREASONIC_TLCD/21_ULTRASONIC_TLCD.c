#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>

const int pinEcho = 1;
const int pinTrigger = 0;

int main(void)
{
    wiringPiSetupGpio();

    pinMode(pinEcho, INPUT);
    pinMode(pinTrigger, OUTPUT);

    int lcd = lcdInit(2,16,4,16,26,18,27,22,23,0,0,0,0);
    lcdPuts(lcd, "Distance");

    digitalWrite(pinTrigger, LOW);
    delay(30);

    while(1)
    {
        // trigger 신호 전송
        digitalWrite(pinTrigger, HIGH);
        delayMicroseconds(20);
        digitalWrite(pinTrigger, LOW);

        // Echo 신호가 High가 될때까지 대기
        while(digitalRead(pinEcho) == LOW);     
        long startTime = micros();
        // Echo 신호가 LOW가 될때까지 대기
        while(digitalRead(pinEcho) == HIGH);     
        long stopTime = micros();   // micro() 부팅 후의 시간값

        // 초음파가 반사되서 돌아온 시간
        long elapsedTime = stopTime - startTime;

        // 시간을 이용한 거리 계산
        int distance = elapsedTime / 58;

        lcdPosition(lcd, 0, 1);
        lcdPrintf(lcd, "Distance : %d cm\n", distance);
        delay(1000);
    }

    return 0;
}