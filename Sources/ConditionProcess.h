//-------------------------------------------------------------------------*
//文件名: ConditionProcess.h 					                             	                 *
//说  明: 工况处理函数											                           *
//初始时间：  2017年11月16日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#ifndef _MSCAN_H_
#define _MSCAN_H_

//1、头文件   
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
//#include "MAP.h"

//2  宏定义

//3、函数声明
void StartCondition_Sub(void);
void IdleCondition(void);

#endif