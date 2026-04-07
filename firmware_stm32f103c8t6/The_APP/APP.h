#ifndef _app_H
#define _app_H

/*******************************************************************************
  * Name    :Data_analysis.h.c
  * Author  :KitaOvO
  * Function:****
  * Version :V1.0.0
  * Data    :2025.3.15
*******************************************************************************/

/*-------------include file---------------------------*/
#include "system.h"

/*-------------variable statement---------------------*/


/*------------------function--------------------------*/
extern void Init_State(void);
extern void Reset_Group1(void);
extern void Reset_Group2(void);
extern void Try_Move_Forward(void);
extern void Try_Move_Backward(void);
extern void Try_Turn_Right(void);
extern void Try_Turn_Left(void);

#endif
