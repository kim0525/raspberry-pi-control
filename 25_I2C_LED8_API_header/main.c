#include <stdio.h>          // < >는 /usr/include 폴더에서 추가   
#include <I2C_GPIO_API.h>   // " "는 현재 경로에서 추가

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