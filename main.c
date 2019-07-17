#include <reg52.h>
#include "I2C.h"
#define VA 5
unsigned int value = 0;
unsigned char code num[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned char DisplayData[5];

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

void delay(unsigned int time);
void DigDisplay();
void DataProcess();
void ChangeTemp();
void main()
{
    while (1)
    {
        value = ReadResult();
        DataProcess();
        DigDisplay();
    }
    return;
}
void delay(unsigned int time)
{
    while (time--)
        ;
}
void DigDisplay()
{
    unsigned char i, j = 150;
    while (j--)
        for (i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                LSA = 0;
                LSB = 0;
                LSC = 0;
                break;
            case 1:
                LSA = 1;
                LSB = 0;
                LSC = 0;
                break;
            case 2:
                LSA = 0;
                LSB = 1;
                LSC = 0;
                break;
            case 3:
                LSA = 1;
                LSB = 1;
                LSC = 0;
                break;
            }
            P0 = DisplayData[i + 1];
            delay(100);
            P0 = 0x00;
        }
}
void DataProcess()
{
    float Val_temp, vaa = value;
    unsigned int Val;
    Val_temp = VA * vaa * 100 / 4096;
    Val = (int)Val_temp;
    DisplayData[1] = num[Val % 10];
    DisplayData[2] = num[Val % 100 / 10];
    DisplayData[3] = num[Val % 1000 / 100] | 0x80;
    DisplayData[4] = num[Val / 1000];
}
