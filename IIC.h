#ifndef _I2C_H
#define _I2C_H

#include <reg52.h>
sbit SCL = P2 ^ 1;
sbit SDA = P2 ^ 0;

void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_SendByte(unsigned char dat);
unsigned char IIC_ReadByte(void);
void Delay10us(void);
void ResponseS(void);
void ResponseM(void);
void noresponseM(void);
unsigned int ReadResult(void);
#endif
