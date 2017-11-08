//-------------------------------------------------------------------------*
//文件名: GeneralFun.c			                               	               *
//说  明: 通用函数文件,文件包含：					                                 *
//	      延时函数							                                           *
//初始时间：  2012年7月31日              			                             *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128                           			           *
//-------------------------------------------------------------------------*
#include "GeneralFun.h"   //包含通用函数头文件

//-------------------------------------------------------------------------*
// 函数名: Delay_Us()                                                      *
// 功  能: 延时                                                            *
// 参  数: count(小于65535)                                                *
// 返  回: 无                                                              *
// 说  明: 无                                                              *
//-------------------------------------------------------------------------*
void DelayUs(UINT16 count){
	UINT16 i,j;
	for(j=0; j<count; j++)
	   for(i=0; i<40; i++)
	      ;
}

//-------------------------------------------------------------------------*
// 函数名: Delay_Ms()                                                      *
// 功  能: 延时                                                            *
// 参  数: count(小于65535)                                                *
// 返  回: 无                                                              *
// 说  明: 无                                                              *
//-------------------------------------------------------------------------*
void DelayMs(UINT16 count){
	UINT16 i,j;
	for(j=0; j<count; j++)
	   for(i=0; i<4000; i++)
	      ;
}

