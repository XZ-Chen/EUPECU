//-------------------------------------------------------------------------*
//�ļ���: SensorModule.c 					                             	                   *
//˵  ��: ģ/��ת��ģ�������ļ�	  								                         *
//��ʼʱ�䣺  2012��06��30��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#include "SensorModule.h"
#include "CrankModule.h"
#include "DebugConfig.h"

//-------------------------------------------------------------------------*
//������: SensorModuleInit                                                 	     *
//��  ��: ��ʼ������������ģ��                                                    * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*


sensor batteryVol_sensor,pedalpos_sensor,coolwater_sensor,crankspeed_sensor;

void ValueAverage(sensor *pSensor,uint16 nNewValue) 
{
    int8 i;
    uint16 sum;
    
    for(i=pSensor->pointer-1;i>=0;i--)  //rise order sort
    {
        if(nNewValue < pSensor->value[i])
        {
            pSensor->value[i+1] = pSensor->value[i];
            if(i==0) pSensor->value[0] = nNewValue;
        }
        else
        {
            pSensor->value[i+1] = nNewValue;
            break;
        }
    }
    pSensor->pointer++;
    if(pSensor->pointer == 6)
    {
        pSensor->pointer = 2;
        sum=0;
        for(i=2;i<=3;i++)
        {
            sum += pSensor->value[i];
            pSensor->value[i-2] = pSensor->value[i];
        }
        pSensor->value[6] = (sum>>1);
    }
}
void SensorVarInit(sensor *pSensor){
  uint8 i;
  pSensor->status = 0;
  pSensor->pointer = 2;
  for(i = 0;i<7;i++)
    pSensor->value[i] = 0;   
}
void SensorModuleInit(void)
{  
    SensorVarInit(&batteryVol_sensor);        //��ص�ѹ
    SensorVarInit(&pedalpos_sensor);          //����λ��
    SensorVarInit(&coolwater_sensor);         //�����¶�
    SensorVarInit(&crankspeed_sensor);        //ת��
}

extern uint16 un16TabPedalAD[11];

void SensorScan(uint16 *pSensor) 
{    
    uint16 nNewValue = 0;
    nNewValue = ATDRead(AD_BATTERYVOL_CH);
    ValueAverage(&batteryVol_sensor,nNewValue);
    nNewValue = CrankSpeedRead();
    ValueAverage(&crankspeed_sensor,nNewValue);
    nNewValue = ATDRead(AD_PEDAL_CH);
    ValueAverage(&pedalpos_sensor,nNewValue);
    nNewValue = ATDRead(AD_COOLWATER_CH);
    ValueAverage(&coolwater_sensor,nNewValue);

    #if(DEBUGMODE == 1)  
    *(pSensor+0) = crankspeed_sensor.value[6];
    #elif(DEBUGMODE == 2)   
    *(pSensor+0) = 2000;
    #endif
    *(pSensor+1) = pedalpos_sensor.value[6];
    *(pSensor+2) = batteryVol_sensor.value[6];
    *(pSensor+3) = coolwater_sensor.value[6];
}
void SensorProcess(uint16 *pSensor)
{
    if(*(pSensor+2) <= 930) 
    {
        SCI_SendDec16u(*(pSensor+2));  
        DOOutput(LED1,OFF); 
    } 
    else
    {
        SCI_SendDec16u(*(pSensor+2));  
        DOOutput(LED1,ON); 
    }
}
 