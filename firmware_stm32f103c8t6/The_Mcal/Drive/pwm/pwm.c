#include "pwm.h"
 /*****  **********************************
*函    数 PWM_Init
*功    能 PWM初始化
*入口参数  无
*返 回 值  无
*********************************  *******/
void PWM_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0|GPIO_Pin_1);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM3);
 
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//复用输出
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;	//自动重装器，ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;	//预分频器，PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;						//输出比较模式，选择PWM模式1
	TIM_OCInitStruct.TIM_Pulse = 0; 													 //初始的CCR值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;		//输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
 
	TIM_Cmd(TIM2,ENABLE);
	
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;						//输出比较模式，选择PWM模式1
	TIM_OCInitStruct.TIM_Pulse = 0; 													 //初始的CCR值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;		//输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
	TIM_OC3Init(TIM3,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
	TIM_OC4Init(TIM3,&TIM_OCInitStruct);											//将结构体变量交给TIM_OC1Init，配置TIM2的输出比较通道1
 
	TIM_Cmd(TIM3,ENABLE);
	
	
}
 
/*****  **********************************
*函    数 PWM_SetCompare
*功    能 设定定时器占空比
*入口参数 占空比 (100 = 100us)
*返 回 值 无
*********************************  *******/
void PWM_SetCompare1(uint16_t Compare){
	
	TIM_SetCompare1(TIM2,Compare); //设置定时器2占空比 这里1比1us高电平 周期为20ms
 
}

void PWM_SetCompare2(uint16_t Compare){
	
	TIM_SetCompare2(TIM2,Compare); //通道2
 
}

void PWM_SetCompare3(uint16_t Compare){
	
	TIM_SetCompare3(TIM2,Compare); //通道3
 
}

void PWM_SetCompare4(uint16_t Compare){
	
	TIM_SetCompare4(TIM2,Compare); //通道4
 
}




void PWM_SetCompare5(uint16_t Compare){
	
	TIM_SetCompare1(TIM3,Compare); //设置定时器2占空比 这里1比1us高电平 周期为20ms
 
}

void PWM_SetCompare6(uint16_t Compare){
	
	TIM_SetCompare2(TIM3,Compare); //通道2
 
}

void PWM_SetCompare7(uint16_t Compare){
	
	TIM_SetCompare3(TIM3,Compare); //通道3
 
}

void PWM_SetCompare8(uint16_t Compare){
	
	TIM_SetCompare4(TIM3,Compare); //通道4
 
}

/*****  **********************************
*函    数 Servo_XX_XX_XX_Control
*功    能 控制舵机角度
*入口参数 Angle 舵机角度()
*返 回 值 
*********************************  *******/
void Servo_Left_Vertical_Front_Control(uint16_t Angle)//左前垂直舵机
{
	uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare1(Pulse);
	
}
 void Servo_Left_Horizontal_Front_Control(uint16_t Angle)//左前水平舵机
 {
	 uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare2(Pulse);
 }
 
 void Servo_Right_Vertical_Front_Control(uint16_t Angle)//右前垂直舵机
 {
	 uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare3(Pulse);
 }
 
 void Servo_Right_Horizontal_Front_Control(uint16_t Angle)//右前水平舵机
 {
	 uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare4(Pulse);
 }
 
 
 
 
 
 void Servo_Left_Vertical_Back_Control(uint16_t Angle)//左hou垂直舵机
{
	uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare5(Pulse);
	
}
 void Servo_Left_Horizontal_Back_Control(uint16_t Angle)//左hou水平舵机
 {
	 uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare6(Pulse);
 }
 
 void Servo_Right_Vertical_Back_Control(uint16_t Angle)//右hou垂直舵机
 {
	 uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare7(Pulse);
 }
 
 void Servo_Right_Horizontal_Back_Control(uint16_t Angle)//右hou水平舵机
 {
	 uint16_t Pulse;
	Pulse=Angle*11.1+500;//  0.9°：10us 高电平 取11.1 
	PWM_SetCompare8(Pulse);
 }

/*****  **********************************
*函    数 
*功    能 
*入口参数 
*返 回 值 
*********************************  *******/
 
 void Low_Speed_Control()
 {
	 uint8_t Angle;
	 for (Angle=25;Angle<100;Angle++)
	 {
		 Servo_Left_Vertical_Front_Control(Angle);
		delay_ms(8);
	 }
	  for (Angle=100;Angle>25;Angle--)
	 {
		 Servo_Left_Vertical_Front_Control(Angle);
		delay_ms(8);	 
	 }
	 
 }
 
