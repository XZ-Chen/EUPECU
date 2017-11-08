//-------------------------------------------------------------------------*
//文件名: TIM.h      					                             	               *
//说  明: TIM定时器驱动头文件											                         *
//初始时间：  2012年07月09日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _CRANKMODULE_H_
#define _CRANKMODULE_H_

//1、头文件   
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ECT.h"

//2  宏定义
#define CRANK_GEAR_NUM        70
#define CRANK_CYLINDER_NUM    6
#define CRANK_RPM_MAX         5000
#define CRANK_RPM_MIN         100

typedef struct{
	UINT16 array[200];
	UINT32 accum;
	UINT16 average;
	UINT8 index;
	UINT8 gearnum;
	UINT16 rpm;
	uint8 stopcnt;
} GROUP_ACCUM;
    


//3  函数声明 
//-------------------------------------------------------------------------*
//函数名: CrankModuleInit                                                  *
//功  能: 初始化定时器模块                                                 * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*

void CrankModuleInit(void);
uint16 CrankSpeedRead(void);

#endif