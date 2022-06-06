
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int fndPin[8] = {9, 11, 0, 5, 6, 13, 19, 26};
							// A,   B,   C,   D,   E,   F,   G,  DP
int fndData[10][8] = { {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH, LOW, LOW},	// 0
                        { LOW,HIGH,HIGH, LOW, LOW, LOW, LOW, LOW},	// 1
                        {HIGH,HIGH, LOW,HIGH,HIGH, LOW,HIGH, LOW},	// 2
                        {HIGH,HIGH,HIGH,HIGH, LOW, LOW,HIGH, LOW},	// 3
                        { LOW,HIGH,HIGH, LOW, LOW,HIGH,HIGH, LOW},	// 4
                        {HIGH, LOW,HIGH,HIGH, LOW,HIGH,HIGH, LOW},	// 5
                        {HIGH, LOW,HIGH,HIGH,HIGH,HIGH,HIGH, LOW},	// 6
                        {HIGH,HIGH,HIGH, LOW, LOW, LOW, LOW, LOW},	// 7
                        {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH, LOW},	// 8
                        {HIGH,HIGH,HIGH,HIGH, LOW,HIGH,HIGH, LOW} };	// 9
int fndDataBit[10] = {0xFC,0x60,0xDA,0xF2,0x66, 0xB6,0xBE,0xE0,0xFE,0xF6};

int main(void)
{
	int i, j;
		
	// wiringPi setup
	wiringPiSetupGpio();	// BCM 번호, 21
	
	// Pin 모드 설정 
	for(i = 0; i<8; i++)
	{
		pinMode(fndPin[i], OUTPUT);	// (핀번호, 모드), 입출력 모드 설정(필수)
	}	
	
	// 출력 이중 for문
	for(i=0; i<10; i++)
	{
		for(j=0; j<8; j++)
		{
			digitalWrite(fndPin[j], fndDataBit[i]&(0x80>>j));
		}
		delay(1000);
	}

	return 0;
}
