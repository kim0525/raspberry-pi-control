
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define LED_NUM 4

int ledControl(int *gpio)
{
	int i, j;
	
	for(i = 0; i<LED_NUM; i++)
	{
		pinMode(gpio[i], OUTPUT);	// (핀번호, 모드), 입출력 모드 설정(필수)
	}
	
	while(1)
	{
		for(j=0; j<LED_NUM; j++)
		{
			digitalWrite(gpio[j], HIGH);	// (핀번호, 출력값)
			delay(300);
			digitalWrite(gpio[j], LOW);
		}
		
		for(j=3; j>-1; j--)
		{
			digitalWrite(gpio[j], HIGH);	// (핀번호, 출력값)
			delay(300);
			digitalWrite(gpio[j], LOW);
		}
		
	}
	return 0;
}

int main(int argc, char **argv)
{
	int gno[LED_NUM] = {0};
	int i;
	
	if(argc < LED_NUM+1){
		printf("Usage : %s GPIO_NO0 GPIO_NO1 \n", argv[0]);
		return -1;
	}
	
	for(i=0; i<LED_NUM; i++)
	{
		gno[i] = atoi(argv[i+1]);
	}
	
	
	//wiringPiSetup();		// wPi 번호, 29
	wiringPiSetupGpio();	// BCM 번호, 21
	//wiringPiSetupPhys(); 	// 보드 번호, 40
	
	ledControl(gno);
	
	return 0;
}
