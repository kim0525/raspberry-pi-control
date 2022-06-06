#define delay_val 1

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <I2C_GPIO_API.h>

const int pinSwitch0 = 5;
const int pinSwitch1 = 6;
int fd_FND6;
int watch_state = 0;    // 0:stop, 1:start
int cnt = 0;

// A,   B,   C,   D,   E,   F,   G,  DP
int fndDataBit[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
int fndDigitBit[6] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB};

// 사용자 함수
void *I2C_FND6_Display(void *arg);
void start_stop(void);
void reset(void);

int main(void)
{
    int i;
    pthread_t t_id;

    // wiringPi setup
    wiringPiSetupGpio(); 

    // SW 설정
    pinMode(pinSwitch0, INPUT);
    pinMode(pinSwitch1, INPUT);

    wiringPiISR(pinSwitch0, INT_EDGE_RISING, start_stop);
    wiringPiISR(pinSwitch1, INT_EDGE_RISING, reset);

    // FND 설정
    fd_FND6 = I2C_FND6_config(FND_I2C_ADDR);
    
    if (pthread_create(&t_id, NULL, I2C_FND6_Display, (void *)&cnt) != 0)
    {
        printf("pthread_create() error");
        return -1;
    }

    while (1)
    {
        // 시계의 상태값에 따른 동작 기술
        if(watch_state == 1)
        {
            cnt++;
            delay(10);
        }
    }

    return 0;
}

void *I2C_FND6_Display(void *arg)
{
    int *num = (int *)arg;
    int i, j;
    int num_ary[6];

    while (1)
    {
        num_ary[0] = *num / 100000;
        num_ary[1] = (*num % 100000) / 10000;
        num_ary[2] = (*num % 10000) / 1000;
        num_ary[3] = (*num % 1000) / 100;
        num_ary[4] = (*num % 100) / 10;
        num_ary[5] = *num % 10;

        for (i = 0; i < 6; i++)
        {
            // digit 변경
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT0, fndDigitBit[i]); // FND Digit
            // 데이터 변경
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT1, fndDataBit[num_ary[i]]); // FND Data
            delay(delay_val);

            // 모두 OFF(잔상처리)
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT0, 0xFF); // FND Digit
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT1, 0x00); // FND Data
        }
    }
    return NULL;
}

void start_stop(void)
{
    // 시계의 상태값 변경
    if(watch_state == 0) watch_state = 1;
    else watch_state = 0;
}

void reset(void)
{
    cnt = 0;
    watch_state = 0;
}
