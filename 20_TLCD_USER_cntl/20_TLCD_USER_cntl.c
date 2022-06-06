#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <softPwm.h>

const int pinTlcdEN = 26;
const int pinTlcdRS = 16;
int pinTlcdData[4] = {18,27,22,23};

void TLCD_config(int en, int rs, int *data);
void TLCD_init(void);
void TLCD_write(int rs, int data);
void TLCD_putc(char ch);
void TLCD_puts(char *str);

int main(void)
{
    wiringPiSetupGpio();

    TLCD_config(pinTlcdEN, pinTlcdRS, pinTlcdData);
    TLCD_init();

    TLCD_puts("hello world..!!");    

    while(1);

    return 0;
}

void TLCD_config(int en, int rs, int *data)
{
    // 입출력 설정
    pinMode(en, OUTPUT);
    pinMode(rs, OUTPUT);
    for(int i=0; i<4; i++)  pinMode(data[i], OUTPUT);

    // 신호선을 0으로 초기화
    digitalWrite(en, LOW);
    digitalWrite(rs, LOW);
    for(int i=0; i<4; i++)  digitalWrite(data[i], LOW);
}

void TLCD_init(void)
{
    TLCD_write(0, 0x33);    // (rs, data)
    TLCD_write(0, 0x32);
    TLCD_write(0, 0x28);    // function set
    TLCD_write(0, 0x0E);    // display control
    TLCD_write(0, 0x01);    // display clear
    TLCD_write(0, 0x06);    // entry mode set
    TLCD_write(0, 0x02);    // return home
}

void TLCD_write(int rs, int data)
{
    digitalWrite(pinTlcdRS, rs);
    
    digitalWrite(pinTlcdEN, LOW);

    // 상위비트 데이터를 인가
    digitalWrite(pinTlcdData[0], (data>>4)&0x01);
    digitalWrite(pinTlcdData[1], (data>>5)&0x01);
    digitalWrite(pinTlcdData[2], (data>>6)&0x01);
    digitalWrite(pinTlcdData[3], (data>>7)&0x01);

    digitalWrite(pinTlcdEN, HIGH);
    delayMicroseconds(2);
    digitalWrite(pinTlcdEN, LOW);

    // 하위비트 데이터를 인가
    digitalWrite(pinTlcdData[0], (data>>0)&0x01);
    digitalWrite(pinTlcdData[1], (data>>1)&0x01);
    digitalWrite(pinTlcdData[2], (data>>2)&0x01);
    digitalWrite(pinTlcdData[3], (data>>3)&0x01);

    digitalWrite(pinTlcdEN, HIGH);
    delayMicroseconds(2);
    digitalWrite(pinTlcdEN, LOW);

    delay(2);   // 쓰기 실행 대기 
}

void TLCD_putc(char ch)
{
    TLCD_write(1, ch);
}

void TLCD_puts(char *str)
{
    while(*str)
	{
		TLCD_putc(*str++);
	}
}