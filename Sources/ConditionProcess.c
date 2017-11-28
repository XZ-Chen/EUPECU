//-------------------------------------------------------------------------*
//文件名: ConditionProcess.c 					                             	                 *
//说  明: 工况处理函数											                           *
//初始时间：  2017年11月16日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*

#include "ConditionProcess.h"
#include "MAP.h"
#include "SysTask.h"

extern SYS_PARA sys_para;

#define G_InjEnable        sys_para.item.un16InjEnable
#define G_InjOilMo         sys_para.item.un16InjOilMo
#define G_DieInjWidth      sys_para.item.un16InjWidth
#define G_un16RPM          sys_para.item.un16Sensor[0]
#define G_CoolWaterTemp    sys_para.item.un16Sensor[3]                  //
#define G_InjAdvance       sys_para.item.un16InjAdvance
#define G_InjAdTime        sys_para.item.un16InjAdTime

#define G_STLowStp     sys_para.item.StartCondition_var.LowStp            //
#define G_STHiStp      sys_para.item.StartCondition_var.HiStp             //
#define G_STOilStp     sys_para.item.StartCondition_var.OilStp            //
#define G_STHiStCount  sys_para.item.StartCondition_var.HiStCount         //
#define G_STPaTiSt     sys_para.item.StartCondition_var.PaTiSt            //
#define G_InjRadian    sys_para.item.un16InjRadian     //
#define G_IdGoSp          sys_para.item.IdleCondition_var.IdGoSp
#define G_IdGoSpOffset sys_para.item.IdleCondition_var.IdGoSpOffset
#define G_PID_ArrayBgn	  sys_para.item.IdleCondition_var.PID_Array
//-------------------------------------------------------------------------*
//函数名: void StartCondition_Sub(void) 					                             	                 *
//说  明: 启动工况处理函数											                           *
//1、判断是否到达最低供油转速              			           			           *
//2、查供油量
//3、查供油脉宽     		              			           				                 *
//4、求持续供油角
//5、查供油提前角
//6、求供油提前时间
//备注：根据冷却液温度 电源电压等修正功能还未完成                       	                 *
//-------------------------------------------------------------------------*
void StartCondition_Sub(void)
{
    UINT16 Vary_InjWidth;
    UINT16 Vary_InjAdvance;
    if(G_un16RPM >= G_STOilStp) 
    {
        G_InjEnable = ON;
    } 
    else
    {
        G_InjEnable = OFF;
    }
    G_InjOilMo = look2D_U16_U16_U16(G_CoolWaterTemp,G_un16RPM, \
                    	u16TabCWTX, 9,\
                    	u16TabSTSpeedY, 29,u16TabStartOil);
    Vary_InjWidth = look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabSpeedY, 29,u16TabInjWidth); 
    
    G_DieInjWidth = Vary_InjWidth;
    G_InjRadian = 6.43 * G_DieInjWidth * G_un16RPM / 100000; 
    Vary_InjAdvance = look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabOilAngleSpeedY, 29,u16TabOilAdAngle);
    //此处可根据液温对提前角进行修正
    G_InjAdvance = Vary_InjAdvance;  //确定供油提前角
    G_InjAdTime = G_un16RPM * 3600 /(60*1000*1000)/G_InjAdvance;  //确定供油提前时间
}
        
void IdleCondition_PID(void) 
{
  int Error,Derror,Output;
  int Vary_InjWidth, Vary_InjAdvance;
  Error = G_IdGoSp - G_un16RPM; //本次处理的转速偏差 -积分项
  if(Error < G_IdGoSpOffset)
		return;
	Derror = Error - *(G_PID_ArrayBgn+2); //二次偏差
	*(G_PID_ArrayBgn) =  look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabOilAngleSpeedY, 29,u16TabOilAdAngle);
	*(G_PID_ArrayBgn+1) =  look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabOilAngleSpeedY, 29,u16TabOilAdAngle);
	Output = *(G_PID_ArrayBgn) * Derror;
	Output += *(G_PID_ArrayBgn+3);
	*(G_PID_ArrayBgn+2) = Error;//记录本次偏差供下次使用
	*(G_PID_ArrayBgn+3) = look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabOilAngleSpeedY, 29,u16TabOilAdAngle);//查map求等转速油量限制
   if(Output > *(G_PID_ArrayBgn+3))
   {
		Output = *(G_PID_ArrayBgn+3);//目标油量取限制值
	 }
	 *(G_PID_ArrayBgn+3) = look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabOilAngleSpeedY, 29,u16TabOilAdAngle);//记录本次调整后的供油量供下次使用
         G_InjOilMo = Output;
	  Vary_InjWidth =  look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabOilAngleSpeedY, 29,u16TabOilAdAngle);//记录本次调整后的供油量供下次使用
    /*     Vary_InjWidth *=  look2D_U16_U16_U16(G_InjOilMo,G_un16RPM, \
                    	u16TabInjOilMoX, 9,\
                    	u16TabOilAngleSpeedY, 29,u16TabOilAdAngle)  / 100;//根据电压值做修正 */
	  G_DieInjWidth = Vary_InjWidth; //确定最终怠速供油脉宽 
	  G_InjAdTime = G_un16RPM * 3600/(60*1000*1000)/G_InjAdvance;//确定供油提前时间 可由上位机提供
}

void StopCondition_Sub(void)
{
     //关闭外围设备 如涡轮等
}































