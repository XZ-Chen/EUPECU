//-------------------------------------------------------------------------*
//ÎÄ¼þÃû: MCUInit.h                                                    	   *
//Ëµ  Ã÷: Ð¾Æ¬³õÊ¼»¯Í·ÎÄ¼þ                                         		     *
//×÷Õß£º      ÁõÏþ³Ì						                                           *
//³õÊ¼Ê±¼ä£º  2012Äê07ÔÂ01ÈÕ              			                           *
//ÐÞ¶©¼ÇÂ¼£º     		              			                                   *
//±¸×¢£º      ÊÊÓÃÓÚMC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _SYSTASK_H_
#define _SYSTASK_H_


//1 Í·ÎÄ¼þ
#include "typedefine.h"        //ÀàÐÍ±ðÃû¶¨Òå



typedef union _sys_para{
   uint16 data[256];
   struct{
       struct{
          uint16 un16SysMode;       //0 ÏµÍ³Ö÷Ä£Ê½
          uint16 un16DuralMode;     //1 Ë«È¼ÁÏÄ£Ê½
          uint16 un16InjWide;       //2 ÅçÉäÊ±¼ä ÅçÉäÂö³å¿í¶È
          uint16 un16StepperPos;    //3 µç»úÐÐ³Ì    
          uint16 un16LNGState;      //4 LNG×´Ì¬
          uint16 bSensorScan;       //5 ´«¸ÐÆ÷É¨Ãè
          uint16 bIOScan;           //6 IO¿ÚÉ¨Ãè  
          uint16 bModeJudge;        //7 Ä£Ê½ÅÐ±ð
          uint16 bOutput;           //8 Êä³ö
          uint16 un16Pedal;         //9 ÓÍÃÅÎ»ÖÃ
                       
       }mem_var;                      
       struct{
         uint16 un16GearNum;          //10 ³ÝÂÖ³ÝÊý
         uint16 un16LNGSpeed;         //11 LNGÆô¶¯×ªËÙ
         uint16 un16EstTempMax;       //12 ÅÅÆø×î´óÑ¹Á¦
         uint16 un16StpP1;            //13 µç»úÐÐ³Ì¾ø¶ÔÐÞÕýP1
         uint16 un16HighSpeed;        //14 ¸ßËÙãÐÖµ
         uint16 un16HSK1;             //15 ¸ßËÙÐÞÕýK1 
         uint16 un16LSK2;             //16 µÍËÙÐÞÕýK2
         uint16 un16StpP2;            //17 µç»úÐÐ³Ì¾ø¶ÔÐÞÕýP2
         uint16 un16StpStart;         //18 ²½½øµç»úÆðµã
         uint16 un16StpEnd;           //19 ²½½øµç»úÖÕÖ¹
       }const_var;                
       uint16 un16Sensor[10];        //20·¢¶¯»ú×ªËÙ 21ÓÍÃÅ¿ª¶È Ô¤Áô10¸ö´«¸ÐÆ
       uint16 un16DI[8];             //Ô¤Áô8¸öÊäÈë
       uint16 un16DO[8];             //Ô¤Áô8¸öÊä³ö
       uint16 un16PedalAd[11];      //46
       struct{
	      	uint16 un16Inj_HV_Time;//6
	      	uint16 un16Inj_LV_Time;
	      	uint16 un16Inj_Gap_Time;
	      	uint16 un16InjCurAD;
	      	uint16 Reversed1;
	      	uint16 Reversed2;
	     }CylinInj_var;
	   
       uint16 un16Reserved[188];
   }item;
}SYS_PARA;

#define SYS_POWERON  0
#define SYS_SINGLE   1
#define SYS_DURAL    2
#define SYS_ERR      3  //³ö´í
#define SYS_HALT     4  //Í£Ö¹


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





//ÕâÊÇsub mode´æ´¢³öÖÂÃü´úÂë


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