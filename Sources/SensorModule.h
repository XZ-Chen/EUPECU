//-------------------------------------------------------------------------*
//文件名: ATD.h 					                             	                   *
//说  明: 模/数转换模块驱动头文件	  								                       *
//初始时间：  2012年06月30日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#ifndef _SENSORMODULE_H_           //防止重复定义
#define _SENSORMODULE_H_ 

//1、头文件    
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ATD.h"
#include "SPI.h"
#include "PinMap.h"



typedef struct _sensor {
    uint8 status;
    UINT8 pointer;
  	UINT16 value[7];
}sensor;

//-----------------------------------------------------------------------*
//函数名: SensorModuleInit                                                  	   *
//功  能: 初始化ATD模块                                                  * 
//参  数: 无															                               *
//返  回: 无                                                             *
//说  明: 无                                                             *
//-----------------------------------------------------------------------*

extern sensor stppos_sensor;
extern sensor pedalpos_sensor;
extern sensor stppos_sensor;
extern sensor esttemp_sensor;
extern sensor crankspeed_sensor;

void SensorModuleInit(void);
void SensorScan(uint16 *pSensor);
void PedalRead(uint16 *pSensor); 
#define ExhasutTempRead() (SPIReadWord(SPI_MAX6675,0xffff))



        
#endif



