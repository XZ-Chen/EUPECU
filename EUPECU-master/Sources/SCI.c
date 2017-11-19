#include "SCI.h"
#include "derivative.h"
#define BUS_CLOCK	  32000000	   //总线频率

#define BAUD 9600

/*************************************************************/
/*                        初始化SCI                          */
/*************************************************************/
void INIT_SCI(void) 
{
  SCI2BD = BUS_CLOCK/16/BAUD;   //设置SCI0波特率为9600
  SCI2CR1 = 0x00;        //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI2CR2 = 0x2c;        //允许接收和发送数据，允许接收中断功能 
}                                                            
/*************************************************************/
/*                       串口发送函数                        */
/*************************************************************/
void SCI_send(unsigned char data) 
{
  while(!SCI2SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI2DRL = data;
}
/*************************************************************/
/*             以十进制的形式发送一个16位无符号数            */
/*************************************************************/
void SCI_SendDec16u(uint16 a)
{
    unsigned char b;
    b = (unsigned char)(a/10000);//取万位
    b = b + '0';
    SCI_send(b);
    a = a%10000;
    b = (unsigned char)(a/1000);//取千位
    b = b + '0';
    SCI_send(b);
    a = a%1000;
    b = (unsigned char)(a/100);//取百位
    b = b + '0';
    SCI_send(b);
    a = a%100;
    b = (unsigned char)(a/10);//取十位
    b = b + '0';
    SCI_send(b);
    b = (unsigned char)(a%10);//取个位
    b = b + '0';
    SCI_send(b);
}
/*************************************************************/
/*                  串口发送字符串函数                       */
/*************************************************************/
void send_string(unsigned char *putchar) 
{
  while(*putchar!=0x00)       //判断字符串是否发送完毕
  {
   SCI_send(*putchar++);  
  }
}
/*************************************************************/
/*                       串口接收函数                        */
/*************************************************************/
unsigned char SCI_receive(void) 
{
  while(!SCI2SR1_RDRF);          //等待发送数据寄存器满
  return(SCI2DRL);
}







