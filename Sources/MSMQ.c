//-------------------------------------------------------------------------*
//�ļ���: MSMQ.c 					                             	                 *
//˵  ��: �������ݴ���											                               *
//��ʼʱ�䣺  2017��08��29��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XET256                         	                 *
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
        switch(ReadMsg.data[0])               //��������
        {
          case 'H':
              G_HVInjWide = ((ReadMsg.data[2] << 8) | ReadMsg.data[1]); //��8λ 
              SCI_SendDec16u(G_HVInjWide);
              SCI_send('\n');
              break;
          case 'G':
              G_GapInjWide = (ReadMsg.data[2] << 8) | ReadMsg.data[1]; //��8λ 
              SCI_SendDec16u(G_GapInjWide);
              SCI_send('\n');
              break;
          case 'L':
              G_LVInjWide = (ReadMsg.data[2] << 8) | ReadMsg.data[1]; //��8λ 
              SCI_SendDec16u(G_LVInjWide);
              SCI_send('\n');
              break;   
          default:
              break;     
        }
     }
     
}