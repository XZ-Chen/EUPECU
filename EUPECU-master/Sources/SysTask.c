//-------------------------------------------------------------------------*
//�ļ���: SysTask.c                                                    	   *
//˵  ��: ϵͳ�����ļ�                                          		       *
//��ʼʱ�䣺  2012��10��20��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "SysTask.h"
//#include "MAP.h"
#include "Includes.h"
#include "DFlashModule.h"

SYS_PARA sys_para;

#define G_InjEnable        sys_para.item.un16InjEnable                           
#define G_SysParaBgn       sys_para.data
#define G_un16SysMode      sys_para.item.mem_var.un16SysMode       //0ϵͳ��ģʽ
#define G_un16DuralMode    sys_para.item.mem_var.un16DuralMode     //1˫ȼ��ģʽ
#define G_un16InjWide      sys_para.item.mem_var.un16InjWide       //2����ʱ��
#define G_un16IgSignal     sys_para.item.mem_var.un16IgSignal      //3����ź�
#define G_un16SingleMode   sys_para.item.mem_var.un16bSingleMode

#define G_un16Pedal        sys_para.item.mem_var.un16Pedal         //4
#define G_bSensorScan      sys_para.item.mem_var.bSensorScan       //
#define G_bIOScan          sys_para.item.mem_var.bIOScan           //
#define G_bModeJudge       sys_para.item.mem_var.bModeJudge        //
#define G_bOutput          sys_para.item.mem_var.bOutput           //
#define G_bOilAngle        sys_para.item.CylinInj_var.bOilAngle
#define G_SensorAddrBgn    sys_para.item.un16Sensor                //
#define G_un16RPM          sys_para.item.un16Sensor[0]             //ת��ADֵ
#define G_un16PedalPosAD   sys_para.item.un16Sensor[1]             //����λ��ADֵ
#define G_un16BatteryVolAD sys_para.item.un16Sensor[2]             //�������λ��ADֵ
#define G_un16CoolWaterTemp  sys_para.item.un16Sensor[3]          //
#define G_un16InjCurAD     sys_para.item.un16Sensor[4]
#define G_DIAddrBgn        sys_para.item.un16DI                 //
#define G_DIIGSwitch       sys_para.item.un16DI[0]              //
#define G_DILNGSwitch      sys_para.item.un16DI[1]              //
#define G_DILNGSwitch      sys_para.item.un16DI[1]
#define G_DOLNGRVRelay     sys_para.item.un16DO[0]       //LNG��ѹ��
#define G_DOMainRelay      sys_para.item.un16DO[1]       //���̵���

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
//ȫ�ֱ�����ʼ��                                      //
////////////////////////////////////////////////////////
void SysVarInit(void)
{
    uint8 i;
    for(i=0;i<255;i++) {
       *(G_SysParaBgn + i) = 0;
    }
    //for test/////////////////////////////////
           //���Ը���ͬ��ֵ
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
    G_STLowStp = 100; //�������ת��
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
//��ȼ��ģʽ����                                     //
///////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//��ʼ����ϣ��������ģʽ                            //
//����ģʽ����                                        //
//��IG��𿪹عر�                                    //
//1.��ʱ2s�ر����̵���                                //
//2.���̵����رպ󣬲����������ʼλ��                //
//3.���������λ��LNG��ѹ���Ŵ򿪣�2S��ر�         //
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
   if(nSeq == 0)   //10*0.2s = 2s    �̵����պ�
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
//˫ȼ��ģʽ����                                     //
///////////////////////////////////////////////////////
void SysDuralProcess(void) 
{
   DuralModeJudge();
   DuralAppExcute();
}
///////////////////////////////////////////////////////
//ϵͳ����ģʽ����                                   //
///////////////////////////////////////////////////////
void SysErrProcess(void) 
{
  
}

//////////////////////////////////////////////////////
//ִ�����������                                    //
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
//ϵͳ��ģʽ����                                     //
///////////////////////////////////////////////////////

void SysTaskProcess(void)
{
    if(G_bOilAngle)
    {
      OilAngle();
      G_bOilAngle = FALSE;
    }
    if(G_bIOScan){ 
      DIScan(G_DIAddrBgn);       //����ɨ��  ��𿪹� LNG��ѹ������
      G_bIOScan = FALSE;
    }
    if(G_bSensorScan){
      SensorScan(G_SensorAddrBgn);   //������ɨ��    
      //CheckSave();
      //PedalRead(G_PedalAdBgn);   //�궨read flash����
      SensorProcess(G_SensorAddrBgn);
      G_bSensorScan = FALSE;
    }
    if(G_bModeJudge) 
    {  
      switch(G_un16SysMode) {
        case SYS_SINGLE:
          SysSingleProcess();    //��ȼ��ģʽ����          
          break;
        case SYS_DURAL:
          SysDuralProcess();     //˫ȼ��ģʽ����
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
//ϵͳ����ģʽ����                                   //
///////////////////////////////////////////////////////
void SysDigProcess(void)
{
    
}
///////////////////////////////////////////////////////
//ϵͳ��ȼ��ģʽ�б�                               //
///////////////////////////////////////////////////////
void SingleModeJudge(void)
{
	if(G_DILNGSwitch == ON) { //ȷ��˫ȼ�Ͽ��عر�
	   G_un16SysMode = SYS_DURAL;
	   return;
	}
	
	if(G_un16IgSignal == ON)   //����յ�����ź� ���Խ׶��ɴ��ڽ��� ������IO�жϷ���
  {
		G_un16IgSignal = OFF;
		G_un16DuralMode = SINGLE_MODE_IDLE; //������������
		return;
  }

}
///////////////////////////////////////////////////////
//���ٹ���������		
/*#define G_STLowStp     //
#define G_STHiStp        //
#define G_STOilStp      //
#define G_STHiStCount   //
#define G_STPaTiSt	                                 // */
///////////////////////////////////////////////////////
void StartCondition(void)
{
	if(G_un16RPM < G_STLowStp)  //�����ǰת�ٵ����������ת��
	{
		G_un16SingleMode = SINGLE_MODE_STOP;   //����תΪֹͣ����
	}
	else
	{
		if(G_un16RPM > G_STHiStp)
		{
			G_STHiStCount++;
			if(G_STHiStCount > G_STPaTiSt)
			    G_un16SingleMode = SINGLE_MODE_IDLE; //ת����� �����ɹ����뵡�ٹ���
			else
			    StartCondition_Sub();  //���û�н����������Ʋ���
		}
  	else 
	  {
  	  	G_STHiStCount = 0;
  	  	StartCondition_Sub();
	  }
	}
}

    	      
///////////////////////////////////////////////////////
//ϵͳ˫ȼ��ģʽ����                                 //
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
  //G_un16Pedal = look1D_U16_U16(G_un16PedalPosAD,un16TabPedalAD,10,un16TabPedalPercent);  //��������̤��MAP	
  nPedalRatio = 1000 + 2*G_un16PedalPosAD - 2*nPedalADPre;  
  //********************���ٹ���****************************//
  if(G_un16RPM>2800)  
	{
			//ת��>2800rpm
			G_un16DuralMode = DURAL_MODE_SPEEDLIMIT;    //  DURAL_MODE_SPEEDLIMIT = 6
			goto RETURN;
	}
	//****************�����ٹ���**************// 
  if(nPedalRatio > PEDAL_RATIO_MAX &&G_un16RPM >= 750)  //  PEDAL_RATIO_MAX=1200 
	{		
		 G_un16DuralMode = DURAL_MODE_OVERACC;   //  DURAL_MODE_OVERACC = 4
	   goto RETURN;
	}
	//****************�����ٹ���**************//
  if(nPedalRatio < PEDAL_RATIO_MIN && G_un16RPM >= 750)     //PEDAL_RATIO_MIN=900 
	{
		 G_un16DuralMode = DURAL_MODE_OVERDEC;		
		 goto RETURN;
  }
  //*****************������ʻ����***************************//
  if(G_un16Pedal>=10 && G_un16RPM >=1100)   //
  {
	   G_un16DuralMode = DURAL_MODE_NORMAL;   //DURAL_MODE_NORMAL = 3
	}
  RETURN:
  nPedalADPre = G_un16PedalPosAD;     // ����λ�ø���ֵ
}
///////////////////////////////////////////////////////
//ϵͳ��ȼ��ִ�����������                           //
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
//ϵͳ˫ȼ��ִ�����������                           //
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
/*                      ˫ȼ����ͨģʽ                       */
/*************************************************************/
void NormalCtrl()
{
  uint32 nTemp;
  G_DOLNGRVRelay = ON;
	//***************��ѯmap*******************************//
	//G_un16InjWide = look2D_U16_U16_U16(G_un16RPM,G_un16Pedal, \
						        	//u16TabSpeedX, 19,\
							        //u16TabPedalY, 14,u16TabInjWidth);
	//***************���䷧�������*******************//
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
/*                      ˫ȼ���ٶ�����ģʽ                   */
/*************************************************************/
void SpeedLimitCtrl()
{
	 
   if(G_un16InjWide != 0)
       G_un16InjWide = 0;
   
   G_DOLNGRVRelay = OFF;
}
/*************************************************************/
/*                      ˫ȼ�ϼ����ٿ���ģʽ                 */
/*************************************************************/
void OverAccCtrl()
{
    G_DOLNGRVRelay = ON;
  /*  G_un16InjWide = look2D_U16_U16_U16(G_un16RPM,G_un16Pedal, \
						        	u16TabSpeedX, 19,\
							        u16TabPedalY, 14,u16TabInjWidth);  */
}
/*************************************************************/
/*                      ˫ȼ�ϼ�����ģʽ                     */
/*************************************************************/
void OverDecCtrl()
{   
    G_DOLNGRVRelay = ON;
    //G_un16InjWide = 1500;
}
/*************************************************************/
/*                      ������ֹͣģʽ                       */
/*************************************************************/
void EngineStopCtrl()
{
   if(G_un16InjWide != 0)
       G_un16InjWide = 0;
   G_DOLNGRVRelay = OFF;
}

/*************************************************************/
/*                      ��ȡMAP                              */
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



