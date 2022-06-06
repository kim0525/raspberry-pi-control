#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>

int main(void)
{
    int i;

    wiringPiSetupGpio();

    int lcd = lcdInit(2,16,4,16,26,18,27,22,23,0,0,0,0);

    lcdClear(lcd);

    lcdPosition(lcd, 0, 0);
    lcdPuts(lcd, "edgeiLAB");

    for(i=0;i<10;i++)
    {
        lcdPosition(lcd, 0, 1);
        lcdPrintf(lcd, "Hello World..%d", i);
        delay(1000);
    }
    

    while(1);

    return 0;
}