#ifndef _CAMSHIFTMODULE_H_
#define _CAMSHIFTMODULE_H_
//1��ͷ�ļ�   
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ECT.h"

//2  �궨��
#define CAMSHIFT_GEAR_NUM     3

#define CAMSHIFT_RPM_MAX         1500
#define CAMSHIFT_RPM_MIN         100

typedef struct{
	UINT16 array[200];
	UINT32 accum;
	UINT16 average;
	UINT8 index;
	UINT8 gearnum;
	UINT16 rpm;
	uint8 stopcnt;
} CAMSHIFT_GROUP_ACCUM;

#endif