#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define SERVO_I2C_ADDR      0x20

#define OUT_PORT0           0x02
#define CONFIG_PORT0        0x06

const int period = 20000;
const int servoUD = 0x01;
const int servoLR = 0x02;

int fd_SERVO;

int main(void)
{
    fd_SERVO = wiringPiI2CSetup(SERVO_I2C_ADDR);
    if (fd_SERVO < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    wiringPiI2CWriteReg16(fd_SERVO, CONFIG_PORT0, 0x00);

    int i;

    while (1)
    {
        printf("-90도\n");
        for(i=0; i<50; i++)     // -90
        {
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, servoUD);
            delayMicroseconds(50);         // 0.5ms
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, 0x00);
            delayMicroseconds(period-50);   // 19.5ms
        }
        
        printf("0도\n");
        for(i=0; i<50; i++)     // -90
        {
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, servoUD);
            delayMicroseconds(600);         // 0.5ms
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, 0x00);
            delayMicroseconds(period-600);   // 19.5ms
        }

        printf("+90도\n");
        for(i=0; i<50; i++)     // -90
        {
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, servoUD);
            delayMicroseconds(1500);         // 1.5ms
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, 0x00);
            delayMicroseconds(period-1500);   // 19.5ms
        }
    }
}