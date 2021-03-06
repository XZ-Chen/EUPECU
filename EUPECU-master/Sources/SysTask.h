//-------------------------------------------------------------------------*
//文件名: MCUInit.h                                                    	   *
//说  明: 芯片初始化头文件                                         		     *
//作者：      刘晓程						                                           *
//初始时间：  2012年07月01日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _SYSTASK_H_
#define _SYSTASK_H_


//1 头文件
#include "typedefine.h"        //类型别名定义



typedef union _sys_para{
   uint16 data[256];
   struct{
       struct{
          uint16 un16SysMode;       //0 系统主模式
          uint16 un16DuralMode;     //1 双燃料模式
          uint16 un16InjWide;       //2 喷射时间 喷射脉冲宽度
          uint16 un16IgSignal;      //3 点火开关   
          uint16 un16bSingleMode;      //4 单燃料模式工况
          uint16 bSensorScan;       //5 传感器扫描
          uint16 bIOScan;           //6 IO口扫描  
          uint16 bModeJudge;        //7 双燃料模式判别
          uint16 bOutput;           //8 输出
          uint16 un16Pedal;         //9 油门位置
                       
       }mem_var;                      
       struct{
         uint16 un16GearNum;          //10 齿轮齿数
         uint16 un16LNGSpeed;         //11 LNG启动转速
         uint16 un16EstTempMax;       //12 排气最大压力
         uint16 un16StpP1;            //13 电机行程绝对修正P1
         uint16 un16HighSpeed;        //14 高速阈值
         uint16 un16HSK1;             //15 高速修正K1 
         uint16 un16LSK2;             //16 低速修正K2
         uint16 un16StpP2;            //17 电机行程绝对修正P2
         uint16 un16StpStart;         //18 步进电机起点
         uint16 un16StpEnd;           //19 步进电机终止
       }const_var;                
       uint16 un16Sensor[10];        //20发动机转速 21油门开度 预留10个传感�
       uint16 un16DI[8];             //预留8个输入
       uint16 un16DO[8];             //预留8个输出
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
	        uint16 StartSp;  //停止工况运行最高转速
	        uint16 LowStp;   //启动工况的最低转速
	        uint16 HiStp;    //启动工况最高转速
	        uint16 OilStp;   //启动工况中开始供油转速
	        uint8  HiStCount;     //统计次数：超过HiStp
	        uint8  PaTiSt;    //最高启动转数检测次数
	        uint16 Reversed1;
	      	uint16 Reversed2;
	     }StartCondition_var;
	        uint16 un16InjEnable; 
	        uint16 un16InjOilMo;
	        uint16 un16InjWidth;
	        uint16 un16InjRadian;
	        uint16 un16InjAdvance;
	        uint16 un16InjAdTime;
	        
       uint16 un16Reserved[179];
   }item;
}SYS_PARA;

#define SYS_POWERON  0
#define SYS_SINGLE   1
#define SYS_DURAL    2
#define SYS_ERR      3  //出错
#define SYS_HALT     4  //停止

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





//这是sub mode存储出致命代码


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

#endif