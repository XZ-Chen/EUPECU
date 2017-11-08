/**************************************************************************/
/* FILE NAME: interrupt.c   COPYRIGHT (c) GL Automotive Electronics 2009  */
/* VERSION: 3.0                                   All Rights Reserved     */
/*                                                                        */
/* DESCRIPTION: This file is the main program including main loop.        */
/*                                                                        */
/*========================================================================*/
/* HISTORY           ORIGINAL AUTHOR: colin                               */
/*                                                                        */
/* REV     AUTHOR       DATE       DESCRIPTION OF CHANGE                  */
/* ---   -----------  ---------    ---------------------                  */
/* 1.0      colin    2005-03-01    Initial version of function.           */
/* 2.0      colin    2009-10-14    Autobase  version                      */
/* 3.0      colin    2011-01-10    Advanced  version                      */
/**************************************************************************/
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "SysTask.h"

extern SYS_PARA sys_para;
#define bSensorScan      sys_para.item.mem_var.bSensorScan
#define bIOScan          sys_para.item.mem_var.bIOScan
#define bModeJudge       sys_para.item.mem_var.bModeJudge
#define bOutput          sys_para.item.mem_var.bOutput

//************************中断函数************************   

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt VectorNumber_Vpit0 SYSTEM_TIMER_ISR(void)         //PIT中断               
{ 
    // 40MHZ 1ms timer overflow
    static uint16 nTicks = 0;           //静态变量 初始化一次
    PITTF = 0x01;    //CLER FLAG
    nTicks ++;
    if(nTicks%2 == 0) //2ms
      bOutput = TRUE;
    if(nTicks%15 == 0) //15ms
      bIOScan = TRUE;
    if(nTicks%20 == 0)   //20ms   
      bSensorScan = TRUE;
    if(nTicks%200 == 0)
    {  //200ms
      bModeJudge = TRUE;
    }
    if(nTicks == 60000)
      nTicks = 0;
}
#pragma CODE_SEG DEFAULT

