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
                    	u16TabCWTX, 9,\
                    	u16TabSTSpeedY, 29,u16TabStartOil);
    //此处可根据液温对提前角进行修正
    G_InjAdvance = Vary_InjAdvance;  //确定供油提前角
    G_InjAdTime = G_un16RPM * 3600 /(60*1000*1000)/G_InjAdvance;  //确定供油提前时间
}
        
void IdleCondition(void) 
{
     
}
































