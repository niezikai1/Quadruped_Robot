#ifndef _system_H
#define _system_H

/*******************************************************************************
  * Name    :system.c
  * Author  :@YI
  * Function:****
  * Version :V1.0.0
  * Data    :2025.1.2
	
*******************************************************************************/

/***********硬件抽象层接口处，所有外设在此处集中调用******************************/


/*-------------include file---------------------------*/
#include "stm32f10x.h"
#include "SysTick.h"
#include "usart.h"
#include "adc.h"
#include "pwm.h"

#include "Data_analysis.h"
#include "Roobt_leg.h"
#include "app.h"

/*-------------variable statement---------------------*/


#define TRUE 1
#define FALSE 0

/*-------------function-------------------------------*/




extern void SysManage_Main_Init(void); // 底层外设初始化

#endif
