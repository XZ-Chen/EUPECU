//-------------------------------------------------------------------------*
//�ļ���: LedKey.c                                                  	   *
//˵  ��: ����LED�������ļ�                                         		     *
//��ʼʱ�䣺  2017��11��14��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ���ڲ��������ź�               			                       *
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