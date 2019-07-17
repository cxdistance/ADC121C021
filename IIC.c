#include <reg52.h>
#include "I2C.h"

void Delay10us(void)
{
    unsigned char a, b;
    for (b = 1; b > 0; b--)
        for (a = 2; a > 0; a--)
            ;
}
void IIC_Start()
{
    SDA = 1;
    Delay10us();
    SCL = 1;
    Delay10us();
    SDA = 0;
    Delay10us();
    SCL = 0;
    Delay10us();
}
void IIC_Stop()
{
    SDA = 0;
    Delay10us();
    SCL = 1;
    Delay10us();
    SDA = 1;
    Delay10us();
}
unsigned char IIC_SendByte(unsigned char dat)
{
    unsigned char i = 0;
    unsigned char a = 0;
    unsigned char temp = dat;
    for (i = 0; i < 8; i++)
    {
        temp <<= 1;
        SDA = CY;
        Delay10us();
        SCL = 1;
        Delay10us();
        SCL = 0;
        Delay10us();
    }
    return 1;
}
unsigned char IIC_ReadByte()
{
    unsigned char i;
    unsigned char dat;
    SDA = 1;
    for (i = 0; i < 8; i++)
    {
        SCL = 1;
        Delay10us();
        dat <<= 1;
        dat |= SDA;
        Delay10us();
        SCL = 0;
        Delay10us();
    }
    return dat;
}
void ResponseS(void)
{
    SDA = 1;
    Delay10us();
    SCL = 1;
    Delay10us();
    SCL = 0;
    Delay10us();
    SDA = 1;
    Delay10us();
}
void ResponseM(void)
{
    SDA = 0;
    Delay10us();
    SCL = 1;
    Delay10us();
    SCL = 0;
    Delay10us();
    SDA = 1;
    Delay10us();
}
void noresponseM(void)
{
    SDA = 1;
    Delay10us();
    SCL = 1;
    Delay10us();
    SCL = 0;
    Delay10us();
    SDA = 0;
    Delay10us();
}
unsigned int ReadResult(void)
{
    unsigned int temp1, temp2;
    IIC_Start();
    IIC_SendByte(0xa8);
    ResponseS();
    IIC_SendByte(0x00);
    ResponseS();
    IIC_Start();
    IIC_SendByte(0xa9);
    ResponseS();
    temp1 = IIC_ReadByte();
    ResponseM();
    temp2 = IIC_ReadByte();
    noresponseM();
    IIC_Stop();
    temp1 <<= 8;
    temp1 |= temp2;
    return temp1;
}