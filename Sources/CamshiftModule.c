#include "CamshiftModule.h"
#include "MAP.h"
static CAMSHIFT_GROUP_ACCUM A_camshift;

void CamshiftModuleInit(void){
//-------------------------------------------------------------------------*
//    输入捕捉和输出比较PT  	                             	               *
//-------------------------------------------------------------------------* 
    uint8 i;
    A_camshift.gearnum = CAMSHIFT_GEAR_NUM;//for test
    A_camshift.rpm = 0;
    A_camshift.average = 0;
    A_camshift.index = 0;   //齿号初始为零
    A_camshift.accum = 0;
    A_camshift.stopcnt = 0;
	A_camshift.CamTeeth = 0;
    for(i=0;i<200;i++)
        A_camshift.array[i] = 0;      
    ECT_TSCR1 = 0x80;              //1000   允许ECT主定时器运行
}
uint16 camshiftSpeedRead(void) { 
  if(A_camshift.stopcnt < 25)   //25*20ms = 500ms无转速信号
     A_camshift.stopcnt++;
  else if(A_camshift.stopcnt == 25) 
     return 0;
  if(A_camshift.rpm > CAMSHIFT_RPM_MAX || A_camshift.rpm < CAMSHIFT_RPM_MIN)
     return (30);  
  return (A_camshift.rpm); 
}
//定时器通道0输入捕捉中断    采样频率为2.5M  每个计数0.4us

#pragma CODE_SEG __NEAR_SEG NON_BANKED        
void interrupt VectorNumber_Vectch1 ECT_IC1(void) 
{
    static uint16 u16TCrank = 0;   //当前时间计数值
    static uint16 u16TCrank0 = 0;  //前次时间计数值
    uint16 u16DTCrank;             //两齿时间间隔计数值
    ECT_TFLG1_C1F = 1;                 //通道1清中断标志位
    A_camshift.stopcnt = 0;
    A_camshift.index++;   //凸轮齿计数加一
    if(A_camshift.index >= A_camshift.gearnum)
    {
        A_camshift.index = 0;
        //get the average distance between two gear
        A_camshift.average = A_camshift.accum/A_camshift.gearnum;
    }   
    //get the distance between two gear
  	u16TCrank = ECT_TC1;
  	if(u16TCrank0 != 0 && u16TCrank > 2*u16TCrank0) 
  	{  //说明到达多齿后第一齿
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