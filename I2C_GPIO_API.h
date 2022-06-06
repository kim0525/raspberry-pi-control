// I2C 주소
#define LED_I2C_ADDR        0x20
#define STEP_I2C_ADDR       0x20
#define FND_I2C_ADDR        0x21
#define LIGHT_I2C_ADDR      0x23
#define SHT20_I2C_ADDR      0x40

// GPIO IC 관련 설정
#define IN_PORT0            0x00
#define IN_PORT1            0x01
#define OUT_PORT0           0x02
#define OUT_PORT1           0x03
#define POLARITY_IVE_PORT0  0x04
#define POLARITY_IVE_PORT1  0x05
#define CONFIG_PORT0        0x06
#define CONFIG_PORT1        0x07

#define PORT0_0             0x0001
#define PORT0_1             0x0002
#define PORT0_2             0x0004
#define PORT0_3             0x0008
#define PORT0_4             0x0010
#define PORT0_5             0x0020
#define PORT0_6             0x0040
#define PORT0_7             0x0080
#define PORT0_ALL           0x00FF

#define PORT1_0             0x0101
#define PORT1_1             0x0102
#define PORT1_2             0x0104
#define PORT1_3             0x0108
#define PORT1_4             0x0110
#define PORT1_5             0x0120
#define PORT1_6             0x0140
#define PORT1_7             0x0180
#define PORT1_ALL           0x01FF

// LIGHT 관련 설정
#define LIGHT_I2C_POWER_DOWN    0x00
#define LIGHT_I2C_POWER_ON      0x01
#define LIGHT_I2C_RESET         0x07
#define LIGHT_I2C_CON_HR_MODE   0x10
#define LIGHT_I2C_CON_LR_MODE   0x13
#define LIGHT_I2C_OT_HR_MODE    0x20
#define LIGHT_I2C_OT_LR_MODE    0x23

// SHT20 관련 설정
#define SHT20_I2C_CMD_MEASURE_TEMP  0xF3
#define SHT20_I2C_CMD_MEASURE_HUMI  0xF5
#define SHT20_I2C_CMD_SOFT_RESET    0xFE

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// 사용자 함수 선언
int I2C_LED8_config(int addr);      // PORT1번을 모두 출력으로 설정하는 함수를 작성
int I2C_FND6_config(int addr);
int I2C_STEP_config(int addr);
int I2C_LIGHT_config(int addr);
int I2C_SHT20_config(int addr);

void I2C_digitalWrite(int fd, int pin, int value);
void I2C_digitalToggle(int fd, int pin);

float I2C_SHT20_TEMP(int fd);
float I2C_SHT20_HUMI(int fd);
float I2C_LIGHT_BRIGHT(int fd);


