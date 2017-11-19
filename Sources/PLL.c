//-------------------------------------------------------------------------*
//文件名: MCUInit.c                                                    	   *
//说  明: 芯片初始化文件                                         		       *
//初始时间：  2012年07月01日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "PLL.h"

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
    CLKSEL = 0x00;       
    SYNR = 0b01011000;
    //       ||||||||_____SYNDIV0:   //SYNDIV   11000 = 24 
    //       |||||||______SYNDIV1:  
    //       ||||||_______SYNDIV2:
    //       |||||________SYNDIV3:
    //       ||||_________SYNDIV4:
    //       |||__________SYNDIV5:   //fvco = 2*4*(19+1)/(1+1) = 80mhz
    //       ||___________VCOFRQ0:   //01   48<fvco<80mhz
    //       |____________VCOFRQ1:

    REFDV = 0b00000001;
    //        ||||||||____REFDIV0:   //REFDIV    01=1  
    //        |||||||_____REFDIV1:  
    //        ||||||______REFDIV2:  
    //        |||||_______REFDIV3:
    //        ||||________REFDIV4:
    //        |||_________REFDIV5:   //fref = 6/(2+1) = 2mhz
    //        ||__________REFFRQ0:   //00  1<fref<2mhz
    //        |___________REFFRQ1:
    
    POSTDIV = 0b00000000;
    //          ||||||||__POSTDIV0:  //POSTDIV  00 = 0
    //          |||||||___POSTDIV1:  //fpll = fvco = 80mhz
    //          ||||||____POSTDIV2:  //fbus = fpll/2 = 40mhz 
    //          |||||_____POSTDIV3:
    //          ||||______POSTDIV4:
    //          |||_______0:
    //          ||________0:
    //          |_________0:
 
    //时钟和复位模块标志寄存器    
 // CRGFLG = 0b00000000; 
    //         ||||||||___SCM:    自给时钟状态位 1 外部晶振停止工作，系统靠自给时钟工作 0 系统靠外部晶振正常工作
    //         |||||||____SCMIF:  自给时钟中断标志位 1 SCM位发生变化 0 SCM位没有发生变化
    //         ||||||_____ILAF:
    //         |||||______LOCK:   锁相环频率锁定标志位 1 已锁定 0 未锁定
    //         ||||_______LOCKIF: 锁相环中断标志位
    //         |||________LVRF:     
    //         ||_________PORF:   上电复位标志位 1 有 0 没有
    //         |__________RTIF:   实时中断标志位 1 有 0 没有
    while(!(CRGFLG&0x08));  
    
 // CLKSEL = 0b00000000;
    //         ||||||||___COPWAI:   循环转换 结束通道 控制位
    //         |||||||____RTIWAI:  （仅在多通道模式下有效）
    //         ||||||_____0:
    //         |||||______PLLWAI:
    //         ||||_______0:
    //         |||________XCLKS:
    //         ||_________PSTP:
    //         |__________PLLSEL:
    CLKSEL = 0x80;        //选定锁相环时钟 
}


