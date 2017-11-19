//-------------------------------------------------------------------------*
//文件名:StepperModule.c      	                           	               *
//说  明:步进电机驱动文件		    								                           *
//初始时间：  2012年07月09日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "StepperModule.h"
#include "SPI.h"


//-------------------------------------------------------------------------*
//函数名: StepperModuleInit                                          	     *
//功  能: 初始化步进电机模块                                               * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
#define CMD_L9935_STOP 0xff
static uint16 CMD_L9935_PHASE[STEPPER_PHASE_NUM] = {0x1b,0x13,0x12,0x1a};
//static uint16 CMD_L9935_PHASE[8] = {0x1b,0x3b,0x13,0x17,0x12,0x32,0x1a,0x1e};  //half step

static uint16 StepperCurPos = 0;
static uint16 StepperDesPos = 0;
static uint8 StepperPhase = 0;
static uint16 Ret = 0;

void StepperStop(void){
   SPIWriteWord(SPI_L9935,CMD_L9935_STOP);
}
uint16 StepperCW(void) {
   uint16 ret;
   if(StepperPhase == STEPPER_PHASE_NUM - 1)
     StepperPhase = 0;
   else
     StepperPhase ++;
   ret = SPIWriteWord(SPI_L9935,CMD_L9935_PHASE[StepperPhase]);
   StepperCurPos ++;
   return ret;
}
uint16 StepperCCW(void) {
   uint16 ret;
   if(StepperPhase == 0)
     StepperPhase = STEPPER_PHASE_NUM - 1;
   else
     StepperPhase --;
   ret = SPIWriteWord(SPI_L9935,CMD_L9935_PHASE[StepperPhase]);
   StepperCurPos --; 
   return ret;
}
void StepperModuleInit(void)
{   
   STEPPER_EN_L9935_DDR = 1;
   STEPPER_EN_L9935 = 0;
   DelayMs(1);
   StepperStop(); 
}
uint8 StepperRun(uint16 nDesPos,uint16 nDesPosAD,uint16 nCurPosAD) 
{
   static uint16 ticks = 0;
   StepperDesPos = nDesPos;   //nDesPos * 16(16分频）
   if(StepperCurPos == StepperDesPos) {
        ticks ++;
        if(ticks == 25) {  //50ms
            if(nCurPosAD < nDesPosAD - STEPPER_POSERR && StepperCurPos > 15){
                StepperCurPos = StepperCurPos - 15;  
            }
            else if(nCurPosAD > nDesPosAD + STEPPER_POSERR) {
                StepperCurPos = StepperCurPos + 15;
            }
            ticks = 0;
        } else{  
          StepperStop();
          return STEPPER_REACH;
        }
   } else if(StepperCurPos > StepperDesPos) {
      Ret = StepperCCW();//正转
   }
   else{
      Ret = StepperCW();      
   }
   return STEPPER_RUN;
}


