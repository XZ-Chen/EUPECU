//-------------------------------------------------------------------------*
//文件名: SPI.c 					                             	                   *
//说  明: SPI串行通讯驱动文件  											                       *
//初始时间：  2012年07月12日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "SPI.h"
#include "GeneralFun.h"
//-------------------------------------------------------------------------*
//函数名: SPIInit                                                  	       *
//功  能: 初始化SPI模块                                                    * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: A39441,A39442,MAX6675---->SPI0    PE5  PE4  PS7
//                     CJ125------->SPI1 
//                L9733,L9935------>SPI2    PE6  PE7
//-------------------------------------------------------------------------*
void SPIInit(void){
    //SPI控制寄存器1
    SPI0CR1 = 0b01010110;    //
    SPI1CR1 = 0b01010110; 
    SPI2CR1 = 0b01011110;    //经过无数次的验证，极性要设置成11，我哭啊
    //          ||||||||_____LSBFE:   LSB在先使能位
    //          |||||||______SSOE:    随从选择输出使能位
    //          ||||||_______CPHA:    SPI时钟相位选择位  0在奇数沿采样  1在偶数沿采样
    //          |||||________CPOL:    SPI时钟极性位 1 空闲为高 0 空闲为低
    //          ||||_________MSTR:    SPI主从模式位 Master = 1 Slave = 0
    //          |||__________SPTIE:   SPI数据传输中断使能 1 使能 0 禁止 
    //          ||___________SPE:     SPI系统使能位 1 使能 0 禁止
    //          |____________SPIE:    SPI中断使能位 1 使能 0 禁止
    
    //SPI控制寄存器2
    SPI0CR2 = 0b01000000;
    SPI1CR2 = 0b01010000; 
    SPI2CR2 = 0b01000000; 
    //          ||||||||_____SPC0:    串行引脚控制位 1 双工 0 普通模式
    //          |||||||______SPISWAI: 在等待模式下SPI停止位 1 正常 0 停止
    //          ||||||_______0
    //          |||||________BIDIROE: 在双工模式下输出缓冲使能位
    //          ||||_________MODFEN:  模式故障功能使能位 1 使能 0 禁止
    //          |||__________0
    //          ||___________XFRW:    位宽选择： 1 16位 0 8位   
    //          |____________0

    //SPI波特率选择寄存器
    SPI0BR = 0b01000001;     //       F = 2M 分频系数 = (SPPR+1)*2^(SPR+1) = 20
    SPI1BR = 0b01000010;     //       F = 1M 分频系数 = (SPPR+1)*2^(SPR+1) = 40
    SPI2BR = 0b01000010;     //       F = 1M
    //         ||||||||______SPR0:    SPI波特率选择位
    //         |||||||_______SPR1:    bus = 40mhz
    //         ||||||________SPR2:
    //         |||||_________0
    //         ||||__________SPPR0:   SPI波特率预选择位
    //         |||___________SPPR1: 
    //         ||____________SPPR2: 
    //         |_____________0
    
    //SPI数据寄存器
//  SPI_SR = 0b10110000;
    //         ||||||||______0
    //         |||||||_______0
    //         ||||||________0
    //         |||||_________0
    //         ||||__________MODF:    SPI模式错误标志位 1 模式错误发生 0 模式错误不发生
    //         |||___________SPTEF:   SPI传输空中断标志位 1 SPI0DR为空 0 SPI0DR不能为空   
    //         ||____________0 
    //         |_____________SPIF:    SPI中断请求位 1 新数据复制到SPI0DR 0 数据传输未完成
    DDRS |= 0xf0;
    DDRH |= 0xff; 
    MODRR_MODRR4 = 0; //SPI0--->PS4 PS5 PS6 PS7
    MODRR_MODRR5 = 1; //SPI1--->PH0 PH1 PH2 PH3
    MODRR_MODRR6 = 1; //SPI2--->PH4 PH5 PH6 PH7
    
    //DDRE |= 0xf0;  //PE4,PE5,PE6,PE7 set as ouput
    SPI_CSN_L9733_DDR = 1;
    SPI_CSN_L9935_DDR = 1;
    SPI_CSN_A39441_DDR = 1;
    SPI_CSN_A39442_DDR = 1;
    SPI_CSN_MAX6675_DDR = 1;
    
    SPI_CSN_MAX6675 = 1;
    SPI_CSN_L9733 = 1;
    SPI_CSN_L9935 = 1;
    SPI_CSN_A39441 = 1;
    SPI_CSN_A39442 = 1;
   
}

//-----------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
//MAX6675调试完毕
UINT16 SPIReadWord(UINT8 id,UINT16 cmd) {
   UINT16 ret = 0;
   DisableInterrupts;
   switch(id) {
      case SPI_MAX6675:
        SPI_CSN_MAX6675 = 0;
        while(!SPI0SR_SPTEF);
        SPI0DR = cmd;
        while(SPI0SR_SPTEF); 
        while(!SPI0SR_SPIF);
        ret = SPI0DR;
        SPI_CSN_MAX6675 = 1;
      break; 
           
      case SPI_A39441:
        SPI_CSN_A39441 = 0;
        while(!SPI0SR_SPTEF);
        SPI0DR = cmd;
        while(SPI0SR_SPTEF);
        while(!SPI0SR_SPIF);
        ret = SPI0DR; 
        SPI_CSN_A39441 = 1;
      break;
      
      case SPI_A39442:
        SPI_CSN_A39442 = 0;
        while(!SPI0SR_SPTEF);
        SPI0DR = cmd;
        while(SPI0SR_SPTEF); 
        while(!SPI0SR_SPIF);
        ret = SPI0DR; 
        SPI_CSN_A39442 = 1;
      break;
      
      case SPI_CJ125:
        while(!SPI1SR_SPTEF);
        SPI1DR = cmd;    
        while(SPI1SR_SPTEF); 
        while(!SPI1SR_SPIF);
        ret = SPI1DR;
      break;
      
      case SPI_L9733:
        SPI2CR1_LSBFE = 1;
        SPI2CR2_XFRW = 1;  //转换成8位字宽
        SPI_CSN_L9733 = 0;   //芯片选择
        while(!SPI2SR_SPTEF);//等待空闲
        SPI2DRL = cmd;       //发数据
        while(SPI2SR_SPTEF);   //等待发送完毕
        while(SPI2SR_SPIF != 1);  //等待接收到数据
        ret = SPI2DR;          //返回数据
        SPI_CSN_L9733 = 1;     //芯片释放 
      break;
      
      case SPI_L9935:
        SPI2CR1_LSBFE = 0;
        SPI2CR2_XFRW = 0;  //转换成8位字宽
        SPI_CSN_L9935 = 0;   //芯片选择
        while(!SPI2SR_SPTEF);//等待空闲
        SPI2DRL = cmd & 0x00ff; //发数据
        while(SPI2SR_SPTEF);   //等待发送完毕
        while(SPI2SR_SPIF != 1);  //等待接收到数据
        ret = SPI2DRL;          //返回数据   ret = 0xff
        SPI_CSN_L9935 = 1;     //芯片释放
      break;

   }
   EnableInterrupts;
   return ret;
}


 


    
   