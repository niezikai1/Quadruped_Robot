
/*******************************************************************************
  * Name    :main.c
  * Author  :
  * Function:****
  * Version :V1.0.0
  * Data    :2025.1.2
*******************************************************************************/

/*-------------include file---------------------------*/
#include "system.h"

/*-------------variable statement---------------------*/



/*------------------function--------------------------*/


int main()
{
	SysManage_Main_Init();
	
	Init_State();
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000); 
	delay_ms(1000);
	delay_ms(1000);
	while(1)
	{
	  // Analysis_Data();
		
		// Test Each Leg
		
		// Right_Front_leg(Right_Front_Init_Vertical_Angle+vertical_move_direction[Right_Front]*30, Right_Front_Init_Horizontal_Angle+horizontal_move_direction[Right_Front]);
		// Left_Back_leg(Left_Back_Init_Vertical_Angle+vertical_move_direction[Left_Back]*30, Left_Back_Init_Horizontal_Angle+horizontal_move_direction[Left_Back]);
		// Left_Front_leg(Left_Front_Init_Vertical_Angle+vertical_move_direction[Left_Front]*30, Left_Front_Init_Horizontal_Angle+horizontal_move_direction[Left_Front]);
		// Right_Back_leg(Right_Back_Init_Vertical_Angle+vertical_move_direction[Right_Back]*30, Right_Back_Init_Horizontal_Angle+horizontal_move_direction[Right_Back]);
		
		// Test Function
	  
		Init_State();
		// Try_Move_Forward();
		// Try_Move_Backward();
		// Try_Turn_Left();
		// Try_Turn_Right();
	}
}
