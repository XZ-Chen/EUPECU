//-------------------------------------------------------------------------*
//文件名: StepperModule.h      					                             	     *
//说  明: 步进电机驱动头文件											                         *
//初始时间：  2012年07月09日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _STEPPERMODULE_H_
#define _STEPPERMODULE_H_

//1、头文件   
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "GeneralFun.h"
    
#define STEPPER_WAIT     0
#define STEPPER_RUN      1
#define STEPPER_REACH    2
#define STEPPER_POSERR   5

#define STEPPER_EN_L9935      PORTK_PK1
#define STEPPER_EN_L9935_DDR  DDRK_DDRK1

#define STEPPER_PHASE_NUM 4



   
//2  宏定义
//3  函数声明
    
//-------------------------------------------------------------------------*
//函数名: StepperModuleInit                                                *
//功  能: 初始化步进电机模块                                               * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------* 
void StepperModuleInit(void); 
uint8 StepperRun(uint16 nDesPos,uint16 nDesPosAD,uint16 nCurPosAD); 
#endif