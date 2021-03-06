//-------------------------------------------------------------------------*
//文件名: LedKey.c                                                  	   *
//说  明: 按键LED灯驱动文件                                         		     *
//初始时间：  2017年11月14日              			                           *
//修订记录：     		              			                                   *
//备注：      用于测试输入信号               			                       *
//-------------------------------------------------------------------------*
#include "LedKey.h"
#include "PinMap.h"



void LedTurn(uint8 pin,uint8 val) 
{
   DOOutput(pin,val);
}

void InitLed(void) 
{
    LedTurn(LED1,ON);
    LedTurn(LED2,ON);
    LedTurn(LED3,ON);
    LedTurn(LED4,ON);
}