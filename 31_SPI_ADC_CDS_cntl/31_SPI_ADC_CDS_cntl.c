#include <stdio.h>
#include "../EDGE_SPI_API.h"

int main(void)
{
    int adcValue_CDS = 0;
    wiringPiSetupGpio();

    SPI_MCP3208_config(SPI_MCP3208);    // MCP3208 설정

    while(1)
    {
        adcValue_CDS = SPI_MCP3208_Read_modfi(ADC_CH_CDS);      // ADC값을 읽는 함수(channel)
        printf("CDS = %u\n", adcValue_CDS);
        delay(1000);
    }

    return 0;
}
