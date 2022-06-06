#include <stdio.h>
#include <I2C_GPIO_API.h>

// 1상 여자 방식 회전 데이터(A,B,/A,/B) 
int stepData1[4] = {0x80,0x40,0x20,0x10};
int stepData2[4] = {0xC0,0x60,0x30,0x90};

int main(void)
{
    int fd_STEP;
    int data;
    int i, j=0;

    fd_STEP = I2C_STEP_config(0x20);

    while (j < 12)
    {
        for(i=0; i<4; i++)
        {
            data = wiringPiI2CReadReg8(fd_STEP, OUT_PORT0);
            data &= 0x0F;           // 수정할 자리를 0으로 초기화
            data |= stepData2[i];   // 출력할 데이터를 OR 연산으로 대입
            wiringPiI2CWriteReg8(fd_STEP, OUT_PORT0, data);
            delay(5);
        }
        j++;     
    }

    return 0;
}