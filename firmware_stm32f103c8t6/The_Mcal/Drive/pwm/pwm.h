
#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"                  // Device header
                // Device header
#include "SysTick.h"
 
 
void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);

extern void Servo_Left_Vertical_Front_Control(uint16_t Angle);
extern void Servo_Left_Horizontal_Front_Control(uint16_t Angle);
extern void Servo_Right_Vertical_Front_Control(uint16_t Angle);
extern void Servo_Right_Horizontal_Front_Control(uint16_t Angle);

extern void Servo_Left_Vertical_Back_Control(uint16_t Angle);				//舵机左后垂直角度
extern void Servo_Left_Horizontal_Back_Control(uint16_t Angle);			//舵机左后水平角度
extern void Servo_Right_Vertical_Back_Control(uint16_t Angle);			//舵机右后垂直角度
extern void Servo_Right_Horizontal_Back_Control(uint16_t Angle);		//舵机右后水平角度

void Low_Speed_Control(void);
 
#endif
 

 
