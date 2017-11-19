//-------------------------------------------------------------------------*
//文件名: SPI.h 					                             	                   *
//说  明: SPI串行通讯驱动头文件											                       *
//初始时间：  2012年07月12日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _SPI_H_           //防止重复定义
#define _SPI_H_

//1、头文件   
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 

#define SPI_MAX6675    1
#define SPI_A39441     2
#define SPI_A39442     3
#define SPI_CJ125      4
#define SPI_L9935      5
#define SPI_L9733      6


#define SPI_CSN_L9935      PORTE_PE7
#define SPI_CSN_L9733      PORTE_PE6
#define SPI_CSN_MAX6675    PORTE_PE5    //   SPI_CSN_A39441
#define SPI_CSN_A39442     PTS_PTS0
#define SPI_CSN_A39441     PTS_PTS7

#define SPI_CSN_L9935_DDR    DDRE_DDRE7
#define SPI_CSN_L9733_DDR    DDRE_DDRE6
#define SPI_CSN_MAX6675_DDR  DDRE_DDRE5  //  SPI_CSN_A39441_DDR
#define SPI_CSN_A39442_DDR   DDRS_DDRS0
#define SPI_CSN_A39441_DDR   DDRS_DDRS7



//2  宏定义


//-------------------------------------------------------------------------*
//函数名: SPIInit                                                  	       *
//功  能: 初始化SPI模块                                                    * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
void SPIInit(void);
    
//-----------------------------------------------------------------------*
//函数名: SPIReadWord                                                    *
 //功  能: 从SPI接收一个字节的数据                                       *
//参  数: 无                                                             *
//返  回: 接收到的数(若接收失败,返回0xff)                                *
//说  明: 无                                                             *
//-----------------------------------------------------------------------* 
UINT16 SPIReadWord(UINT8 id,UINT16 cmd);
#define SPIWriteWord(id,cmd) (SPIReadWord(id,cmd))
        
   

#endif



