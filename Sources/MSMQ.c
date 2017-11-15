//-------------------------------------------------------------------------*
//文件名: MSMQ.c 					                             	                 *
//说  明: 串口数据处理											                               *
//初始时间：  2017年08月29日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#include "MSMQ.h"
#include "MsgQueue.h"
#include "SCI.h"

extern SYS_PARA sys_para;
#define G_HVInjWide sys_para.item.CylinInj_var.un16Inj_HV_Time
#define G_LVInjWide sys_para.item.CylinInj_var.un16Inj_LV_Time
#define G_GapInjWide sys_para.item.CylinInj_var.un16Inj_Gap_Time
extern uint8 DataSuccess_Flag;
T_SciMsg ReadMsg;
extern Queue MsgLine;

void MSSCIProcess(void){
     
     if(DeQueue(&ReadMsg,&MsgLine)){
        switch(ReadMsg.data[0])               //解析数据
        {
          case 'H':
              G_HVInjWide = ((ReadMsg.data[2] << 8) | ReadMsg.data[1]); //低8位 
              SCI_SendDec16u(G_HVInjWide);
              SCI_send('\n');
              break;
          case 'G':
              G_GapInjWide = (ReadMsg.data[2] << 8) | ReadMsg.data[1]; //低8位 
              SCI_SendDec16u(G_GapInjWide);
              SCI_send('\n');
              break;
          case 'L':
              G_LVInjWide = (ReadMsg.data[2] << 8) | ReadMsg.data[1]; //低8位 
              SCI_SendDec16u(G_LVInjWide);
              SCI_send('\n');
              break;   
          default:
              break;     
        }
     }
     
}