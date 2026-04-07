/*******************************************************************************
  * Name    :Data_analysis.h.c
  * Author  :
  * Function:****
  * Version :V1.0.0
  * Data    :2025.3.15
*******************************************************************************/

/*-------------include file---------------------------*/
#include "Roobt_leg.h"

/*-------------variable statement---------------------*/


/*------------------function--------------------------*/

/*
*   Vertical angle  &&   Horizontal angle
*
*/
void Left_Front_leg(u8 Vertical,u8 Horizontal)
{
	Servo_Left_Vertical_Front_Control(Vertical);
	Servo_Left_Horizontal_Front_Control(Horizontal);
	
}

/*
*   Vertical angle  &&   Horizontal angle
*
*/
void Right_Front_leg(u8 Vertical,u8 Horizontal)
{
	Servo_Right_Vertical_Front_Control(Vertical);
	Servo_Right_Horizontal_Front_Control(Horizontal);
	
}

/*
*   Vertical angle  &&   Horizontal angle
*
*/

void Left_Back_leg(u8 Vertical,u8 Horizontal)
{
	Servo_Left_Vertical_Back_Control(Vertical);
	Servo_Left_Horizontal_Back_Control(Horizontal);
	
}
/*
*   Vertical angle  &&   Horizontal angle
*
*/


void Right_Back_leg(u8 Vertical,u8 Horizontal)
{
	Servo_Right_Vertical_Back_Control(Vertical);
	Servo_Right_Horizontal_Back_Control(Horizontal);
	
}



/*****
*
8
8
8*/
//void move_test()
//{
//	Left_Front_leg(120,90);
//	Right_back_leg(120,100); 
//	
// 	Right_Front_leg(60,90); 
//	Left_Back_leg(60,80);
//	delay_ms(1000);
//	

//	
//	/****************/
//	
//	Left_Front_leg(90,120); 
//	Right_back_leg(90,60);
//	delay_ms(100);
//	
////	Right_Front_leg(60,90); 
////	Left_Back_leg(60,90);
////	delay_ms(1000);
//	
//	Left_Front_leg(120,120); 
//	Right_back_leg(120,60); 
//	delay_ms(100);
//	
//	Right_Front_leg(90,50); 
//	Left_Back_leg(90,120);
//	delay_ms(100);
//	
//	Left_Front_leg(120,90);
//	Right_back_leg(120,100); 
//	delay_ms(100);
//	
//	Right_Front_leg(60,60); 
//	Left_Back_leg(60,120);
//	delay_ms(100);
//	
//	Right_Front_leg(60,90); 
//  Left_Back_leg(60,80);
//	delay_ms(100);
//	
//}
