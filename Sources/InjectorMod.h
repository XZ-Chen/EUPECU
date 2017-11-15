#ifndef _INJECTORMOD_H_
#define _INJECTORMOD_H_

//1��ͷ�ļ�   
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ECT.h"
#include "PinMap.h"

//2  �궨��

void InjectorTest(uint16 nWide);
//  1.��һ����ֹ���Ӧ�������λ��
//  2.͹�����һ�ݶ�Ӧ�������λ��
typedef struct{
	UINT8  DtcCrankI; //��һ����ֹ���Ӧ�������λ��
	UINT8  CrankToCam; //
	UINT16 TDCAngle;
	UINT8  FireSeq[2];
	UINT8  iMax;
	uint8  iR;
	UINT16 TDC[2]; //��ֹ��ݺ�
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