// 사용자 함수 정의
int I2C_LED8_config(int addr)
{
    int fd;

    fd = wiringPiI2CSetup(addr);
    if (fd < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    wiringPiI2CWriteReg8(fd, CONFIG_PORT1, 0x00);   // 출력으로 설정
    wiringPiI2CWriteReg8(fd, OUT_PORT1, 0x00);      // LED를 모두 OFF

    return fd;
}

int I2C_FND6_config(int addr)
{
    int fd;

    fd = wiringPiI2CSetup(addr);
    if (fd < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    wiringPiI2CWriteReg8(fd, CONFIG_PORT0, 0x00);   // FND DIGIT 출력으로 설정
    wiringPiI2CWriteReg8(fd, CONFIG_PORT1, 0x00);   // FND DATA 출력으로 설정
    wiringPiI2CWriteReg8(fd, OUT_PORT0, 0xFF);      // FND DIGIT를 모두 OFF
    wiringPiI2CWriteReg8(fd, OUT_PORT1, 0x00);      // FND DATA를 모두 OFF

    return fd;
}

int I2C_STEP_config(int addr)
{
    int fd;
    int data;

    fd = wiringPiI2CSetup(addr);
    if (fd < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    data = wiringPiI2CReadReg8(fd, CONFIG_PORT0);
    wiringPiI2CWriteReg8(fd, CONFIG_PORT0, data&0x0F);   // step pin출력으로 설정
    data = wiringPiI2CReadReg8(fd, OUT_PORT0);
    wiringPiI2CWriteReg8(fd, OUT_PORT0, data&0x0F);      // step를 모두 OFF

    return fd;
}

int I2C_LIGHT_config(int addr)
{
    int fd;

    fd = wiringPiI2CSetup(addr);
    if (fd < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    wiringPiI2CWrite(fd, LIGHT_I2C_RESET);
    delay(50);

    return fd;
}

int I2C_SHT20_config(int addr)
{
    int fd;

    fd = wiringPiI2CSetup(addr);
    if (fd < 0)
    {
        printf("Device not Found..!\n");
        return -1;
    }

    wiringPiI2CWrite(fd, SHT20_I2C_CMD_SOFT_RESET);
    delay(50);

    return fd;
}


// ===============================================================
void I2C_digitalWrite(int fd, int pin, int value)
{
    int data;

    if( (pin&0x0100)  == FALSE )
    {
        // PORT0 일 때
        if(value == LOW)
        {
            // LOW 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT0);
            wiringPiI2CWriteReg8(fd, OUT_PORT0, data&((char)~pin));
        }
        else
        {
            // HIGH 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT0);
            wiringPiI2CWriteReg8(fd, OUT_PORT0, data|(char)pin);
        }
    }
    else
    {
        // PORT1 일 때
        if(value == LOW)
        {
            // LOW 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT1);
            wiringPiI2CWriteReg8(fd, OUT_PORT1, data&((char)~pin));
        }
        else
        {
            // HIGH 일때
            data = wiringPiI2CReadReg8(fd, OUT_PORT1);
            wiringPiI2CWriteReg8(fd, OUT_PORT1, data|(char)pin);
        }
    }
}

void I2C_digitalToggle(int fd, int pin)
{
    int data;

    if( (pin&0x0100)  == FALSE )
    {
        // PORT0 일 때
        data = wiringPiI2CReadReg8(fd, OUT_PORT0);
        wiringPiI2CWriteReg8(fd, OUT_PORT0, data^(char)pin);
    }
    else
    {
        // PORT1 일 때
        data = wiringPiI2CReadReg8(fd, OUT_PORT1);
        wiringPiI2CWriteReg8(fd, OUT_PORT1, data^(char)pin);
    }
}

float I2C_SHT20_TEMP(int fd)
{
    float temp = 0.0;
    int aData[2];
    int value;

    wiringPiI2CWrite(fd, SHT20_I2C_CMD_MEASURE_TEMP);
    delay(260);

    aData[0] = wiringPiI2CRead(fd);   // 상위비트
    aData[1] = wiringPiI2CRead(fd);   // 하위비트

    // 측정된 데이터를 계산
    value = (aData[0]<<8) | aData[1];
    temp = -46.85 + 175.72/65536*(int)value;

    return temp;
}

float I2C_SHT20_HUMI(int fd)
{
    float humi = 0.0;
    int aData[2];
    int value;

    wiringPiI2CWrite(fd, SHT20_I2C_CMD_MEASURE_HUMI);
    delay(260);

    aData[0] = wiringPiI2CRead(fd);   // 상위비트
    aData[1] = wiringPiI2CRead(fd);   // 하위비트

    // 측정된 데이터를 계산
    value = (aData[0]<<8) | aData[1];
    humi = -6.0 + 125.0/65536*(int)value;

    return humi;
}

float I2C_LIGHT_BRIGHT(int fd)
{
    float brigt = 0.0;
    int aData[2];
    int value;

    wiringPiI2CWrite(fd, LIGHT_I2C_OT_HR_MODE);
    delay(200);

    aData[0] = wiringPiI2CRead(fd);   // 상위비트
    aData[1] = wiringPiI2CRead(fd);   // 하위비트

    // 측정된 데이터를 계산
    value = (aData[0]<<8) | aData[1];
    brigt = value / 1.2;

    return brigt;
}