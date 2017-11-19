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

UINT8 Igtips[]="fire success";
UINT8 Closetips[]="stop working";

extern SYS_PARA sys_para;
#define G_un16IgSignal     sys_para.item.mem_var.un16IgSignal      //3����ź�
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
          case 'O':
              //G_HVInjWide = ((ReadMsg.data[2] << 8) | ReadMsg.data[1]); //��8λ 
              G_un16IgSignal = ON;
              send_string(Igtips);
              SCI_send('\n');
              break;
          case 'C':
              //G_GapInjWide = (ReadMsg.data[2] << 8) | ReadMsg.data[1]; //��8λ 
              send_string(Closetips);
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