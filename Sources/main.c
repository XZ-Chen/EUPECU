#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "Includes.h"
//#include "MAP.h"
#include "PLL.h"
#include "PIT.h"
#include "ECT.h"
#include "SPI.h"
#include "DataFlash.h"
#include "DFlashModule.h"
#include "MSCan.h"
#include "ATD.h"
#include "PinMap.h"


void main(void) {
  //关总中断
  DisableInterrupts;
  //MCU peripheral unit initial
  PLLInit();            //Fbus = 40MHZ           
  MSCANInit();            //CAN Baudrate = 500KHZ
  DFlashInit();         //Data Flash initial  
  PITInit();
  SPIInit();
  ATDInit();
  ECTInit();
  //ECU peripheral devices initial 
  DIOModuleInit();      //PORTB 4 input,4 output
  SensorModuleInit();   //stepper pos; exhaust temp;pedal pos;
  CrankModuleInit();    //crankshaft speed measurement 
  InjectorModuleInit(); //Injector module initial
  StepperModuleInit();  //Steppermotor initial
  SysVarInit(); 
  StartSystemTimer();  //开启定时器
  _ENABLE_COP_X();      //看门狗设置
  JudgeFlashStatus();   //判断Flash是否被写入
  EnableInterrupts; 
  for(;;)
  {
      SysTaskProcess();   //System task
      MSCANProcess();     //CAN Communication
      SysDigProcess();    //Disgnose
      _FEED_COP();        // feeds the dog 
           
  }
  /* please make sure that you never leave main */
}