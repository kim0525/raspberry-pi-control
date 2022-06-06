#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_EEPROM      0
#define SPI_MCP3208     1
#define SPI_SPEED       1000000

#define ADC_CH_CDS      0
#define ADC_CH_VR       1
#define ADC_CH_SOUND    2

// 사용자 함수 선언
int SPI_MCP3208_config(int channel); 

int SPI_MCP3208_Read(char adcChannel);
int SPI_MCP3208_Read_modfi(char adcChannel);

// 사용자 함수 정의
int SPI_MCP3208_config(int channel)
{
    if(wiringPiSPISetup(channel, SPI_SPEED) < 0)
    {
        return -1;
    }

    return 0;
}


int SPI_MCP3208_Read(char adcChannel)
{
    unsigned char buff[3];   // 3 Bytes

    int adcValue = 0;
    buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
    buff[1] = ((adcChannel & 0x07) << 6);
    buff[2] = 0x00;

    wiringPiSPIDataRW(SPI_MCP3208, buff, 3);

    // printf("buff[0] = 0x%x\n", (char)buff[0]);
    // printf("buff[1] = 0x%x\n", (char)buff[1]);
    // printf("buff[2] = 0x%x\n", (char)buff[2]);

    buff[1] = 0x0F & buff[1];
    adcValue = (buff[1] << 8) | buff[2];

    return adcValue;
}

int SPI_MCP3208_Read_modfi(char adcChannel)
{
    unsigned char buff[3];   // 3 Bytes

    int adcValue = 0;
    buff[0] = 0x18 | (adcChannel & 0x07);
    buff[1] = 0x00;
    buff[2] = 0x00;

    wiringPiSPIDataRW(SPI_MCP3208, buff, 3);

    adcValue = ((buff[1]&0x3F)<<6) | (buff[2] >> 2);

    return adcValue;
}

