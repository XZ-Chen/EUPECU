//-------------------------------------------------------------------------*
//文件名: DataFlash.c                                                      *
//说  明: DataFlash程序文件                                         		     *
//初始时间：  2012年10月02日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*

#include "DataFlash.h"
#include "MSCAN.h"
//-------------------------------------------------------------------------* 
//函数名: DFlashInit                                                         *
//功  能: DFlash初始化                                                        *
//参  数：无                                                               * 
//返  回: 无                                                               * 
//说  明: 无                                                               *
//-------------------------------------------------------------------------*  
//这个模块经过测试，大致没什么问题

uint16  Buffer[]={0x1111,0x2222,0x3333,0x4444};//数据缓存区，只能一次写入四个数据

uint16  date_read[4];


          
/*************************************************************/
/*                      初始化DFLASH                         */
/*************************************************************/
void DFlashInit(void)
{
   while(FSTAT_CCIF==0);            //等待正在处理的FLASH操作完成
  // FCLKDIV=0x0F;                    //外部晶振为16M.FLASH时钟不超过1M，具体参照手册
  // FCLKDIV=0x05;                    //外部晶振为6M.FLASH时钟不超过1M，具体参照手册
   FCLKDIV=0x03;                    //外部晶振为4M.FLASH时钟不超过1M，具体参照手册
   FCNFG=0x00;                      //禁止中断
   while(FCLKDIV_FDIVLD==0);        //等待时钟设置成功
}

/*************************************************************/
/*                     向DFLASH写入数据                      */
/*************************************************************/
//每次允许4个word，即8个字节一次性写入
extern  uint16    Buffer_Pedal[11];
void DFlashWrite(word ADDR16)
{
    while(FSTAT_CCIF==0); 
    if(FSTAT_ACCERR)           //判断并清除标志位；
        FSTAT_ACCERR=1;
    if(FSTAT_FPVIOL)           //判断并清除标志位；
        FSTAT_FPVIOL=1;
    FCCOBIX_CCOBIX=0x00; 
    FCCOB=0x1110;         //写入命令和高位地址
    FCCOBIX_CCOBIX=0x01;  //地址后16位
    FCCOB=ADDR16;         //写入低16位地址
    FCCOBIX_CCOBIX=0x02;  //写入第一个数据
    FCCOB=Buffer_Pedal[0];
    FCCOBIX_CCOBIX=0x03;  //写入第二个数据
    FCCOB=Buffer_Pedal[1];
    FCCOBIX_CCOBIX=0x04;  //写入第三个数据
    FCCOB=Buffer_Pedal[2];
    FCCOBIX_CCOBIX=0x05;  //写入第四个数据
    FCCOB=Buffer_Pedal[3];  
    FSTAT_CCIF=1;         //写入执行命令
    while(FSTAT_CCIF==0); //等待执行完毕 
     
    if(FSTAT_ACCERR)           //判断并清除标志位；
        FSTAT_ACCERR=1;
    if(FSTAT_FPVIOL)           //判断并清除标志位；
        FSTAT_FPVIOL=1;
    FCCOBIX_CCOBIX=0x00; 
    FCCOB=0x1110;         //写入命令和高位地址
    FCCOBIX_CCOBIX=0x01;  //地址后16位
    FCCOB=0x0008;         //写入低16位地址
    FCCOBIX_CCOBIX=0x02;  //写入第一个数据
    FCCOB=Buffer_Pedal[4];
    FCCOBIX_CCOBIX=0x03;  //写入第二个数据
    FCCOB=Buffer_Pedal[5];
    FCCOBIX_CCOBIX=0x04;  //写入第三个数据
    FCCOB=Buffer_Pedal[6];
    FCCOBIX_CCOBIX=0x05;  //写入第四个数据
    FCCOB=Buffer_Pedal[7];     
    FSTAT_CCIF=1;         //写入执行命令
    while(FSTAT_CCIF==0); //等待执行完毕
    
    if(FSTAT_ACCERR)           //判断并清除标志位；
        FSTAT_ACCERR=1;
    if(FSTAT_FPVIOL)           //判断并清除标志位；
        FSTAT_FPVIOL=1;
    FCCOBIX_CCOBIX=0x00; 
    FCCOB=0x1110;         //写入命令和高位地址
    FCCOBIX_CCOBIX=0x01;  //地址后16位
    FCCOB=0x0010;         //写入低16位地址
    FCCOBIX_CCOBIX=0x02;  //写入第一个数据
    FCCOB=Buffer_Pedal[8];
    FCCOBIX_CCOBIX=0x03;  //写入第二个数据
    FCCOB=Buffer_Pedal[9];
    FCCOBIX_CCOBIX=0x04;  //写入第三个数据
    FCCOB=Buffer_Pedal[10];   
    FSTAT_CCIF=1;         //写入执行命令
    while(FSTAT_CCIF==0); //等待执行完毕
}
extern can_msg msg;

void MapWTFlash(word ADDR16)
{
    while(FSTAT_CCIF==0); 
    if(FSTAT_ACCERR)           //判断并清除标志位；
        FSTAT_ACCERR=1;
    if(FSTAT_FPVIOL)           //判断并清除标志位；
        FSTAT_FPVIOL=1;
    FCCOBIX_CCOBIX=0x00; 
    FCCOB=0x1110;         //写入命令和高位地址
    FCCOBIX_CCOBIX=0x01;  //地址后16位
    FCCOB=ADDR16;         //写入低16位地址
    FCCOBIX_CCOBIX=0x02;  //写入第一个数据
    FCCOB=(msg.data[3] << 8) | msg.data[2];

    FSTAT_CCIF=1;         //写入执行命令
    while(FSTAT_CCIF==0); //等待执行完毕
}
/*************************************************************/
/*                     由DFLASH读取数据                      */
/*************************************************************/
word DFlashRead (word destination)
{
    byte   lastepage;          //用于存储EPAGE的值
    byte   epage;              //用于计算EPAGE的值
    unsigned int data;         //读取出的数据

    lastepage = EPAGE;   //保存EPAGE的值

    epage = (byte)((DFLASH_LOWEST_START_PAGE)+(destination >>10));   //计算EPAGE
    EPAGE=epage;                                                     //给EPAGE赋值
 
    data = READword((destination & (DFLASH_PAGE_SIZE - 1)) + DFLASH_PAGE_WINDOW_START);  //读取页面窗口中的数据

    EPAGE= lastepage;       //恢复EPAGE的值

    return(data);
}

/*************************************************************/
/*                    擦除DFLASH的一个分区                   */
/*************************************************************/
void DFlashErase(word ADDR16)
{   
  while(FSTAT_CCIF==0);
  if(FSTAT_ACCERR)           //判断并清除标志位；
      FSTAT_ACCERR=1;
  if(FSTAT_FPVIOL)           //判断并清除标志位；
      FSTAT_FPVIOL=1;
  
  FCCOBIX_CCOBIX=0x00;
  FCCOB=0x1210;           //写入擦除命令和高位地址
  FCCOBIX_CCOBIX=0x01;   
  FCCOB=ADDR16;           //写入低16位的地址
  FSTAT_CCIF=1;           //启动执行命令
  while(FSTAT_CCIF==0);   //等待执行完成
}


