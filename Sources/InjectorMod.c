//-------------------------------------------------------------------------*
//文件名:InjectorModule.c      					                             	     *
//说  明:喷射阀驱动文件											                               *
//初始时间：  2012年07月09日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "InjectorMod.h"
#include "SysTask.h"
extern SYS_PARA sys_para;
#define  G_Inj_HV_Time    sys_para.item.CylinInj_var.un16Inj_HV_Time
#define  G_Inj_Gap_Time  sys_para.item.CylinInj_var.un16Inj_Gap_Time
#define  G_Inj_LV_Time  sys_para.item.CylinInj_var.un16Inj_LV_Time


	

void InjectorTest(uint16 nWide) {

    ECT_TIE   = 0x43;     // 开6中断

}
//-------------------------------------------------------------------------* 
//函数名: ECT_OC6                                                        *
//功  能: ECT输出比较中断                                                        *
//参  数：无                                                               * 
//返  回: 无                                                               * 
//说  明: PA1-10ms PP0-0.4ms PP1-8ms50%的方波   A3 A6  
//Cylinder_1--PK3   Cylinder_2--PA0      
//PA1--DIESELINJ_HV PP0--DIESELINJ_LV                                                  *
//-------------------------------------------------------------------------*  
/*#pragma CODE_SEG __NEAR_SEG NON_BANKED        
interrupt VectorNumber_Vectch6 void ECT_OC6(void) 
{
  if(ECT_TFLG1_C6F == 1)
  {
    ECT_TFLG1_C6F = 1;
  }    
  switch(nSeq) {
    case 0:
    DOOutput(Cylinder_1,ON); //PA0
    asm NOP;
    asm NOP;
    DOOutput(DIESELINJ_HV,ON); //PA1
    ECT_TC6 = ECT_TCNT + In;  //开0.4ms
    nSeq = 1;
    //LEDCPU = ~LEDCPU;
    break;
    case 1: 
    DOOutput(DIESELINJ_HV,OFF); //PP0
    ECT_TC6 = ECT_TCNT + 1000;   //高低压间隔0.4ms
    nSeq = 2;
    break;
    case 2: 
    PWMOutput(1,ON);
    ECT_TC6 = ECT_TCNT + 20000;  //PP1 PWM输出8ms
    nSeq = 3; 
    break;
    case 3:
    PWMOutput(0,OFF);
    asm NOP;
    asm NOP;
    DOOutput(Cylinder_1,OFF);
    nSeq = 0;
    ECT_TC6 = ECT_TCNT + 65000;
    break;
  }
   
}
#pragma CODE_SEG DEFAULT  */
