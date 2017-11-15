//-------------------------------------------------------------------------*
//文件名: MSCAN.h 					                             	                 *
//说  明: CAN总线驱动头文件											                           *
//初始时间：  2017年08月29日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#ifndef _MSMQ_H_
#define _MSMQ_H_
//1 头文件 
#include "typedefine.h"           //类型别名定义
#include <hidef.h> 
#include <MC9S12XET256.h>     /* derivative information */
#include "SysTask.h"

//2 宏定义

//3函数

void MSSCIProcess(void);
#endif