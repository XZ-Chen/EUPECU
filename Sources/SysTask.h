//-------------------------------------------------------------------------*
//ÎÄ¼şÃû: MCUInit.h                                                    	   *
//Ëµ  Ã÷: Ğ¾Æ¬³õÊ¼»¯Í·ÎÄ¼ş                                         		     *
//×÷Õß£º      ÁõÏş³Ì						                                           *
//³õÊ¼Ê±¼ä£º  2012Äê07ÔÂ01ÈÕ              			                           *
//ĞŞ¶©¼ÇÂ¼£º     		              			                                   *
//±¸×¢£º      ÊÊÓÃÓÚMC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _SYSTASK_H_
#define _SYSTASK_H_


//1 Í·ÎÄ¼ş
#include "typedefine.h"        //ÀàĞÍ±ğÃû¶¨Òå



typedef union _sys_para{
   uint16 data[256];
   struct{
       struct{
          uint16 un16SysMode;       //0 ÏµÍ³Ö÷Ä£Ê½
          uint16 un16DuralMode;     //1 Ë«È¼ÁÏÄ£Ê½
          uint16 un16InjWide;       //2 ÅçÉäÊ±¼ä ÅçÉäÂö³å¿í¶È
          uint16 un16IgSignal;      //3 µã»ğ¿ª¹Ø   
          uint16 un16bSingleMode;      //4 µ¥È¼ÁÏÄ£Ê½¹¤¿ö
          uint16 bSensorScan;       //5 ´«¸ĞÆ÷É¨Ãè
          uint16 bIOScan;           //6 IO¿ÚÉ¨Ãè  
          uint16 bModeJudge;        //7 Ë«È¼ÁÏÄ£Ê½ÅĞ±ğ
          uint16 bOutput;           //8 Êä³ö
          uint16 un16Pedal;         //9 ÓÍÃÅÎ»ÖÃ
                       
       }mem_var;                      
       struct{
         uint16 un16GearNum;          //10 ³İÂÖ³İÊı
         uint16 un16LNGSpeed;         //11 LNGÆô¶¯×ªËÙ
         uint16 un16EstTempMax;       //12 ÅÅÆø×î´óÑ¹Á¦
         uint16 un16StpP1;            //13 µç»úĞĞ³Ì¾ø¶ÔĞŞÕıP1
         uint16 un16HighSpeed;        //14 ¸ßËÙãĞÖµ
         uint16 un16HSK1;             //15 ¸ßËÙĞŞÕıK1 
         uint16 un16LSK2;             //16 µÍËÙĞŞÕıK2
         uint16 un16StpP2;            //17 µç»úĞĞ³Ì¾ø¶ÔĞŞÕıP2
         uint16 un16StpStart;         //18 ²½½øµç»úÆğµã
         uint16 un16StpEnd;           //19 ²½½øµç»úÖÕÖ¹
       }const_var;                
       uint16 un16Sensor[10];        //20·¢¶¯»ú×ªËÙ 21ÓÍÃÅ¿ª¶È Ô¤Áô10¸ö´«¸ĞÆ
       uint16 un16DI[8];             //Ô¤Áô8¸öÊäÈë
       uint16 un16DO[8];             //Ô¤Áô8¸öÊä³ö
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
	        uint16 StartSp;  //Í£Ö¹¹¤¿öÔËĞĞ×î¸ß×ªËÙ
	        uint16 LowStp;   //Æô¶¯¹¤¿öµÄ×îµÍ×ªËÙ
	        uint16 HiStp;    //Æô¶¯¹¤¿ö×î¸ß×ªËÙ
	        uint16 OilStp;   //Æô¶¯¹¤¿öÖĞ¿ªÊ¼¹©ÓÍ×ªËÙ
	        uint8  HiStCount;     //Í³¼Æ´ÎÊı£º³¬¹ıHiStp
	        uint8  PaTiSt;    //×î¸ßÆô¶¯×ªÊı¼ì²â´ÎÊı
	        uint16 Reversed1;
	      	uint16 Reversed2;
	     }StartCondition_var;
	     struct{    //8
	        uint16 StartSp;  //Í£Ö¹¹¤¿öÔËĞĞ×î¸ß×ªËÙ
	        uint16 IdLowSp;   //µ¡ËÙ¹¤¿öµÄ×îµÍ×ªËÙ
	        uint16 IdleFlag;    //Æô¶¯¹¤¿ö×î¸ß×ªËÙ
	        uint16 PID_Array[4];   //Æô¶¯¹¤¿öÖĞ¿ªÊ¼¹©ÓÍ×ªËÙ
	        uint8  HiStCount;     //Í³¼Æ´ÎÊı£º³¬¹ıHiStp
	        uint8  PaTiSt;    //×î¸ßÆô¶¯×ªÊı¼ì²â´ÎÊı
	        uint16 Reversed1;
	      	uint16 Reversed2;
	     }IdleCondition_var;
	        uint16 un16InjEnable; //¹©ÓÍÊ¹ÄÜ
	        uint16 un16InjOilMo;  //¹©ÓÍÁ¿
	        uint16 un16InjWidth;  //¹©ÓÍÂö¿í
	        uint16 un16InjRadian; //¹©ÓÍ³ÖĞø½Ç
	        uint16 un16InjAdvance;  //¹©ÓÍÌáÇ°½Ç
	        uint16 un16InjAdTime;  //¹©ÓÍÌáÇ°Ê±¼ä
	        
	        
       uint16 un16Reserved[179];
   }item;
}SYS_PARA;

#define SYS_POWERON  0
#define SYS_SINGLE   1
#define SYS_DURAL    2
#define SYS_ERR      3  //³ö´í
#define SYS_HALT     4  //Í£Ö¹

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
void StartCondition(void);
void IdleCondition(void); 
void StopCondition(void);

#endif