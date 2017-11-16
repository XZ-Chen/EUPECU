#include "CamshiftModule.h"
#include "MAP.h"
static CAMSHIFT_GROUP_ACCUM A_camshift;

void CamshiftModuleInit(void){
//-------------------------------------------------------------------------*
//    ���벶׽������Ƚ�PT  	                             	               *
//-------------------------------------------------------------------------* 
    uint8 i;
    A_camshift.gearnum = CAMSHIFT_GEAR_NUM;//for test
    A_camshift.rpm = 0;
    A_camshift.average = 0;
    A_camshift.index = 0;   //�ݺų�ʼΪ��
    A_camshift.accum = 0;
    A_camshift.stopcnt = 0;
	A_camshift.CamTeeth = 0;
    for(i=0;i<200;i++)
        A_camshift.array[i] = 0;      
    ECT_TSCR1 = 0x80;              //1000   ����ECT����ʱ������
}
uint16 camshiftSpeedRead(void) { 
  if(A_camshift.stopcnt < 25)   //25*20ms = 500ms��ת���ź�
     A_camshift.stopcnt++;
  else if(A_camshift.stopcnt == 25) 
     return 0;
  if(A_camshift.rpm > CAMSHIFT_RPM_MAX || A_camshift.rpm < CAMSHIFT_RPM_MIN)
     return (30);  
  return (A_camshift.rpm); 
}
//��ʱ��ͨ��0���벶׽�ж�    ����Ƶ��Ϊ2.5M  ÿ������0.4us

#pragma CODE_SEG __NEAR_SEG NON_BANKED        
void interrupt VectorNumber_Vectch1 ECT_IC1(void) 
{
    static uint16 u16TCrank = 0;   //��ǰʱ�����ֵ
    static uint16 u16TCrank0 = 0;  //ǰ��ʱ�����ֵ
    uint16 u16DTCrank;             //����ʱ��������ֵ
    ECT_TFLG1_C1F = 1;                 //ͨ��1���жϱ�־λ
    A_camshift.stopcnt = 0;
    A_camshift.index++;   //͹�ֳݼ�����һ
    if(A_camshift.index >= A_camshift.gearnum)
    {
        A_camshift.index = 0;
        //get the average distance between two gear
        A_camshift.average = A_camshift.accum/A_camshift.gearnum;
    }   
    //get the distance between two gear
  	u16TCrank = ECT_TC1;
  	if(u16TCrank0 != 0 && u16TCrank > 2*u16TCrank0) 
  	{  //˵�������ݺ��һ��
  	   A_camshift.CamTeeth = 1;
  	}
  	else
  	{
	  	if(A_camshift.CamTeeth < 4)
	  	{
		  	A_camshift.CamTeeth ++;
	  	}
  	}
  	if(u16TCrank < u16TCrank0)
  	    u16DTCrank = 65535 - u16TCrank0 + u16TCrank + 1;
		else
		    u16DTCrank = u16TCrank - u16TCrank0;
   	A_camshift.accum = A_camshift.accum - A_camshift.array[A_camshift.index] + u16DTCrank;
  	A_camshift.array[A_camshift.index] = u16DTCrank;
   	u16TCrank0 = u16TCrank;

    
}
#pragma CODE_SEG DEFAULT           

#pragma CODE_SEG __NEAR_SEG NON_BANKED        
void interrupt VectorNumber_Vectpaaovf ECT_Overflow(void) {

	static uint16 OverflowCoun = 0;
	OverflowCoun++; 
  
}
#pragma CODE_SEG DEFAULT   