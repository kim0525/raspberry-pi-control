#include <stdio.h>
#include <wiringSerial.h>
#include <wiringPi.h>

const int pinLed0 = 21;

int main(void)
{
    int fd;
    int data;

    wiringPiSetupGpio();

    pinMode(pinLed0, OUTPUT);

    fd = serialOpen("/dev/ttyS0", 115200);      // 8-N-1
    if(fd < 0)
    {
        printf("Failed to open serial device..!!\n");
        return -1;
    }

    printf("\nRaspverry Pi UART Test\n");

    while(1){
        data = serialGetchar(fd);
        printf("\nRecv Data: %c\n", (char)data);
        serialPutchar(fd, data);

        if(data == '0')
        {
            digitalWrite(pinLed0, LOW);
        }
        else if(data == '1')
        {
            digitalWrite(pinLed0, HIGH);
        }
    }

    return 0;
}