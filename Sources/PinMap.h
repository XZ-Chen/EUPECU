//-------------------------------------------------------------------------*
//文件名: ECT.h                                                        	   *
//说  明: 增强型定时器头文件                                         		   *
//初始时间：  2012年07月02日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _PINMAP_H
#define _PINMAP_H

#define PIN1_24V       1
#define PIN2_GND       2
#define PIN3_GND       3
#define PIN4_5V        4
#define PIN36_24VRLY   36

//热电偶
#define PIN6_TCN       5 //ThemalCouple T-
#define PIN7_TCP       6 //ThemalCouple T+

//CAN接口
#define PIN7_CANL     7
#define PIN8_CANH     8




//步进电机
#define PIN11_B1       11   //步进电机
#define PIN12_A1       12
#define PIN13_A2       13
#define PIN14_B2       14

//6路通用AD

#define PIN15_AD       0
#define PIN16_AD       1 
#define PIN17_AD       2
#define PIN22_AD       4
#define PIN23_AD       5


#define PIN24_AD       11
#define PIN25_AD       12
#define PIN26_AD       13

//2路压力温度         
#define PIN30_P        7
#define PIN9_NTC       8  //AD8
#define PIN29_P        9
#define PIN10_NTC      10 //AD10
//1路NTC水温
#define PIN27_NTCP     6    //水温
#define PIN28_NTCN     28


//转速传感器
#define PIN18_SPEEDP   18  //SPEED+
#define PIN19_SPEEDN   19  //SPEED-

//4路高位开关输入（24V-->5V) 
#define PIN20_DI       0
#define PIN21_DI       1
#define PIN22_DI       2
#define PIN23_DI       3 

//宽域氧传感器
#define PIN31_UEGO_IP   31
#define PIN32_UEGO_VM   32
#define PIN33_UEGO_HN   33 //H-
#define PIN34_UEGO_HP   34 //H+
#define PIN35_UEGO_IA   35 
#define PIN50_UEGO_UN   50 

//7路1A低端开关（低电流）
#define PIN43_LDO      3
#define PIN44_LDO      2
#define PIN45_LDO      1
#define PIN46_LDO      0
#define PIN47_LDO      4
#define PIN48_LDO      5
#define PIN49_LDO      6

//12路10A低端开关（高电流）
#define PIN37_HDO      7
#define PIN38_HDO      8
#define PIN39_HDO      9
#define PIN40_HDO      10
#define PIN41_HDO      11
#define PIN42_HDO      12
#define PIN51_HDO      13
#define PIN52_HDO      14
#define PIN53_HDO      15 
#define PIN54_HDO      16
#define PIN55_HDO      17
#define PIN56_HDO      18


#define DI_IGSWITCH_PIN   PIN21_DI   //点火开关    0有效
#define DI_LNGSWITCH_PIN  PIN20_DI   //天然气开关  0有效

#define DO_MAINRLY_PIN  PIN54_HDO
#define DO_LNGRLY_PIN   PIN53_HDO   

#define AD_BATTERYVOL_CH  PIN15_AD    //步进电机位置AN0 
#define AD_PEDAL_CH       PIN16_AD    //油门位置AN3
#define AD_COOLWATER_CH   PIN22_AD    //水温AN04

#define INJECTOR_PIN1 PIN37_HDO
#define INJECTOR_PIN2 PIN38_HDO
#define INJECTOR_PIN3 PIN39_HDO
#define INJECTOR_PIN4 PIN40_HDO
#define INJECTOR_PIN5 PIN51_HDO
#define INJECTOR_PIN6 PIN52_HDO

#define DIESELINJ_HV  PIN52_HDO
#define DIESELINJ_LV  PIN37_HDO
#define LNGINJ_HV     PIN39_HDO
#define LNGINJ_LV     PIN40_HDO
#define Cylinder_1      PIN51_HDO
#define Cylinder_2      PIN53_HDO

#define LED1 PIN37_HDO
#define LED2 PIN38_HDO
#define LED3 PIN39_HDO
#define LED4 PIN40_HDO



//-------------------------------------------------------------------------* 


#endif