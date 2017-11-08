//-------------------------------------------------------------------------*
//文件名: SensorModule.c 					                             	                   *
//说  明: 模/数转换模块驱动文件	  								                         *
//初始时间：  2012年06月30日              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#include "SensorModule.h"
#include "CrankModule.h"
#include "DebugConfig.h"
//#include "MAP.h"

//-------------------------------------------------------------------------*
//函数名: SensorModuleInit                                                 	     *
//功  能: 初始化各个传感器模块                                                    * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*


sensor stppos_sensor,pedalpos_sensor,esttemp_sensor,crankspeed_sensor;

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
    SensorVarInit(&stppos_sensor);            //步进电机位置
    SensorVarInit(&pedalpos_sensor);          //油门位置
    SensorVarInit(&esttemp_sensor);           //排气温度
    SensorVarInit(&crankspeed_sensor);        //转速
}

extern uint16 un16TabPedalAD[11];

void SensorScan(uint16 *pSensor) 
{    
    uint16 nNewValue = 0;
    nNewValue = CrankSpeedRead();
    ValueAverage(&crankspeed_sensor,nNewValue);
    nNewValue = ATDRead(AD_STEPPER_CH);
    ValueAverage(&stppos_sensor,nNewValue);
    nNewValue = ATDRead(AD_PEDAL_CH);
    ValueAverage(&pedalpos_sensor,nNewValue);
    /*
    nTicks++;       
    //max6675读取时间的间隔不能太短，太短的话数据根本就不会变化，一致接收到的
    //的是最初的值，读取间隔改成200ms后面，读取正常
    if(nTicks == 10) {  //200ms
       nTicks = 0;
       esttemp_sensor.nValue = ExhasutTempRead();
    }
    */
    #if(DEBUGMODE == 1)  
    *(pSensor+0) = crankspeed_sensor.value[6];
    #elif(DEBUGMODE == 2)   
    *(pSensor+0) = 2000;
    #endif
    *(pSensor+1) = pedalpos_sensor.value[6];
    *(pSensor+2) = stppos_sensor.value[6];
    *(pSensor+3) = esttemp_sensor.value[6];
}

 
