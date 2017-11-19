#ifndef _LEDKEY_H_
#define _LEDKEY_H_

//1、头文件   
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ECT.h"


//void LedTurnOn(void);
void LedTurn(uint8 pin,uint8 val);






#endif