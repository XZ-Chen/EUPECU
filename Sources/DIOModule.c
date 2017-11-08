//-------------------------------------------------------------------------*
//文件名: DIODodule.c                                                  	   *
//说  明: 输入输出驱动文件                                         		     *
//初始时间：  2012年07月02日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "DIOModule.h"
#include "GeneralFun.h" 
#include "SPI.h"
#include "DebugConfig.h"



//12路低位大电流功率开关控制引脚
static UINT8 *pHDOCtrlPort[12] =    {&PTP,  &PTP,  &PTP,  &PTP,  &PTP,  &PTS, 
                                     &PORTA,&PORTA,&PORTA,&PORTA,&PORTA,&PORTA};
//12路低位大电流功率开关控制引脚方向控寄存器                            
static UINT8 *pHDOCtrlPortDDR[12] = {&DDRP, &DDRP, &DDRP, &DDRP, &DDRP, &DDRS, 
                                     &DDRA, &DDRA, &DDRA, &DDRA, &DDRA, &DDRA};
//A39441   PTP0 PTP1 PTP2 PTP3 PTP4 PA0
//A39442   PA1  PA2  PA3  PA4  PA5  PA6    
static UINT8 HDOCtrlPortMask[12] =  {0x01,  0x02,  0x04,  0x08,  0x10,  0x02,
                                     0x02,  0x04,  0x08,  0x10,  0x20,  0x40};
//4路高位开关端口  PB1 PB2 PB3 PB4                             
static UINT8 *pDIPort[4] =    {&PORTB,&PORTB,&PORTB,&PORTB};
static UINT8 *pDIPortDDR[4] = {&DDRB, &DDRB, &DDRB, &DDRB};
static UINT8 DIPortMask[4] =  {0x02,  0x04,  0x08,   0x10};

//7路小电流功率开关状态                                    
static uint8 LDOStatus = 0; 

  
  
                                
//A3944初始化
void A3944Init(void) {
   RESTN_A39441_DDR = 1;
   RESTN_A39442_DDR = 1;
   RESTN_A39441 = 0;//超过一定时间重置所有寄存器
   RESTN_A39442 = 0;
   DelayUs(5);
   RESTN_A39441 = 1;//开始诊断
   RESTN_A39442 = 1;  
}

//L9733初始化
void L9733Init(void){
   LDOStatus = 0;
   RESTN_L9733_DDR = 1;
   RESTN_L9733 = 0;
   DelayUs(5);
   RESTN_L9733 = 1;
}

void DIOModuleInit(void)
{
   UINT8 i;
   A3944Init();
   L9733Init();
   for(i=0;i<12;i++) {                     
     *(pHDOCtrlPortDDR[i]) |= HDOCtrlPortMask[i];//相应的控制端口设置为输出
   }
   for(i=0;i<4;i++) {
     *(pDIPortDDR[i]) &= (~DIPortMask[i]); //相应端口设置为输入
   }
   
}
//高位开关扫描
uint16 DIRead(uint8 pin){
   uint8 ch;
   if(pin>PIN23_DI)
      return 0xff;
   ch = pin;
   if(*(pDIPort[ch]) & DIPortMask[ch])
      return ON;
   else
      return OFF;     
}
//小电流功率开关输出
uint16 LDOOutput(uint8 ch,uint8 val) {
    uint16 cmd;
    if(val == 1)
      LDOStatus = BSET(ch,LDOStatus);
    else
      LDOStatus = BCLR(ch,LDOStatus); 
    cmd = CMD_L9733_OUTPUT | LDOStatus;
    return SPIWriteWord(SPI_L9733,cmd);
}
//大电流功率开关输出
uint16 HDOOutput(uint8 ch,uint8 val){
   if(val == ON)
      *(pHDOCtrlPort[ch]) |=  HDOCtrlPortMask[ch];
   else
      *(pHDOCtrlPort[ch]) &=  (~HDOCtrlPortMask[ch]);
   return 0;
}
//高位开关扫描
void DIScan(uint16 *pDI) 
{
  #if(DEBUGMODE == 1)  
    *pDI = DIRead(DI_IGSWITCH_PIN);
    *(pDI+1) = DIRead(DI_LNGSWITCH_PIN);
  #elif(DEBUGMODE == 2)   
    *pDI = ON;
    *(pDI+1) = ON;
  #endif
}
//读高位开关状态

//功率开关输出
uint16 DOOutput(uint8 pin,uint8 val) {
   if(val != 1 && val != 0)
      return 0;
   if(pin <= PIN49_LDO) {  
      return LDOOutput(pin,val);
   } else if(pin <= PIN56_HDO){
      return HDOOutput(pin - 7,val);
   } 
}


























