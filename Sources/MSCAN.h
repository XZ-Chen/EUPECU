//-------------------------------------------------------------------------*
//文件名: MSCAN.h 					                             	                 *
//说  明: CAN总线驱动头文件											                           *
//初始时间：  2012年07月20日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#ifndef _MSCAN_H_
#define _MSCAN_H_
//1 头文件 
#include "typedefine.h"           //类型别名定义
#include <hidef.h> 
#include <MC9S12XET256.h>     /* derivative information */
#include "SysTask.h"

//2 宏定义

#define   MAX_LEN 8     // Max Data Frame

/////////////////////////////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct _can_msg 
{
    unsigned int id;
    Bool RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;
}can_msg;



/////////////////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////////////////
void MSCANInit(void);
Bool MSCANSendMsg(can_msg msg);
Bool MSCANGetMsg(can_msg *pmsg);
Bool MSCANCheckRcvdMsg(void);
void MSCANProcess(void); 

#endif