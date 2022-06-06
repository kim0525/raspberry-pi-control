#include <stdio.h>
#include <I2C_GPIO_API.h>

int fndDataBit[10] = {0xFC,0x60,0xDA,0xF2,0x66, 0xB6,0xBE,0xE0,0xFE,0xF6};
int fndDigitBit[6] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB};

int main(void)
{
    int fd_FND6;
    int data;
    int i;

    fd_FND6 = I2C_FND6_config(FND_I2C_ADDR);

    while (1)
    {
        for(i=0; i<6; i++)
        {
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT0, fndDigitBit[i]); // FND Digit
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT1, fndDataBit[i+1]); // FND Data
                                                        // OUT_PORT1        OUT_PORT0
            // wiringPiI2CWriteReg16(fd_FND6, OUT_PORT0, (fndDataBit[i+1]<<8)|fndDigitBit[i]);
            delay(1);

            // 모두 OFF(잔상처리)
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT0, 0xFF); // FND Digit
            wiringPiI2CWriteReg8(fd_FND6, OUT_PORT1, 0x00); // FND Data
        }        
    }

    return 0;
}