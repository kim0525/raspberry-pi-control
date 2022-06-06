#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL     0
#define SPI_SPEED       1000000

// EEPROM 레지스터 설정
#define WRSR    0x01
#define WRITE   0x02
#define READ    0x03
#define WRDI    0x04
#define RDSR    0x05
#define WREN    0x06

int main(void)
{
    char buff[9];
    
    wiringPiSetupGpio();

    if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) < 0)
    {
        return -1;
    }

    // EEPROM 프로그래밍 모드 활성화
    buff[0] = WREN;
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 1);
    delay(1);

    // EEPROM에 데이터 쓰기
    printf("SAVE : RASPI\n");
    buff[0] = WRITE;    buff[1] = 0x00;    buff[2] = 0x11;
    buff[3] = 'R';      buff[4] = 'A';     buff[5] = 'S';
    buff[6] = 'P';      buff[7] = 'I';     buff[8] = '\n';

    wiringPiSPIDataRW(SPI_CHANNEL, buff, 9);
    delay(5000);

    // EEPROM 프로그래밍 모드 비활성화
    buff[0] = WRDI;
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 1);
    delay(1);

    // EEPROM으로부터 데이터 읽기
    buff[0] = READ;    buff[1] = 0x00;    buff[2] = 0x11;

    wiringPiSPIDataRW(SPI_CHANNEL, buff, 9);
    delay(1000);

    printf("READ : ");
    for(int i=3; i<9; i++)
    {
        printf("%c", buff[i]);
    }
    printf("\n");

    return 0;
}