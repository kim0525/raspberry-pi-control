#include <stdio.h>
#include <wiringPi.h>

const int pinPir = 24;
//          // A,   B,   C,   D,   E,   F,   G,  DP
// int fndPin[8] = {9, 11, 0, 5, 6, 13, 19, 26};	
         // A,   B,   C,   D,   E,   F,   G,  DP
int fndPin[8] = {26, 19, 13, 6, 5, 0, 11, 9};	

int fndDataBit[10] = {0xFC,0x60,0xDA,0xF2,0x66, 
                      0xB6,0xBE,0xE0,0xFE,0xF6};


int main(void)
{
    int i;
    int cnt=0;

    wiringPiSetupGpio();

    pinMode(pinPir, INPUT);
    // Pin 모드 설정 
	for(i = 0; i<8; i++)
	{
		pinMode(fndPin[i], OUTPUT);	// (핀번호, 모드), 입출력 모드 설정(필수)
	}

    while(1)
    {
        if(digitalRead(pinPir) == HIGH)
        {
            // 스위치가 눌려졌을 때
            cnt++;
            printf("Detected..%d!!\n", cnt);
            delay(500);
        }

        for(i=0; i<8; i++)
		{
			digitalWrite(fndPin[i], fndDataBit[cnt%10]&(0x01<<i));
		}
    }

    return 0;
}
