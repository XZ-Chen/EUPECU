//-------------------------------------------------------------------------*
//文件名: DataFlash.h                                                      *
//说  明: DataFlash头文件                                         		     *
//初始时间：  2012年10月02日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _DATAFLASH_H
#define _DATAFLASH_H

//1 头文件
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 

#define READword(address)     ((unsigned int)(*(volatile unsigned int *__near)(address)))
                                                                       
#define DFLASH_LOWEST_START_PAGE        0x00        //定义data flash的起始页
#define DFLASH_START                    0x00100000  //定义data flash的起始地址
#define DFLASH_PAGE_SIZE                0x0400      //定义data flash的大小为1K.
#define DFLASH_PAGE_WINDOW_START        0x0800      //定义data flash页面窗口的起始地址
#define LEDCPU PORTB_PB0
#define LEDCPU_dir DDRB_DDRB0

void DFlashInit(void);
word DFlashRead (word destination);
void DFlashErase(word ADDR16);

#endif