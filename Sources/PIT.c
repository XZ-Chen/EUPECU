//-------------------------------------------------------------------------*
//文件名: PIT.c                                                        	   *
//说  明: 周期性中断驱动文件                                       		     *
//初始时间：  2012年07月02日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "PIT.h"

//-------------------------------------------------------------------------* 
//函数名: PIT_Init                                                         *
//功  能: 周期中断定时器初始化                                             *
//参  数: 无                                                               *
//返  回: 无                                                               * 
//说  明: 无                                                               *
//-------------------------------------------------------------------------*  
void PITInit(void){
   PITCFLMT_PITE = 0;          //disable PIT
   PITMUX_PMUX0 = 0;           //ch0 connected to micro timer 0
   PITMUX_PMUX1 = 1;           //ch1 connected to micro timer 1
   PITMUX_PMUX2 = 1;           //ch2 connected to micro timer 1
   PITMUX_PMUX3 = 0;           //ch3 connected to micro timer 0
   PITMTLD0 = 39 ;             //micro time base 0 equals 39 clock cycles   1us
   PITMTLD1 = 39 ;             //micro time base 1 equals 39 clock cycles   1us  
   PITLD0 = 999;               //time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS. 
   //1ms的周期中断                  
   PITINTE_PINTE0 = 1;        //enable interupt channel 0
   PITINTE_PINTE1 = 1;        //enable interupt channel 1  
   PITINTE_PINTE2 = 1;        //enable interupt channel 2 
   PITINTE_PINTE3 = 1;        //enable interupt channel 3
   PITCFLMT_PITE = 1;         //使能定时器
   PITCE_PCE0 = 0;
   PITCE_PCE1 = 0;
   PITCE_PCE2 = 0;
   PITCE_PCE3 = 0;
                              
}
static uint16 *pPITLDn[4] = {&PITLD0,&PITLD1,&PITLD2,&PITLD3};
void PITSetCycle(uint8 nCh,uint16 nUs) {

     if(nCh > 3)
         return;
     *pPITLDn[nCh] = nUs - 1;
}


