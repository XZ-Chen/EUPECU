//-------------------------------------------------------------------------*
//文件名: SysTask.c                                                    	   *
//说  明: 系统任务文件                                          		       *
//初始时间：  2012年10月20日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "SysTask.h"
//#include "MAP.h"
#include "Includes.h"
#include "DFlashModule.h"

SYS_PARA sys_para;

#define G_InjEnable        sys_para.item.un16InjEnable                           
#define G_SysParaBgn       sys_para.data
#define G_un16SysMode      sys_para.item.mem_var.un16SysMode       //0系统主模式
#define G_un16DuralMode    sys_para.item.mem_var.un16DuralMode     //1双燃料模式
#define G_un16InjWide      sys_para.item.mem_var.un16InjWide       //2喷射时间
#define G_un16IgSignal     sys_para.item.mem_var.un16IgSignal      //3点火信号
#define G_un16SingleMode   sys_para.item.mem_var.un16bSingleMode

#define G_un16Pedal        sys_para.item.mem_var.un16Pedal         //4
#define G_bSensorScan      sys_para.item.mem_var.bSensorScan       //
#define G_bIOScan          sys_para.item.mem_var.bIOScan           //
#define G_bModeJudge       sys_para.item.mem_var.bModeJudge        //
#define G_bOutput          sys_para.item.mem_var.bOutput           //
#define G_bOilAngle        sys_para.item.CylinInj_var.bOilAngle
#define G_SensorAddrBgn    sys_para.item.un16Sensor                //
#define G_un16RPM          sys_para.item.un16Sensor[0]             //转速AD值
#define G_un16PedalPosAD   sys_para.item.un16Sensor[1]             //油门位置AD值
#define G_un16BatteryVolAD sys_para.item.un16Sensor[2]             //步进电机位置AD值
#define G_un16CoolWaterTemp  sys_para.item.un16Sensor[3]          //
#define G_un16InjCurAD     sys_para.item.un16Sensor[4]
#define G_DIAddrBgn        sys_para.item.un16DI                 //
#define G_DIIGSwitch       sys_para.item.un16DI[0]              //
#define G_DILNGSwitch      sys_para.item.un16DI[1]              //
#define G_DILNGSwitch      sys_para.item.un16DI[1]
#define G_DOLNGRVRelay     sys_para.item.un16DO[0]       //LNG减压阀
#define G_DOMainRelay      sys_para.item.un16DO[1]       //主继电器

#define G_un16HighSpeed    sys_para.item.const_var.un16HighSpeed  //
#define G_un16HSK1         sys_para.item.const_var.un16HSK1       //
#define G_un16LSK2         sys_para.item.const_var.un16LSK2       //
#define G_un16StpP1        sys_para.item.const_var.un16StpP1      //
#define G_un16StpP2        sys_para.item.const_var.un16StpP2      //

#define G_PedalAdBgn       sys_para.item.un16PedalAd

#define G_STLowStp     sys_para.item.StartCondition_var.LowStp //
#define G_STHiStp      sys_para.item.StartCondition_var.HiStp //
#define G_STOilStp     sys_para.item.StartCondition_var.OilStp //
#define G_STHiStCount  sys_para.item.StartCondition_var.HiStCount //
#define G_STPaTiSt     sys_para.item.StartCondition_var.PaTiSt //


////////////////////////////////////////////////////////
//全局变量初始化                                      //
////////////////////////////////////////////////////////
void SysVarInit(void)
{
    uint8 i;
    for(i=0;i<255;i++) {
       *(G_SysParaBgn + i) = 0;
    }
    //for test/////////////////////////////////
           //尝试给不同的值
    G_un16HSK1 = LNG_HSK1;
    G_un16LSK2 = LNG_LSK2;
    G_un16StpP1 = STEPPER_P1;
    G_un16StpP2 = STEPPER_P2;
    G_un16HighSpeed = LNG_HIGHSPEED;
    G_un16InjWide = 0;
    //for test/////////////////////////////////
    G_STOilStp = 0;
    G_InjEnable = OFF;
    G_STHiStCount = 0;
    G_STHiStp = 600;
    G_STLowStp = 100; //最低启动转速
    G_InjEnable = OFF;
    G_un16IgSignal = OFF;
    G_un16SysMode = SYS_SINGLE;
    G_un16DuralMode = DURAL_MODE_STOP;
    G_DOLNGRVRelay = OFF;
    G_DOMainRelay = OFF;
    G_bSensorScan = FALSE;
    G_bIOScan = FALSE;
    G_bModeJudge = FALSE;
    G_bOutput = FALSE;    
    MainRelayOff();
    LNGRVRelayOff();
    //InjectorOff();  
}

