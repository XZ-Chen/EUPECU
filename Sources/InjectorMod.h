#ifndef _INJECTORMOD_H_
#define _INJECTORMOD_H_

//1、头文件   
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ECT.h"
#include "PinMap.h"

//2  宏定义

void InjectorTest(uint16 nWide);
//  1.第一缸上止点对应的曲轴齿位置
//  2.凸轮轴第一齿对应的曲轴齿位置
typedef struct{
	UINT8  DtcCrankI; //第一缸上止点对应的曲轴齿位置
	UINT8  CrankToCam; //
	UINT16 TDCAngle;
	UINT8  FireSeq[2];
	UINT8  iMax;
	uint8  iR;
	UINT16 TDC[2]; //上止点齿号
	UINT16 InjAdvance;
	UINT8  OilTeeth;
} EngStructPara;

typedef struct {
  UINT16  Dtq1;
  UINT16  Dtq2;
  UINT16  Dtq3;
  UINT16  Dtq4; 
  UINT16  DtGaptime;
  UINT16  DtqHvTime;
}InjTimePara;

void Oil_Sup(void);
void oil_Supply1(void);
void oil_Supply2(void); 

#endif
