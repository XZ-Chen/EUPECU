//-------------------------------------------------------------------------*
//文件名: ConditionProcess.c 					                             	                 *
//说  明: 工况处理函数											                           *
//初始时间：  2017年11月16日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*

#include "ConditionProcess.h"
#include "SysTask.h"
#include "MAP.h"

extern SYS_PARA sys_para;
#define G_InjEnable        sys_para.item.un16InjEnable
#define G_InjOilMo         sys_para.item.un16InjOilMo
#define G_DieInjWidth      sys_para.item.un16un16InjWidth;
#define G_un16RPM          sys_para.item.un16Sensor[0]
#define G_un16CoolWaterTemp  sys_para.item.un16Sensor[3]          //

#define G_STLowStp     sys_para.item.StartCondition_var.LowStp //
#define G_STHiStp      sys_para.item.StartCondition_var.HiStp //
#define G_STOilStp     sys_para.item.StartCondition_var.OilStp //
#define G_STHiStCount  sys_para.item.StartCondition_var.HiStCount //
#define G_STPaTiSt     sys_para.item.StartCondition_var.PaTiSt //
 
	     uint16 un16InjOilMo;
	     uint16 un16InjWidth;
void StartCondition_Sub(void)
{
    UINT16 Vary_InjWidth;
    UINT16 Vary_InjAdvance;
    if(G_un16RPM > G_STOilStp) 
    {
        G_InjEnable = ON;
    } 
    else
    {
        G_InjEnable = OFF;
    }
    G_InjOilMo = look2D_U16_U16_U16(G_un16CoolWaterTemp,G_un16RPM, \
                    	u16TabCWTX, 9,\
                    	u16TabSpeedY, 29,u16TabStartOil);
                    	
}