///////////////////////////////////////////////////////
//单燃料模式处理                                     //
///////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//初始化完毕，进入待机模式                            //
//待机模式处理                                        //
//当IG点火开关关闭                                    //
//1.延时2s关闭主继电器                                //
//2.主继电器关闭后，步进电机回起始位置                //
//3.步进电机到位后，LNG减压阀门打开，2S后关闭         //
////////////////////////////////////////////////////////
void SysSingleProcess(void){
   
   static uint16 nTicks = 0;
   static uint16 nSeq = 0;
   SingleModeJudge();
   SingleAppExcute();
/*   if(G_DILNGSwitch != ON)
   {
       nSeq = 0;
       if(G_DOLNGRVRelay == ON) 
       {
           nTicks ++;
           if(nTicks == 10) 
           {  
              G_DOLNGRVRelay = OFF;
              nTicks = 0;
           }
       }
       if(G_un16InjWide != 0)
           G_un16InjWide = 0;
       return;
   }
   if(nSeq == 0)   //10*0.2s = 2s    继电器闭合
   { 
      nTicks++;
      if(nTicks == 10) 
      {   
        G_DOMainRelay = ON;
        nSeq = 1;
        nTicks = 0; 
      }
   } 
   else if(nSeq == 1) 
   {
      G_DOLNGRVRelay = ON;
      nTicks = 0;
      nSeq = 2;
   }
   else if(nSeq == 2) 
   {
      nTicks++;
      if(nTicks == 10) 
      { //200ms*10 = 2s
        nTicks = 0;
        nSeq = 0;
        G_DOLNGRVRelay = OFF;
        G_un16SysMode = SYS_DURAL;
      }
   }  */
}


///////////////////////////////////////////////////////
//双燃料模式处理                                     //
///////////////////////////////////////////////////////
void SysDuralProcess(void) 
{
   DuralModeJudge();
   DuralAppExcute();
}
///////////////////////////////////////////////////////
//系统出错模式处理                                   //
///////////////////////////////////////////////////////
void SysErrProcess(void) 
{
  
}

//////////////////////////////////////////////////////
//执行器输出处理                                    //
//////////////////////////////////////////////////////
void SysOutputProcess(void)
{
   static uint16 nInjWidePre = 1;
   static uint16 nCycle;
   uint32 nTemp; 
   if(G_DOMainRelay == ON)    
      MainRelayOn();
   else {
      MainRelayOff();
      return;
   }
   if(G_DOLNGRVRelay == ON)
      LNGRVRelayOn();
   else
      LNGRVRelayOff();
   if(G_un16InjWide != nInjWidePre){ 
      if(G_un16InjWide != 0) {
        // nTemp = 120000000/G_un16RPM/CRANK_CYLINDER_NUM;
         nTemp = 20000;
         nCycle = nTemp&0xffff;
      }
      else
         nCycle = 0;
      //InjectorWide(nCycle,G_un16InjWide);
      nInjWidePre = G_un16InjWide;
   }
}
///////////////////////////////////////////////////////
//系统主模式处理                                     //
///////////////////////////////////////////////////////

