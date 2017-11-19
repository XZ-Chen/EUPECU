//-------------------------------------------------------------------------*
//文件名:InjectorModule.c      					                             	     *
//说  明:喷射阀驱动文件											                               *
//初始时间：  2012年07月09日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "InjectorModule.h"
#include "CrankModule.h"
static uint16 InjectorIndex = 0;
//static uint16 InjectorPIN[CRANK_CYLINDER_NUM] = {INJECTOR_PIN1,INJECTOR_PIN2,INJECTOR_PIN3,
                      //          INJECTOR_PIN4,INJECTOR_PIN5,INJECTOR_PIN6};
  static uint16 InjectorPIN[CRANK_CYLINDER_NUM] = {INJECTOR_PIN1,INJECTOR_PIN2,INJECTOR_PIN3,
                               INJECTOR_PIN4};
//-------------------------------------------------------------------------*
//函数名: InjectorModuleInit                                                   	     *
//功  能: 初始化喷射阀                                                 * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
//A3944 1-6 接PP0~PP4和PA0
//      7-12接PA1~PA6

void InjectorModuleInit(void)
{
   DOOutput(INJECTOR_PIN1,OFF);
   DOOutput(INJECTOR_PIN2,OFF);
   DOOutput(INJECTOR_PIN3,OFF);
   DOOutput(INJECTOR_PIN4,OFF);
   DOOutput(INJECTOR_PIN5,OFF);
   DOOutput(INJECTOR_PIN6,OFF);
   PITCE_PCE1 = 0;  //PIT通道禁能 
   PITCE_PCE2 = 0; //停止喷射阀
          
}
void InjectorWide(uint16 nCycle,uint16 nWide) //喷射时间
{
    if(nCycle == 0 || nWide == 0) { 
       DOOutput(INJECTOR_PIN1,OFF);
       DOOutput(INJECTOR_PIN2,OFF);
       DOOutput(INJECTOR_PIN3,OFF);
       DOOutput(INJECTOR_PIN4,OFF);
       DOOutput(INJECTOR_PIN5,OFF);
       DOOutput(INJECTOR_PIN6,OFF);
       PITCE_PCE1 = 0;
       PITCE_PCE2 = 0; //停止喷射阀 
       InjectorIndex = 0;
       return;      
    }
    PITSetCycle(1,nCycle);     //时间 (周期)
    PITSetCycle(2,nWide);      //脉宽
    PITCE_PCE1 = 1;             //enable timer channel 1  
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt VectorNumber_Vpit1 PIT1_ISR(void)                        
{ 
    PITTF = 0x02;    //CLEAR FLAG
    DOOutput(INJECTOR_PIN1,ON);
    DOOutput(INJECTOR_PIN2,ON);
    DOOutput(INJECTOR_PIN3,ON);
    DOOutput(INJECTOR_PIN4,ON);
    DOOutput(INJECTOR_PIN5,ON);
    DOOutput(INJECTOR_PIN6,ON);
    PITCE_PCE2 = 1;             //enable timer channel 2
                                                                               
}
#pragma CODE_SEG DEFAULT

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt VectorNumber_Vpit2 PIT2_ISR(void)                        
{  
    PITTF = 0x04;;    //CLEAR FLAG 
    PITCE_PCE2 = 0;             //disable timer channel 2 
    DOOutput(INJECTOR_PIN1,OFF);
    DOOutput(INJECTOR_PIN2,OFF);     
    DOOutput(INJECTOR_PIN3,OFF);
    DOOutput(INJECTOR_PIN4,OFF); 
    DOOutput(INJECTOR_PIN5,OFF);
    DOOutput(INJECTOR_PIN6,OFF);
    //InjectorIndex ++;
    //if(InjectorIndex == CRANK_CYLINDER_NUM)
       //InjectorIndex = 0;                                                                          
}
#pragma CODE_SEG DEFAULT
