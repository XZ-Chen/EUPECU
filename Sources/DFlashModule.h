//-------------------------------------------------------------------------*
//文件名:  					                             	                   *
//说  明: 	  								                       *
//初始时间：  2012年06月30日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#ifndef _DFLASHMODULE_H_           //防止重复定义
#define _DFLASHMODULE_H_ 

//1、头文件    
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "SysTask.h"
void MapToBuffer(uint16 *ptr);
void WriteToFlash(void);
//void PedalReadFlash(uint16 *pSensor);
//-----------------------------------------------------------------------*
//函数名: SensorModuleInit                                                  	   *
//功  能: 初始化ATD模块                                                  * 
//参  数: 无															                               *
//返  回: 无                                                             *
//说  明: 无                                                             *
//-----------------------------------------------------------------------*
typedef struct{
  uint8 WritedFlag;
  uint8 CopyFlag;
}FlashPara;
void DFlash_ParaInit(void);
void JudgeFlashStatus(void);
void DFlash_ParaInit(void);
void ReadFromFlash(void);  
void MapPedalAdBgn(void);   
uint8 checkFlashStatus(void); 
void CheckSave(void);  
#endif