void SysTaskProcess(void)
{
    if(G_bOilAngle)
    {
      OilAngle();
      G_bOilAngle = FALSE;
    }
    if(G_bIOScan){ 
      DIScan(G_DIAddrBgn);       //输入扫描  点火开关 LNG高压阀开关
      G_bIOScan = FALSE;
    }
    if(G_bSensorScan){
      SensorScan(G_SensorAddrBgn);   //传感器扫描    
      //CheckSave();
      //PedalRead(G_PedalAdBgn);   //标定read flash功能
      SensorProcess(G_SensorAddrBgn);
      G_bSensorScan = FALSE;
    }
    if(G_bModeJudge) 
    {  
      switch(G_un16SysMode) {
        case SYS_SINGLE:
          SysSingleProcess();    //单燃料模式处理          
          break;
        case SYS_DURAL:
          SysDuralProcess();     //双燃料模式处理
          break;                 
        case SYS_ERR:
          SysErrProcess();
          break;  
    }
    G_bModeJudge = FALSE;
    }
    if(G_bOutput) { 
      SysOutputProcess();
      G_bOutput = FALSE;
    }
}
///////////////////////////////////////////////////////
//系统故障模式处理                                   //
///////////////////////////////////////////////////////
void SysDigProcess(void)
{
    
}
///////////////////////////////////////////////////////
//系统单燃料模式判别                               //
///////////////////////////////////////////////////////
void SingleModeJudge(void)
{
	if(G_DILNGSwitch == ON) { //确保双燃料开关关闭
	   G_un16SysMode = SYS_DURAL;
	   return;
	}
	
	if(G_un16IgSignal == ON)   //如果收到点火信号 调试阶段由串口接收 后续由IO中断发生
  {
		G_un16IgSignal = OFF;
		G_un16DuralMode = SINGLE_MODE_IDLE; //进入启动工况
		return;
  }

}
///////////////////////////////////////////////////////
//怠速工况处理函数		
/*#define G_STLowStp     //
#define G_STHiStp        //
#define G_STOilStp      //
#define G_STHiStCount   //
#define G_STPaTiSt	                                 // */
///////////////////////////////////////////////////////
void StartCondition(void)
{
	if(G_un16RPM < G_STLowStp)  //如果当前转速低于最低启动转速
	{
		G_un16SingleMode = SINGLE_MODE_STOP;   //工况转为停止工况
	}
	else
	{
		if(G_un16RPM > G_STHiStp)
		{
			G_STHiStCount++;
			if(G_STHiStCount > G_STPaTiSt)
			    G_un16SingleMode = SINGLE_MODE_IDLE; //转速提高 启动成功进入怠速工况
			else
			    StartCondition_Sub();  //如果没有进入启动控制策略
		}
  	else 
	  {
  	  	G_STHiStCount = 0;
  	  	StartCondition_Sub();
	  }
	}
}

    	      
///////////////////////////////////////////////////////
//系统双燃料模式处理                                 //
///////////////////////////////////////////////////////

