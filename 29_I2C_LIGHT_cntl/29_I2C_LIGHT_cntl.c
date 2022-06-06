#include <stdio.h>
#include <I2C_GPIO_API.h>

int main(void)
{
    int fd_LIGHT;
    int i;
    int aData[2];
    float lightValue = 0.0;
    int value;

    fd_LIGHT = I2C_LIGHT_config(LIGHT_I2C_ADDR);

    while (1)
    {
        // 측정 모드 설정
        lightValue = I2C_LIGHT_BRIGHT(fd_LIGHT);

        printf("LIGHT : %.1f\n", lightValue);
        delay(1000);
    }

    return 0;
}