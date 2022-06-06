// I2C 주소
#define LED_I2C_ADDR        0x20

#define IN_PORT0            0x00
#define IN_PORT1            0x01
#define OUT_PORT0           0x02
#define OUT_PORT1           0x03
#define POLARITY_IVE_PORT0  0x04
#define POLARITY_IVE_PORT1  0x05
#define CONFIG_PORT0        0x06
#define CONFIG_PORT1        0x07

#define PORT0_0             0x0001
#define PORT0_1             0x0002
#define PORT0_2             0x0004
#define PORT0_3             0x0008
#define PORT0_4             0x0010
#define PORT0_5             0x0020
#define PORT0_6             0x0040
#define PORT0_7             0x0080
#define PORT0_ALL           0x00FF

#define PORT1_0             0x0101
#define PORT1_1             0x0102
#define PORT1_2             0x0104
#define PORT1_3             0x0108
#define PORT1_4             0x0110
#define PORT1_5             0x0120
#define PORT1_6             0x0140
#define PORT1_7             0x0180
#define PORT1_ALL           0x01FF


#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int I2C_LED8_config(int addr);      // PORT1번을 모두 출력으로 설정하는 함수를 작성
void I2C_digitalWrite(int fd, int pin, int value);
void I2C_digitalToggle(int fd, int pin);

int main(void)
{
    int fd_LED8;
    int data;

    fd_LED8 = I2C_LED8_config(LED_I2C_ADDR);

    while (1)
    {
        I2C_digitalToggle(fd_LED8, PORT1_0|PORT1_1);
        delay(500);
    }

    return 0;
}

int I2C_LED8_config(int addr)
{
    int fd;

    fd = wiringPiI2CSetup(addr);
    if (fd < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    wiringPiI2CWriteReg8(fd, CONFIG_PORT1, 0x00);   // 출력으로 설정
    wiringPiI2CWriteReg8(fd, OUT_PORT1, 0x00);      // LED를 모두 OFF

    return fd;
}

void I2C_digitalWrite(int fd, int pin, int value)
{
    int data;

    if( (pin&0x0100)  == FALSE )
    {
        // PORT0 일 때
        if(value == LOW)
        {
            // LOW 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT0);
            wiringPiI2CWriteReg8(fd, OUT_PORT0, data&((char)~pin));
        }
        else
        {
            // HIGH 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT0);
            wiringPiI2CWriteReg8(fd, OUT_PORT0, data|(char)pin);
        }
    }
    else
    {
        // PORT1 일 때
        if(value == LOW)
        {
            // LOW 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT1);
            wiringPiI2CWriteReg8(fd, OUT_PORT1, data&((char)~pin));
        }
        else
        {
            // HIGH 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT1);
            wiringPiI2CWriteReg8(fd, OUT_PORT1, data|(char)pin);
        }
    }
}

void I2C_digitalToggle(int fd, int pin)
{
    int data;

    if( (pin&0x0100)  == FALSE )
    {
        // PORT0 일 때
        data = wiringPiI2CReadReg8(fd, OUT_PORT0);
        wiringPiI2CWriteReg8(fd, OUT_PORT0, data^(char)pin);
    }
    else
    {
        // PORT1 일 때
        data = wiringPiI2CReadReg8(fd, OUT_PORT1);
        wiringPiI2CWriteReg8(fd, OUT_PORT1, data^(char)pin);
    }
}