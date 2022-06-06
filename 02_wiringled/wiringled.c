#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int ledControl(int *gpio)
{
	int i, j;
	
	for(i = 0; i<2; i++)
	{
		pinMode(gpio[i], OUTPUT);	// (핀번호, 모드), 입출력 모드 설정(필수)
	}
	
	for(i = 0; i<3; i++)
	{
		for(j=0; j<2; j ++)
		{
			digitalWrite(gpio[j], HIGH);	// (핀번호, 출력값)
		}
		delay(300);
		
		for(j=0; j<2; j ++)
		{
			digitalWrite(gpio[j], LOW);
		}
		delay(300);
	}
	return 0;
}

int main(int argc, char **argv)
{
	int gno[2] = {0};
	int i;
	
	if(argc < 3){
		printf("Usage : %s GPIO_NO0 GPIO_NO1 \n", argv[0]);
		return -1;
	}
	
	for(i=0; i<2; i++)
	{
		gno[i] = atoi(argv[i+1]);
	}
	
	
	//wiringPiSetup();		// wPi 번호, 29
	wiringPiSetupGpio();	// BCM 번호, 21
	//wiringPiSetupPhys(); 	// 보드 번호, 40
	
	ledControl(gno);
	
	return 0;
}
