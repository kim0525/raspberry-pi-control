#include <stdio.h>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <string.h>

const int pinLed0 = 21;

int main(void)
{
    int fd;
    int data;
    char recv_str[100];
    int index = 0;

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
        if(data == -1)      // 아무것도 입력이 안됐을때 
        {
            continue;
        }
        else if( data == '\r')  // 엔터 입력이 들어왔을 때
        {
            recv_str[index] = '\0';
            printf("\nRecv Data: %s\n", recv_str);
            serialPuts(fd, recv_str);

            // recv_str 값에 따른 동작을 기술
            if(strcmp("LED ON", recv_str) == 0)
            {
                digitalWrite(pinLed0, HIGH);
            }
            else if(strcmp("LED OFF", recv_str) == 0)
            {
                digitalWrite(pinLed0, LOW);
            }

            memset(recv_str, 0, sizeof(recv_str));
            index = 0;
        }
        else    // 문자를 수신하지 못하거나, 입력이 들어왔을 때 
        {
            recv_str[index] = (char)data;
            index++;
        }        
    }

    return 0;
}