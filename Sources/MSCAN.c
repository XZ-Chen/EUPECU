//-------------------------------------------------------------------------*
//文件名: MSCAN.c 					                             	                 *
//说  明: MACAN驱动文件											                               *
//初始时间：  2012年07月20日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#include "MSCAN.h"

extern SYS_PARA sys_para;
#define AddrSysParaBgn  sys_para.data
//-------------------------------------------------------------------------*
//函数名: CAN_Init                                                  	     *
//功  能: 初始化CAN模块                                                    * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
void MSCANInit(void){
    MODRR_MODRR0 = 0;   //确保CAN0 对应PM0 PM1
    MODRR_MODRR1 = 0;
    CAN0CTL1_CANE = 1; 
    CAN0CTL0_INITRQ = 1;
    while(CAN0CTL1_INITAK == 0);
    CAN0IDAC = 0x20;
    CAN0IDMR0 = 0xff;
    CAN0IDMR1 = 0xff;
    CAN0IDMR2 = 0xff;
    CAN0IDMR3 = 0xff;
    CAN0IDMR4 = 0xff;
    CAN0IDMR5 = 0xff;
    CAN0IDMR6 = 0xff;
    CAN0IDMR7 = 0xff;
    //配置时钟
    //同步跳转宽度为1,预分频因子为6。将位速率设置成 100kbps
    //bit.7-6=01，同步跳转宽度为2，bit.5-0=000101,预分频因子为6
    //CAN0BTR0 = 0x03;      //6M晶振预分频值6  4M晶振预分频值4
    CAN0BTR0 = 0x03;      //1个同步跳转宽度 6M晶振预分频值6  4M晶振预分频值4
    //bit.7=0，单次采样，bit.6-4=010,时间段2为3；bit.3-0=0101,
    //时间段1为6，0b00100101，故位速率=1M/10=100kbps  625kbps
    CAN0BTR1 = 0x25;
    CAN0CTL1_CLKSRC = 0;  //采用外部晶振时钟 4M
    //CAN0CTL1_CLKSRC = 1;  //采用总线时钟 40M
    CAN0CTL1_LISTEN = 0;  //侦听模式禁止
    CAN0CTL1_LOOPB = 0;   //关闭自环测试模式

    CAN0CTL0_INITRQ = 0;
    while(CAN0CTL1_INITAK == 1);
    while(!CAN0CTL0_SYNCH);
    CAN0RIER_RXFIE = 0;     //允许中断     
}

//-------------------------------------------------------------------------*
//函数名: CAN_TX                                                     	     *
//功  能: 初始化CAN发送模块                                                * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*

Bool MSCANSendMsg(can_msg msg)
{
    unsigned char n_tx_buf, i;
    
    // 检查数据长度
    if(msg.len > MAX_LEN)
      return(FALSE);

    // 检查同步状态
    if(!(CAN0CTL0&0x10))
      return(FALSE);

    n_tx_buf = 0;
    do
    {
      // 寻找空闲发送缓冲器
      CAN0TBSEL=CAN0TFLG;
      n_tx_buf=CAN0TBSEL;
    }while(!n_tx_buf); 
    
    // 写ID号
    CAN0TXIDR0 = (unsigned char)(msg.id>>3);
    CAN0TXIDR1 = (unsigned char)(msg.id<<5);     
    // 写数据
    for(i = 0; i < msg.len; i++)
      *((&CAN0TXDSR0)+i) = msg.data[i];
      
    //写数据长度
    CAN0TXDLR = msg.len; 
    
    // 优先级
    CAN0TXTBPR = msg.prty;
    
    //清发送标志，准备好发送
    CAN0TFLG = n_tx_buf;
    
    return(TRUE);
}
/////////////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------------------------
// MSCAN 接收数据
/////////////////////////////////////////////////////////////////////////////////////////
Bool MSCANGetMsg(can_msg *pmsg)
{
  
  unsigned char i;

  // 检查是否收到消息
  if(!(CAN0RFLG&0x01))
    return(FALSE);
  
  
  if(CAN0RXIDR1&0x08)
 
    return(FALSE);

  // 读取ID号
  pmsg->id = (unsigned int)(CAN0RXIDR0<<3) | 
            (unsigned char)(CAN0RXIDR1>>5);
  
  if(CAN0RXIDR1&0x10)   //读取远程帧标志
    pmsg->RTR = TRUE;
  else
    pmsg->RTR = FALSE;
  
  // 读数据长度
  pmsg->len = CAN0RXDLR;
  
  //  读数据
  for(i = 0; i < pmsg->len; i++)
    pmsg->data[i] = *((&CAN0RXDSR0)+i);

  // 清接收标志，准备好接收
  CAN0RFLG = 0x01;
  
  return(TRUE);
    
}

/////////////////////////////////////////////////////////////////////////////////////////
// MSCANCheckRcvdMsg
/////////////////////////////////////////////////////////////////////////////////////////
Bool MSCANCheckRcvdMsg(void)
{

  //查询接收到数据
  if(CAN0RFLG&0x01)
    return(TRUE);
  else return(FALSE);
  
}

////////////////////////////////////////////////////////////////////////////////
extern uint8  PedalSaveFlag;
extern uint8  PeadlSaveCount;
void MSCANMsgProcess(can_msg msg) {
   
   if(msg.id != 1)
      return;
   if(msg.len != 5)
      return;
   if(msg.data[0] != 0 && msg.data[0]!= 1)
      return;      
   if(msg.data[0] == 1){
      *(AddrSysParaBgn + msg.data[1]) =  (msg.data[3] << 8) | msg.data[2]; //低8位 
      /*if(0x2e ==msg.data[1])
      {
           PedalSaveFlag=1;
      }      */
   }      
   msg.data[2] = *(AddrSysParaBgn + msg.data[1])&0x00ff; //低8位
   msg.data[3] = *(AddrSysParaBgn + msg.data[1])>>8;     //高8位
   msg.data[4] = msg.data[0] + msg.data[1] + msg.data[2] + msg.data[3]; 
   MSCANSendMsg(msg); 
}

/////////////////////////////////////////////////////////////////////////////////
can_msg msg;
void MSCANProcess(void){
   if(MSCANCheckRcvdMsg()) {
       if(MSCANGetMsg(&msg)) 
       {
           MSCANMsgProcess(msg);
       }
   }
}