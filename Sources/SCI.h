//-------------------------------------------------------------------------*
//文件名: SCI.h 					                             	                   *
//说  明: SCI串口驱动头文件											                       *
//初始时间：  2017年03月3日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                          	                 *
//-------------------------------------------------------------------------*
#ifndef _SCI_H_      
#define _SCI_H_
#include "Includes.h"

void INIT_SCI(void);
void SCI_send(unsigned char data);
void SCI_SendDec16u(uint16 a);
void send_string(unsigned char *putchar);
unsigned char SCI_receive(void);

typedef struct scimsg{

    unsigned char MsgHead;
    unsigned char MsgTail;
    unsigned char data[3];
    unsigned char len;
    
}T_SciMsg;

#endif