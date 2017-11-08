//-------------------------------------------------------------------------*
//文件名: InjectorModule.h      					                             	   *
//说  明: 喷射阀驱动头文件											                           *
//初始时间：  2012年07月09日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _INJECTORMODULE_H_
#define _INJECTORMODULE_H_

//1、头文件   
#include "PIT.h"
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "PinMap.h"
#include "DIOModule.h"
//-------------------------------------------------------------------------*
//函数名: InjectorModuleInit                                               *
//功  能: 初始化喷射阀模块                                                 * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*





void InjectorModuleInit(void);
void InjectorWide(uint16 nCycle,uint16 nWide); 
#define InjectorOff() InjectorWide(0,0) 

#endif