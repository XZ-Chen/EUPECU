//-------------------------------------------------------------------------*
//文件名:CrankModule.c      					                     	               *
//说  明:TIM定时器驱动文件，用于曲轴转速测量  	                           *
//初始时间：  2012年07月09日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "CrankModule.h"
#include "CamshiftModule.h"
#include "InjectorMod.h"
#include "SysTask.h"
#include "SCI.h"

extern SYS_PARA sys_para;
#define G_bOilAngle          sys_para.item.CylinInj_var.bOilAngle

static GROUP_ACCUM           A_crank;
extern EngStructPara         A_EngStructPara;
extern CAMSHIFT_GROUP_ACCUM  A_camshift;
extern EngStructPara         A_EngStructPara;

//-------------------------------------------------------------------------*
//函数名: CrankModuleInit                                                   	     *
//功  能: 初始化定时器模块                                                 * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
//喷射阀跟转速还有同步关系
//用OC行不通，因为大周期不能调，即TCNT不让设置
//转速高时，没有脉冲信号进来，没法测
//电路有问题               
//改用NCV1124转速测量芯片，已经解决
void CrankModuleInit(void){
//-------------------------------------------------------------------------*
//    输入捕捉和输出比较PT  	                             	               *
//-------------------------------------------------------------------------* 
    uint8 i;
    A_crank.gearnum = CRANK_GEAR_NUM;//for test
    A_crank.rpm = 0;
    A_crank.average = 0;
    A_crank.index = 0;
    A_crank.accum = 0;
    A_crank.stopcnt = 0;
    A_crank.CrankTeeth = 0;
    for(i=0;i<200;i++)
        A_crank.array[i] = 0;      
    ECT_TSCR1 = 0x80;              //1000   允许ECT主定时器运行
}
uint16 CrankSpeedRead(void) { 
  if(A_crank.stopcnt < 25)   //25*20ms = 500ms无转速信号
     A_crank.stopcnt++;
  else if(A_crank.stopcnt == 25) 
     return 0;
  if(A_crank.rpm > CRANK_RPM_MAX || A_crank.rpm < CRANK_RPM_MIN)
     return (30);  
  return (A_crank.rpm); 
}
//定时器通道0输入捕捉中断    采样频率为2.5M  每个计数0.4us


//OilAngle 在曲轴中断中调用，后期曲轴中断应该另写为扩展函数 CSI_Sub
UINT8 OilAngleTips[]="execute OilAngle";

#pragma CODE_SEG __NEAR_SEG NON_BANKED        
void interrupt VectorNumber_Vectch0 ECT_IC0(void) 
{
    static uint16 u16TCrank = 0;   //当前时间计数值
    static uint16 u16TCrank0 = 0;  //前次时间计数值
    uint16 u16DTCrank;             //两齿时间间隔计数值
    EnableInterrupts;
    ECT_TFLG1_C0F = 1;                 //清中断标志位
    A_crank.stopcnt = 0;
    
    if(A_crank.index >= A_crank.gearnum)
    {
        A_crank.index = 0;
        //get the average distance between two gear
        A_crank.average = A_crank.accum/A_crank.gearnum;
    }   
    //get the distance between two gear
  	u16TCrank = ECT_TC0;
  	if(u16TCrank > 2*u16TCrank0) // 当前齿是曲轴缺齿后第一齿
  	{
  	    if(A_camshift.CamTeeth == 1) 
  	    {
  	        A_crank.index = 0;  
  	    } 
  	    else if(A_camshift.CamTeeth == 3)
  	    {
  	        A_crank.index = 60; 
  	    }
  	}else 
  	{
  	   A_crank.index++;
  	   SCI_SendDec16u(A_crank.index);
    }
  	if(A_crank.index == 2)      //当前齿号为2 下一工作汽缸是第一缸
  	{
  	    A_EngStructPara.iR = 1; //下一工作气缸是第一缸
  	} else if(A_crank.index == 62)  //当前齿号为62 下一工作汽缸是第一缸
    {
        A_EngStructPara.iR = 2; //下一工作气缸是第二缸
    }
  	if(u16TCrank < u16TCrank0)
  	    u16DTCrank = 65535 - u16TCrank0 + u16TCrank + 1;
		else
		    u16DTCrank = u16TCrank - u16TCrank0;
   	A_crank.accum = A_crank.accum - A_crank.array[A_crank.index] + u16DTCrank;
  	A_crank.array[A_crank.index] = u16DTCrank;
   	
    if(A_crank.average>0)  
       A_crank.rpm = 185000000/A_crank.average/A_crank.gearnum;
 
    if(A_crank.index == A_EngStructPara.TDC[A_EngStructPara.iR] + 15) 
        A_EngStructPara.iR = A_EngStructPara.FireSeq[A_EngStructPara.iR];
    
    if(A_crank.index == A_EngStructPara.TDC[A_EngStructPara.iR] - 12)
    {
        G_bOilAngle = TRUE;            //激活Oilangle（）
    }   //根据供油提前角得到Dtq1和Dtq2
    
    if(A_crank.index == A_EngStructPara.OilTeeth) 
    {
        Oil_Sup();   
        send_string(OilAngleTips);                        
    }
    
    u16TCrank0 = u16TCrank;
}
#pragma CODE_SEG DEFAULT
   	    


