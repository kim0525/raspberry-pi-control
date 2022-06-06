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

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

const int aLedData[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
int fd;

int main(void)
{
    fd = wiringPiI2CSetup(LED_I2C_ADDR);
    if (fd < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    wiringPiI2CWriteReg16(fd, CONFIG_PORT1, 0x0000);
    delay(1000);

    while (1)
    {
        int i;
        for (i = 0; i < 8; i++)
        {
            wiringPiI2CWriteReg16(fd, OUT_PORT1, aLedData[i]);
            delay(100);
        }
    }

    return 0;
}