void DuralModeJudge(void)
{

	static uint16 nPedalADPre = PEDAL_AD_MIN; //for test  PEDAL_AD_MIN = 25
	uint16 nPedalRatio = 0;
	if(G_DILNGSwitch == OFF) {
	   G_un16SysMode = SYS_SINGLE;
	   return;
	}
  G_un16DuralMode = DURAL_MODE_STOP; //    DURAL_MODE_STOP = 0
  //G_un16Pedal = look1D_U16_U16(G_un16PedalPosAD,un16TabPedalAD,10,un16TabPedalPercent);  //查找油门踏板MAP	
  nPedalRatio = 1000 + 2*G_un16PedalPosAD - 2*nPedalADPre;  
  //********************超速工况****************************//
  if(G_un16RPM>2800)  
	{
			//转速>2800rpm
			G_un16DuralMode = DURAL_MODE_SPEEDLIMIT;    //  DURAL_MODE_SPEEDLIMIT = 6
			goto RETURN;
	}
	//****************急加速工况**************// 
  if(nPedalRatio > PEDAL_RATIO_MAX &&G_un16RPM >= 750)  //  PEDAL_RATIO_MAX=1200 
	{		
		 G_un16DuralMode = DURAL_MODE_OVERACC;   //  DURAL_MODE_OVERACC = 4
	   goto RETURN;
	}
	//****************急减速工况**************//
  if(nPedalRatio < PEDAL_RATIO_MIN && G_un16RPM >= 750)     //PEDAL_RATIO_MIN=900 
	{
		 G_un16DuralMode = DURAL_MODE_OVERDEC;		
		 goto RETURN;
  }
  //*****************正常行驶工况***************************//
  if(G_un16Pedal>=10 && G_un16RPM >=1100)   //
  {
	   G_un16DuralMode = DURAL_MODE_NORMAL;   //DURAL_MODE_NORMAL = 3
	}
  RETURN:
  nPedalADPre = G_un16PedalPosAD;     // 油门位置赋新值
}
///////////////////////////////////////////////////////
//系统单燃料执行器输出处理                           //
///////////////////////////////////////////////////////
void SingleAppExcute(void)
{
 	switch(G_un16SingleMode)
	{
		case SINGLE_MODE_START:
			StartCondition();
			break;
	
		case SINGLE_MODE_NORMAL:
			//NormalCtrl();
			break;
		case SINGLE_MODE_SPEEDLIMIT:
			//SpeedLimitCtrl();
			break;
		case SINGLE_MODE_OVERACC:
			//OverAccCtrl();
			break;
		case SINGLE_MODE_OVERDEC:
			//OverDecCtrl();
			break;
	}
}
///////////////////////////////////////////////////////
//系统双燃料执行器输出处理                           //
///////////////////////////////////////////////////////
void DuralAppExcute(void){
  
	switch(G_un16DuralMode)
	{
		case DURAL_MODE_STOP:
			EngineStopCtrl();
			break;
		case DURAL_MODE_NORMAL:
			NormalCtrl();
			break;
		case DURAL_MODE_SPEEDLIMIT:
			SpeedLimitCtrl();
			break;
		case DURAL_MODE_OVERACC:
			OverAccCtrl();
			break;
		case DURAL_MODE_OVERDEC:
			OverDecCtrl();
			break;
	}
}
/*************************************************************/
/*                      双燃料普通模式                       */
/*************************************************************/
void NormalCtrl()
{
  uint32 nTemp;
  G_DOLNGRVRelay = ON;
	//***************查询map*******************************//
	//G_un16InjWide = look2D_U16_U16_U16(G_un16RPM,G_un16Pedal, \
						        	//u16TabSpeedX, 19,\
							        //u16TabPedalY, 14,u16TabInjWidth);
	//***************喷射阀脉宽计算*******************//
	if (G_un16RPM >= G_un16HighSpeed)	
	{
			nTemp = (uint32)G_un16InjWide*(uint32)G_un16HSK1;
			nTemp = nTemp/100;
			G_un16InjWide = nTemp&0xffff;
			
	}
	else
	{
	   	nTemp = (uint32)G_un16InjWide*(uint32)G_un16LSK2;
			nTemp = nTemp/100;
			G_un16InjWide = nTemp&0xffff;
	}
}
/*************************************************************/
/*                      双燃料速度限制模式                   */
/*************************************************************/
void SpeedLimitCtrl()
{
	 
   if(G_un16InjWide != 0)
       G_un16InjWide = 0;
   
   G_DOLNGRVRelay = OFF;
}
/*************************************************************/
/*                      双燃料急加速控制模式                 */
/*************************************************************/
void OverAccCtrl()
{
    G_DOLNGRVRelay = ON;
  /*  G_un16InjWide = look2D_U16_U16_U16(G_un16RPM,G_un16Pedal, \
						        	u16TabSpeedX, 19,\
							        u16TabPedalY, 14,u16TabInjWidth);  */
}
/*************************************************************/
/*                      双燃料急减速模式                     */
/*************************************************************/
void OverDecCtrl()
{   
    G_DOLNGRVRelay = ON;
    //G_un16InjWide = 1500;
}
/*************************************************************/
/*                      发动机停止模式                       */
/*************************************************************/
void EngineStopCtrl()
{
   if(G_un16InjWide != 0)
       G_un16InjWide = 0;
   G_DOLNGRVRelay = OFF;
}

/*************************************************************/
/*                      读取MAP                              */
/*************************************************************/  
void PedalRead(uint16 *pSensor) {
    uint8 i;
    //CopyPedalMap();
    for(i=0;i<11;i++)
	    *(pSensor+i) = *(G_PedalAdBgn+i);
}
extern uint16 un16TabPedalAD[11]; 
void CopyPedalMap(void) {
    uint8 i,flag;
    flag = checkFlashStatus();
    if(flag) {
      ReadFromFlash();
      for(i=0;i<11;i++)
	      *(G_PedalAdBgn+i) = un16TabPedalAD[i];
    } else{
      //for(i=0;i<11;i++)
	     // *(G_PedalAdBgn+i) = un16TabPedalAD[i];
    } 
}



