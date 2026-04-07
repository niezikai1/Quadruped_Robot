
/*******************************************************************************
  * Name    :Data_analysis.h.c
  * Author  :
  * Function:****
  * Version :V1.0.0
  * Data    :2025.3.15
*******************************************************************************/

/*-------------include file---------------------------*/
#include "Data_analysis.h"

/*-------------variable statement---------------------*/

uint16_t RX_BUF_STA = FALSE;  // mcal层的串口接口标志
//extern uint8_t USART_RX_BUF[USART_REC_LEN];   //接收buf，需要mcal层定义提供


/*------------------function--------------------------*/


void Analysis_Data()
{
	if(RX_BUF_STA==TRUE)  //当该标志为true 表示接收到了一串数据 
	{

		switch(USART_RX_BUF[1])
		{
			case 0x01: 
				switch(USART_RX_BUF[2])
				{
		 			case 0x01: Left_Front_leg(USART_RX_BUF[3],USART_RX_BUF[4]);		
						//move_test();break;
					case 0x02:  Right_Front_leg(USART_RX_BUF[3],USART_RX_BUF[4]); break ;
					case 0x03:  Left_Back_leg(USART_RX_BUF[3],USART_RX_BUF[4]); break ;
					case 0x04:  Right_Back_leg(USART_RX_BUF[3],USART_RX_BUF[4]); break ;		
		  	}break ;
				
			case 0x02: 
				switch(USART_RX_BUF[2])
				{
		 			case 0x01:  Left_Front_leg(USART_RX_BUF[3],USART_RX_BUF[4]); break ;
					case 0x02:  Right_Front_leg(USART_RX_BUF[3],USART_RX_BUF[4]); break ;
					case 0x03:  Left_Back_leg(USART_RX_BUF[3],USART_RX_BUF[4]); break ;
					case 0x04:  Right_Back_leg(USART_RX_BUF[3],USART_RX_BUF[4]);break ; 		
		  	}break ;
		}

		
	}
	RX_BUF_STA=FALSE;
}
