//-------------------------------------------------------------------------*
//�ļ���: MCUInit.h                                                    	   *
//˵  ��: оƬ��ʼ��ͷ�ļ�                                         		     *
//���ߣ�      ������						                                           *
//��ʼʱ�䣺  2012��07��01��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _SYSTASK_H_
#define _SYSTASK_H_


//1 ͷ�ļ�
#include "typedefine.h"        //���ͱ�������



typedef union _sys_para{
   uint16 data[256];
   struct{
       struct{
          uint16 un16SysMode;       //0 ϵͳ��ģʽ
          uint16 un16DuralMode;     //1 ˫ȼ��ģʽ
          uint16 un16InjWide;       //2 ����ʱ�� ����������
          uint16 un16IgSignal;      //3 ��𿪹�   
          uint16 un16bSingleMode;      //4 ��ȼ��ģʽ����
          uint16 bSensorScan;       //5 ������ɨ��
          uint16 bIOScan;           //6 IO��ɨ��  
          uint16 bModeJudge;        //7 ˫ȼ��ģʽ�б�
          uint16 bOutput;           //8 ���
          uint16 un16Pedal;         //9 ����λ��
                       
       }mem_var;                      
       struct{
         uint16 un16GearNum;          //10 ���ֳ���
         uint16 un16LNGSpeed;         //11 LNG����ת��
         uint16 un16EstTempMax;       //12 �������ѹ��
         uint16 un16StpP1;            //13 ����г̾�������P1
         uint16 un16HighSpeed;        //14 ������ֵ
         uint16 un16HSK1;             //15 ��������K1 
         uint16 un16LSK2;             //16 ��������K2
         uint16 un16StpP2;            //17 ����г̾�������P2
         uint16 un16StpStart;         //18 ����������
         uint16 un16StpEnd;           //19 ���������ֹ
       }const_var;                
       uint16 un16Sensor[10];        //20������ת�� 21���ſ��� Ԥ��10�������
       uint16 un16DI[8];             //Ԥ��8������
       uint16 un16DO[8];             //Ԥ��8�����
       uint16 un16PedalAd[11];      //46
       struct{
	      	uint16 un16Inj_HV_Time;//6
	      	uint16 un16Inj_LV_Time;
	      	uint16 un16Inj_Gap_Time;
	      	uint16 un16InjCurAD;
	      	uint16 bOilAngle;
	      	uint16 Reversed2;
	     }CylinInj_var;
	     struct{    //8
	        uint16 StartSp;  //ֹͣ�����������ת��
	        uint16 LowStp;   //�������������ת��
	        uint16 HiStp;    //�����������ת��
	        uint16 OilStp;   //���������п�ʼ����ת��
	        uint8  HiStCount;     //ͳ�ƴ���������HiStp
	        uint8  PaTiSt;    //�������ת��������
	        uint16 Reversed1;
	      	uint16 Reversed2;
	     }StartCondition_var;
	     struct{    //8
	        uint16 StartSp;  //ֹͣ�����������ת��
	        uint16 IdLowSp;   //���ٹ��������ת��
	        uint16 IdleFlag;    //�����������ת��
	        uint16 PID_Array[4];   //���������п�ʼ����ת��
	        uint8  HiStCount;     //ͳ�ƴ���������HiStp
	        uint8  PaTiSt;    //�������ת��������
	        uint16 Reversed1;
	      	uint16 Reversed2;
	     }IdleCondition_var;
	        uint16 un16InjEnable; //����ʹ��
	        uint16 un16InjOilMo;  //������
	        uint16 un16InjWidth;  //��������
	        uint16 un16InjRadian; //���ͳ�����
	        uint16 un16InjAdvance;  //������ǰ��
	        uint16 un16InjAdTime;  //������ǰʱ��
	        
	        
       uint16 un16Reserved[179];
   }item;
}SYS_PARA;

#define SYS_POWERON  0
#define SYS_SINGLE   1
#define SYS_DURAL    2
#define SYS_ERR      3  //����
#define SYS_HALT     4  //ֹͣ

#define SINGLE_MODE_STOP        0   
#define SINGLE_MODE_START       1
#define SINGLE_MODE_IDLE        2
#define SINGLE_MODE_NORMAL      3

#define SINGLE_MODE_OVERACC     4
#define SINGLE_MODE_OVERDEC     5
#define SINGLE_MODE_SPEEDLIMIT  6
#define SINGLE_MODE_OVERSPEED   7

#define DURAL_MODE_STOP        0   
#define DURAL_MODE_START       1
#define DURAL_MODE_IDLE        2
#define DURAL_MODE_NORMAL      3

#define DURAL_MODE_OVERACC     4
#define DURAL_MODE_OVERDEC     5
#define DURAL_MODE_SPEEDLIMIT  6
#define DURAL_MODE_OVERSPEED   7

#define PEDAL_AD_MIN    25
#define PEDAL_AD_MAX    470
#define PEDAL_RATIO_MAX  1200
#define PEDAL_RATIO_MIN  900

#define STEPPER_AD_MIN  135
#define STEPPER_AD_MAX  605
#define STEPPER_P1      0
#define STEPPER_P2      100

#define LNG_HSK1        100
#define LNG_LSK2        100
#define LNG_HIGHSPEED   1600 

#define FirstCyl  1
#define SecondCyl  2





//����sub mode�洢����������


void SysVarInit(void);
void SysSingleProcess(void);
void SysDuralProcess();
void SysTaskProcess(void);
void SysDigProcess(void);
void SysOutputProcess(void);

void SingleModeJudge(void);
void SingleAppExcute(void);
void DuralModeJudge(void);
void DuralAppExcute(void);

void EngineStopCtrl(void);
void NormalCtrl(void);
void OverAccCtrl(void);
void OverDecCtrl(void);
void SpeedLimitCtrl(void);

void EngineTestCtrl(void);
void CopyPedalMap(void);
void StartCondition(void);
void IdleCondition(void); 
void StopCondition(void);

#endif