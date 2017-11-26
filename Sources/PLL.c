//-------------------------------------------------------------------------*
//文件名: PLL.c                                                    	   *              			                       *
//-------------------------------------------------------------------------*
#include "PLL.h"
#define BUS_CLOCK		   40000000	   //总线频率
#define OSC_CLOCK		   4000000	   //晶振频率
//-------------------------------------------------------------------------* 
//函数名: PLLInit                                                         *
//功  能: 锁相环初始化                                                     *
//参  数：无                                                               * 
//返  回: 无                                                               * 
//说  明: Fvco = 2*Fosc*(SYNDIV+1)/(REFDIV+1)                              *                                                               *
//        Fref = Fosc/(REFDIV+1)                                           *
//        Fpll = Fvco/(2*POSTDIV)                                          *
//        Fbus = Fpll/2                                                    *
//-------------------------------------------------------------------------* 
void PLLInit(void){      //设置总线频率为：40M
    CLKSEL &= 0x7f;       //set OSCCLK as sysclk
    PLLCTL &= 0x8F;       //Disable PLL circuit
    CRGINT &= 0xDF;
    
    #if(BUS_CLOCK == 40000000) 
      SYNR = 0x53;
      //SYNR = 0x44;
    #elif(BUS_CLOCK == 32000000)
      SYNR = 0x43;     
    #elif(BUS_CLOCK == 24000000)
      SYNR = 0x42;
    #endif 

    REFDV = 0x81;         //PLLCLK=2×OSCCLK×(SYNR+1)/(REFDV+1)＝64MHz ,fbus=32M
    PLLCTL =PLLCTL|0x70;  //Enable PLL circuit
    asm NOP;
    asm NOP;
    while(!(CRGFLG&0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;        //set PLLCLK as sysclk
}


