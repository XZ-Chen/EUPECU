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
#define  A_InjAdvance      sys_para.item.un16InjAdvance
#define  G_Inj_HV_Time    sys_para.item.CylinInj_var.un16Inj_HV_Time
#define  G_Inj_Gap_Time  sys_para.item.CylinInj_var.un16Inj_Gap_Time
#define  G_Inj_LV_Time  sys_para.item.CylinInj_var.un16Inj_LV_Time
	
void InjectorInit(void) 
{
    A_EngStructPara.DtcCrankI = 17;
    A_EngStructPara.CrankToCam = 17;  
    //A_EngStructPara.TDCAngle =   //����͹����ʱ����Ҫ��ֹ��Ƕ�
    A_EngStructPara.FireSeq[0]= 1;
    A_EngStructPara.FireSeq[1]= 2;
    A_EngStructPara.iMax = 2;
    A_EngStructPara.TDC[0] = 17; //ȱ�ݺ��ʮ�߸��½���
    A_EngStructPara.TDC[1] = 47;
    A_EngStructPara.iR = 1;
}

void OilAngle(void) 
{
    int TDCT;
    int Va_1;
    int Va_2;
    TDCT = A_EngStructPara.TDC[A_EngStructPara.iR];
    Va_1 = (float)A_InjAdvance/6;
    Va_2 =  A_InjAdvance/6;
    if(Va_1 == Va_2)
    {
       A_EngStructPara.OilTeeth = TDCT - A_InjAdvance/6;
       B_InjTimePara.Dtq1 = 0;
    } 
    else
    {
       A_EngStructPara.OilTeeth = TDCT - (int)(A_InjAdvance/6) -1; //ʵ�������źų�
       Va_2 = (int)(((long)A_crank.rpm * 6)/1000000);
       B_InjTimePara.Dtq1 = ((TDCT - A_EngStructPara.OilTeeth) * 6- A_InjAdvance)/Va_2;
    }
    B_InjTimePara.Dtq4 = A_InjWidth - B_InjTimePara.DtqHvTime - B_InjTimePara.DtGaptime; 
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
    ECT_TIE = 0x43;     // ��6�����ж�  
    ECT_TC6 = ECT_TCNT + B_InjTimePara.Dtq1; //���жϵ�����ѡ�׵�λ����
}
void oil_Supply2(void) 
{
    LedTurn(LED2,OFF);
    ECT_TIE = 0x83;     // ��7�����ж�
    ECT_TC7 = ECT_TCNT + B_InjTimePara.Dtq1; //���жϵ�����ѡ�׵�λ����
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
#pragma CODE_SEG __NEAR_SEG NON_BANKED        
interrupt VectorNumber_Vectch6 void ECT_OC6(void) 
{
  static uint8 nSeq = 0;
  if(ECT_TFLG1_C6F == 1)
  {
    ECT_TFLG1_C6F = 1;
  }    
  switch(nSeq) {
    case 0:
    DOOutput(Cylinder_1,ON); //PA0
    ECT_TC6 = ECT_TCNT + B_InjTimePara.Dtq2;  //��λѡ���źŵ���λ���ش򿪼��ʱ��
    nSeq = 1;
    break;
    case 1: 
    DOOutput(DIESELINJ_HV,ON); //PA1
    ECT_TC6 = ECT_TCNT + B_InjTimePara.DtqHvTime;   //��ѹ���س���ʱ�� �̶�ֵ
    nSeq = 2;
    break;
    case 2: 
    DOOutput(DIESELINJ_HV,OFF); //PP0
    ECT_TC6 = ECT_TCNT + B_InjTimePara.DtGaptime;  //�̶�ֵ�ߵ�ѹ���ؼ��ʱ��  
    nSeq = 3; 
    break;
    case 3:
    PWMOutput(1,ON);
    ECT_TC6 = ECT_TCNT + B_InjTimePara.Dtq4; //��ѹ���ش򿪳���ʱ��
    break;
    case 4:
    PWMOutput(1,OFF);
    asm NOP;
    asm NOP;
    asm NOP;
    DOOutput(Cylinder_1,OFF);
 
  }
  ECT_TIE = 0x03;     // �������ж�
   
}
#pragma CODE_SEG DEFAULT 

#pragma CODE_SEG __NEAR_SEG NON_BANKED        
interrupt VectorNumber_Vectch7 void ECT_OC7(void) 
{
  static uint8 nSeq2 = 0;
  EnableInterrupts;
  if(ECT_TFLG1_C7F == 1)
  {
    ECT_TFLG1_C7F = 1;
  }    
  switch(nSeq2) {
    case 0:
    DOOutput(Cylinder_1,ON); //PA0
    asm NOP;
    asm NOP;
    DOOutput(DIESELINJ_HV,ON); //PA1
    ECT_TC6 = ECT_TCNT + 1000;  //��0.4ms
    nSeq2 = 1;
    //LEDCPU = ~LEDCPU;
    break;
    case 1: 
    DOOutput(DIESELINJ_HV,OFF); //PP0
    ECT_TC6 = ECT_TCNT + 1000;   //�ߵ�ѹ���0.4ms
    nSeq2 = 2;
    break;
    case 2: 
    PWMOutput(1,ON);
    ECT_TC6 = ECT_TCNT + 20000;  //PP1 PWM���8ms
    nSeq2 = 3; 
    break;
    case 3:
    PWMOutput(0,OFF);
    asm NOP;
    asm NOP;
    DOOutput(Cylinder_1,OFF);
    nSeq2 = 0;
    ECT_TC6 = ECT_TCNT + 65000;
    break;
  }
  ECT_TIE = 0x03;     // �������ж� 
}
#pragma CODE_SEG DEFAULT 
