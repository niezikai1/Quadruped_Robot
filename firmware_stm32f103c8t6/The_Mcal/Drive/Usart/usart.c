#include "usart.h"		 

int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	USART_SendData(USART1,(u8)ch);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

uint8_t USART_RX_BUF[USART_REC_LEN]={0};   //接收缓冲，最大为USART_REC_LEN个字节
uint16_t USART_RX_STA = 0; //接收状态标记
uint8_t USART_RX_Index = 0;
uint8_t teemp;

/*******************************************************************************
* 函 数 名         : USART1_Init
* 函数功能		   : USART1初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/ 
void USART1_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

/*******************************************************************************
* 函 数 名         : USART1_IRQHandler
* 函数功能		   : USART1中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 rx_data;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		rx_data =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据 自动清楚RXNE标志位 若没有读取，则需要手动清楚 否则会卡在中断
		if(RX_BUF_STA==FALSE) 
		{
			
			if((rx_data==0xfe)||USART_RX_STA==1) 
			{
				if(RX_BUF_STA==FALSE)USART_RX_STA=1; //只有当上层请求状态为FALSE 才接收数据
				
				USART_RX_BUF[USART_RX_Index]=rx_data; 
				USART_RX_Index++;  //索引自增
				if((rx_data==0xef)&&(USART_RX_Index==USART_REC_LEN)) 
				{
					USART_RX_STA=0;
					USART_RX_Index=0;
					printf("接收完成\r\n");
					RX_BUF_STA=TRUE; // 标记给上层接收完成
				}
				
				if(USART_RX_Index>USART_REC_LEN)
				{
					USART_RX_STA=0;
					USART_RX_Index=0;
					printf("数据超时，错误\r\n");
				}
			}
		}
		else
		{
			printf("数据无效上层未操作，错误\r\n");
		}
	} 
} 	






