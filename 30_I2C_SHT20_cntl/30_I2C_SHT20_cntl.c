#include <stdio.h>
#include <I2C_GPIO_API.h>

int main(void)
{
    int fd_SHT20;
    float temp = 0.0;
    float humi = 0.0;

    int aData[2];
    int value;
    int i;

    fd_SHT20 = I2C_SHT20_config(SHT20_I2C_ADDR);

    while (1)
    {
        // 온습도 측정 모드 설정
        temp = I2C_SHT20_TEMP(fd_SHT20);
        humi = I2C_SHT20_HUMI(fd_SHT20);

        printf("Temp : %.1f\n", temp);
        printf("Humi : %.1f\n", humi);
        delay(1000);
    }

    return 0;
}