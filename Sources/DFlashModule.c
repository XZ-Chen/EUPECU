//-------------------------------------------------------------------------*
//文件名: DFlashModule.c 					                             	                   *
//说  明: flash写入  								                         *
//初始时间：  2017年2月17日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#include "DataFlash.h"
#include "DFlashModule.h"

uint16          Buffer_Pedal[11];
uint16          MapData_read[11];
unsigned int    data_read[11];
extern uint16 un16TabPedalAD[11];
uint8           PedalSaveFlag=0;
uint8           PeadlSaveCount=0;
extern uint16 un16TabPedalADTest[11];
uint16  data_Address=0x0000;

static FlashPara A_FlashPara;
extern SYS_PARA sys_para;
/*************************************************************/
/*                   将数据写入FLASH                     */
/*************************************************************/
void WriteToFlash(void){
  
  //MapToBuffer(Buffer_Pedal);           
  DFlashErase(data_Address);     //确保先擦除后写入
  DFlashWrite(data_Address);  
}
 


/*************************************************************/
/*                   判断Flash是否未被写入                   */
/*************************************************************/
void JudgeFlashStatus(void) {
      int i; 
       //WriteToFlash();
       data_read[0]=DFlashRead(data_Address); 
       data_read[1]=DFlashRead(data_Address+2); 
       data_read[2]=DFlashRead(data_Address+4); 
       data_read[3]=DFlashRead(data_Address+6);

    	if(data_read[0]==0xffff || data_read[1]==0xffff || data_read[2]==0xffff || data_read[3]==0xffff)
    	{	
    		A_FlashPara.WritedFlag = FALSE; //未被写入
    		//WriteToFlash();
    	}
    	else
    	{
    		A_FlashPara.WritedFlag = TRUE;  //已被写入
    		ReadFromFlash();   //已被写入 从flash中读出数据
    		//WriteToFlash();		
    	}
     for(i=0;i<11;i++)
	      *(sys_para.item.un16PedalAd+i) = un16TabPedalAD[i];
}


/*************************************************************/
/*                   判断Flash是否有内容读出             */
/*************************************************************/
void ReadFromFlash(void) {
    uint i;
    MapData_read[0]=DFlashRead(data_Address); 
    MapData_read[1]=DFlashRead(data_Address+2); 
    MapData_read[2]=DFlashRead(data_Address+4); 
    MapData_read[3]=DFlashRead(data_Address+6);
    MapData_read[4]=DFlashRead(data_Address+8); 
    MapData_read[5]=DFlashRead(data_Address+10); 
    MapData_read[6]=DFlashRead(data_Address+12); 
    MapData_read[7]=DFlashRead(data_Address+14);
    MapData_read[8]=DFlashRead(data_Address+16); 
    MapData_read[9]=DFlashRead(data_Address+18); 
    MapData_read[10]=DFlashRead(data_Address+20);
    for(i=0;i<11;i++)
	  {  
	    un16TabPedalAD[i] = MapData_read[i];
	   
    }
}
/*************************************************************/
/*                    判断是否有保存动作                     */
/*************************************************************/
void CheckSave(void) 
{
    int i;
    for(i=0;i<11;i++) 
    {
        if(un16TabPedalAD[i] != *(sys_para.item.un16PedalAd+i)) 
        {          
            PedalSaveFlag = 1;
        }
    }
    if(PedalSaveFlag) 
    {
        PedalSaveFlag = 0;
        for(i=0;i<11;i++) {
        
	        Buffer_Pedal[i] = *(sys_para.item.un16PedalAd+i);
	        un16TabPedalAD[i] = *(sys_para.item.un16PedalAd+i);
       }
        WriteToFlash();     
    }
}


