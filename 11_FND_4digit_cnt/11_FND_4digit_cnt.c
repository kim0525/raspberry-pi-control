#define delay_val 100

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int fndDigit[4] = {17, 27, 22, 10};
int fndPin[8] = {9, 11, 0, 5, 6, 13, 19, 26};
// A,   B,   C,   D,   E,   F,   G,  DP
int fndData[10][8] = {{HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW},  // 0
                      {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW},      // 1
                      {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW},   // 2
                      {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW},   // 3
                      {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW},    // 4
                      {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW},   // 5
                      {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},  // 6
                      {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW},     // 7
                      {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, // 8
                      {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW}}; // 9
int fndDataBit[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
int fndDigitBit[4] = {0x07, 0x0B, 0x0D, 0x0E};

// 사용자 함수
void *FND4_Display(void *arg);

int main(void)
{
    int cnt = 0, i;
    pthread_t t_id;

    // wiringPi setup
    wiringPiSetupGpio(); // BCM 번호, 21

    // Pin 모드 설정
    for (i = 0; i < 4; i++) // digit
    {
        pinMode(fndDigit[i], OUTPUT); // (핀번호, 모드), 입출력 모드 설정(필수)
    }
    for (i = 0; i < 8; i++) // data
    {
        pinMode(fndPin[i], OUTPUT); // (핀번호, 모드), 입출력 모드 설정(필수)
    }

    if (pthread_create(&t_id, NULL, FND4_Display, (void *)&cnt) != 0)
    {
        printf("pthread_create() error");
        return -1;
    }

    while (1)
    {
        cnt++;
        delay(1000);
    }

    return 0;
}

void *FND4_Display(void *arg)
{
    int *num = (int *)arg;
    int i, j;
    int num_ary[4];

    while (1)
    {
        num_ary[0] = *num / 1000;
        num_ary[1] = (*num % 1000) / 100;
        num_ary[2] = (*num % 100) / 10;
        num_ary[3] = *num % 10;

        for (j = 0; j < 4; j++)
        {
            // digit 변경
            for (i = 0; i < 4; i++)
            {
                digitalWrite(fndDigit[i], fndDigitBit[j] & (0x08 >> i));
            }

            // 데이터 변경
            for (i = 0; i < 8; i++)
            {
                digitalWrite(fndPin[i], fndDataBit[num_ary[j]] & (0x80 >> i));
            }
            delay(delay_val);
        }
    }
    return NULL;
}
