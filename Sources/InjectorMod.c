//-------------------------------------------------------------------------*
//�ļ���:InjectorModule.c      					                             	     *
//˵  ��:���䷧�����ļ�											                               *
//��ʼʱ�䣺  2012��07��09��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "InjectorMod.h"
#include "SysTask.h"
#include "CrankModule.h"
#include "LedKey.h"



EngStructPara A_EngStructPara;
InjTimePara   B_InjTimePara;
extern SYS_PARA sys_para;
extern GROUP_ACCUM A_crank;

#define  A_InjWidth      sys_para.item.mem_var.un16InjWide
#define  G_Inj_HV_Time    sys_para.item.CylinInj_var.un16Inj_HV_Time
#define  G_Inj_Gap_Time  sys_para.item.CylinInj_var.un16Inj_Gap_Time
#define  G_Inj_LV_Time  sys_para.item.CylinInj_var.un16Inj_LV_Time


	

//void InjectorTest(uint16 nWide) {

//    ECT_TIE   = 0x43;     // ��6�ж�

//}

void OilAngle(void) 
{
    int TDCT;
    int Va_2;
    TDCT = A_EngStructPara.TDC[A_EngStructPara.iR+1];
    A_EngStructPara.OilTeeth = TDCT - (int)(A_EngStructPara.InjAdvance/6.43) -1; //ʵ�������źų�
    Va_2 = (int)(((long)A_crank.rpm * 6.43)/1000000);
    B_InjTimePara.Dtq1 = ((TDCT - A_EngStructPara.OilTeeth) * 6.43- A_EngStructPara.InjAdvance)/Va_2;
    B_InjTimePara.Dtq4 = A_InjWidth - B_InjTimePara.Dtq2 - B_InjTimePara.Dtq3; 
}
void Oil_Sup(void)
{
    switch(A_EngStructPara.iR) 
    {
      case 1: oil_Supply1();break;
      case 2: oil_Supply2();break; 
    }
}
void oil_Supply1(void) 
{
    LedTurn(LED1,OFF);
}
void oil_Supply2(void) 
{
    LedTurn(LED2,OFF);
}
//-------------------------------------------------------------------------* 
//������: ECT_OC6                                                        *
//��  ��: ECT����Ƚ��ж�                                                        *
//��  ������                                                               * 
//��  ��: ��                                                               * 
//˵  ��: PA1-10ms PP0-0.4ms PP1-8ms50%�ķ���   A3 A6  
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
    ECT_TC6 = ECT_TCNT + In;  //��0.4ms
    nSeq = 1;
    //LEDCPU = ~LEDCPU;
    break;
    case 1: 
    DOOutput(DIESELINJ_HV,OFF); //PP0
    ECT_TC6 = ECT_TCNT + 1000;   //�ߵ�ѹ���0.4ms
    nSeq = 2;
    break;
    case 2: 
    PWMOutput(1,ON);
    ECT_TC6 = ECT_TCNT + 20000;  //PP1 PWM���8ms
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
