//-------------------------------------------------------------------------*
//�ļ���: ECT.c                                                        	   *
//˵  ��: ��ǿ�Ͳ�׽��ʱ�������ļ�                                       		     *
//��ʼʱ�䣺  2016��3��24��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XET256               			                       *
//-------------------------------------------------------------------------*
#include "ECT.h"

//-------------------------------------------------------------------------* 
//������: ECTInit                                                          *
//��  ��: ECT��ʼ��                                                        *
//��  ������                                                               * 
//��  ��: ��                                                               * 
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*  
void ECTInit(void){
    //��ʱ��ģ����ƼĴ���1
    /*ECT_TSCR1 = 0b00000000;   
    ECT_TSCR2 = 0b00000100;   //TCNTƵ��40/16= 2.5mhz,ת�����3000����С600��������Ҫ��
    ECT_TIOS = 0b00000000;   
    ECT_TCTL1 = 0b00000000;   
    ECT_TCTL2 = 0b00000000;   
    ECT_TCTL3 = 0b00000000;    
    ECT_TCTL4 = 0b00000001;   
    ECT_TIE = 0b00000001;   
    ECT_TFLG1 = 0b00000001;   
    ECT_TFLG2 = 0b00000000;  */
    //ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
  ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=������ʱ����������; 0=ʹ����ʱ����������(����������)
  ECT_TIOS  = 0xf0;     // 1 2 3 4 IC    5 6 7 8 OC
  ECT_TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  ECT_TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  ECT_TCTL3 = 0b00000000;    
  ECT_TCTL4 = 0b00001010;//IC0 IC1ֻ ��׽�½���
  ECT_DLYCT = 0x00;	    // �ӳٿ��ƹ��ܽ�ֹ
  ECT_ICOVW = 0x00;	    // ��Ӧ�ļĴ�������������;  NOVWx = 1, ��Ӧ�ļĴ�������������
  ECT_ICSYS = 0x00;	    // ��ֹIC��PAC�ı��ּĴ���
  ECT_TIE   = 0x03;     // ��1��0�ж�  ��ʱ����6��7�����ж�
  ECT_TSCR2 = 0x14;	    // ������ʱ������ж� Ԥ��Ƶϵ��pr2-pr0:100,ʱ������Ϊ0.4us,ʹ�ܶ�ʱ������ж�
  ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
  ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ
}
/************************************************************/
/*                    ��ʼ��ECTģ��                         */
/************************************************************
void initialize_ect(void){
  //ECT_TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
  ECT_TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=������ʱ����������; 0=ʹ����ʱ����������(����������)
  ECT_TIOS  = 0xf0;     // 1 2 3 4 IC    5 6 7 8 OC
  ECT_TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  ECT_TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  ECT_TCTL3 = 0b00000000;    
  ECT_TCTL4 = 0b00000101;//IC0 IC1ֻ ��׽������
  ECT_DLYCT = 0x00;	    // �ӳٿ��ƹ��ܽ�ֹ
  ECT_ICOVW = 0x00;	    // ��Ӧ�ļĴ�������������;  NOVWx = 1, ��Ӧ�ļĴ�������������
  ECT_ICSYS = 0x00;	    // ��ֹIC��PAC�ı��ּĴ���
  ECT_TIE   = 0x43;     // ��6��0�ж�
  ECT_TSCR2 = 0x04;	    // Ԥ��Ƶϵ��pr2-pr0:100,ʱ������Ϊ0.4us,ʹ�ܶ�ʱ������ж�
  ECT_TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
  ECT_TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ
}                            */

