#ifndef __usart_H
#define __usart_H

#include "system.h" 
#include "stdio.h" 


#define USART_REC_LEN 6  //接收缓冲数组大小

extern uint16_t USART_RX_STA;
extern uint8_t USART_RX_BUF[USART_REC_LEN]; 


void USART1_Init(u32 bound);



#endif


