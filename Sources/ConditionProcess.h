//-------------------------------------------------------------------------*
//�ļ���: ConditionProcess.h 					                             	                 *
//˵  ��: ����������											                           *
//��ʼʱ�䣺  2017��11��16��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#ifndef _MSCAN_H_
#define _MSCAN_H_

//1��ͷ�ļ�   
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
//#include "MAP.h"

//2  �궨��

//3����������
void StartCondition_Sub(void);
void IdleCondition(void);

#endif