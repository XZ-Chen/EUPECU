//-------------------------------------------------------------------------*
//文件名: Includes.h                                              	       *
//说  明: 总头文件,本文件包含:                                 		         *
//        主函数(main)文件中用到的头文件、外部函数声明及有关常量命名       *
//初始时间：  2012年07月05日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128                			                       *
//-------------------------------------------------------------------------*
#ifndef INCLUDES_H
#define INCLUDES_H
    //1 头文件
    //1.1 包含通用头文件(不需改变)
    #include "typedefine.h"           //类型别名定义

    //1.2 包含通用头文件(需要改变)
    #include <hidef.h>      /* common defines and macros */
    #include <MC9S12XET256.h>     /* derivative information */
    //1.2 包含面向硬件对象头文件  
    #include "CrankModule.h"
    #include "SensorModule.h"
    #include "GeneralFun.h" 
    #include "DIOModule.h"
    #include "SysTask.h"
    #include "lookup_table.h"
    #include "InjectorModule.h"
    #include "StepperModule.h"
    
    
    //2 宏定义

    //3 全局变量声明
#endif