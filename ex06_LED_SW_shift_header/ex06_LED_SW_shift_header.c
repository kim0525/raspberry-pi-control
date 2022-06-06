#include <stdio.h>   
#include <I2C_GPIO_API.h> 

const int aLedData[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const int pinSw0 = 5;
const int pinSw1 = 6;

int dir = 0;    // 0:0~7, 1:7~0

// 사용자 함수
void SW0_ISR(void);
void SW1_ISR(void);

int main(void)
{
    int fd_LED8;
    int data;
    int i, j;

    wiringPiSetupGpio();

    pinMode(pinSw0, INPUT);
    pinMode(pinSw1, INPUT);

    wiringPiISR(pinSw0, INT_EDGE_RISING, SW0_ISR);  // ISR(Interrupt Service Routine)
    wiringPiISR(pinSw1, INT_EDGE_RISING, SW1_ISR);

    fd_LED8 = I2C_LED8_config(LED_I2C_ADDR);

    while (1)
    {
        if(dir == 0){
            for(i=0; i<8; i++)
            {
                wiringPiI2CWriteReg8(fd_LED8, OUT_PORT1, aLedData[i]);
                delay(100);
            }
        }
        else{
            for(i=7; i>-1; i--)
            {
                wiringPiI2CWriteReg8(fd_LED8, OUT_PORT1, aLedData[i]);
                delay(100);
            }
        }
    }

    return 0;
}

void SW0_ISR(void){
    int i;
    while(1)
    {
        for(i=0; i<8; i++)
        {
            wiringPiI2CWriteReg8(fd_LED8, OUT_PORT1, aLedData[i]);
            delay(100);
        }
    }
}

void SW1_ISR(void){
    int i;
    while(1)
    {
        for(i=7; i>-1; i--)
        {
            wiringPiI2CWriteReg8(fd_LED8, OUT_PORT1, aLedData[i]);
            delay(100);
        }
    }
}