#define degree_0    50
#include <stdio.h>          // < >는 /usr/include 폴더에서 추가   
#include <I2C_GPIO_API.h>   // " "는 현재 경로에서 추가


int main(void)
{
    int fd_SERVO;
    int data;
    int i;

    fd_SERVO = I2C_SERVO_config(SERVO_I2C_ADDR);

    while (1)
    {
        printf("1도\n");
        for(i=0; i<50; i++)     // -90
        {
            data = wiringPiI2CReadReg8(fd_SERVO, OUT_PORT0);
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, data | 0x02); 
            delayMicroseconds(1000);
            data = wiringPiI2CReadReg8(fd_SERVO, OUT_PORT0);
            wiringPiI2CWriteReg8(fd_SERVO, OUT_PORT0, data & (~0x02));
            delayMicroseconds(period-1000);
        }
        
        // printf("90도\n");
        // for(i=0; i<50; i++)     // -90
        // {
        //     I2C_SERVO_DN_DEGREE(fd_SERVO, 90);
        // }

        // printf("180도\n");
        // for(i=0; i<50; i++)     // -90
        // {
        //     I2C_SERVO_DN_DEGREE(fd_SERVO, 180);
        // }
    }

    return 0;
}