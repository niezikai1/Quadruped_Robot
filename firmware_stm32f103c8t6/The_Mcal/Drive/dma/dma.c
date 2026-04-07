#include "dma.h"

/*******************************************************************************
* Function Name     : DMAx_Init
* Function Purpose  : DMA initialization function
* Input Parameters  : 
					 DMAy_Channelx: DMA channel selection, @ref DMA_channel DMA_Channel_0~DMA_Channel_7
					 par: Peripheral address
					 mar: Memory address
					 ndtr: Data transfer count
* Output Parameters : None
*******************************************************************************/ 
void DMAx_Init(DMA_Channel_TypeDef* DMAy_Channelx,u32 par,u32 mar,u16 ndtr)
{
	DMA_InitTypeDef  DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//DMA1时钟使能 
	
	//DMA_DeInit(DMAy_Channelx);
	
	/* 配置 DMA */
	DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr = mar;//DMA 存储器0地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//存储器到外设模式
	DMA_InitStructure.DMA_BufferSize = ndtr;//数据传输量 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式 
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMAy_Channelx, &DMA_InitStructure);//初始化DMA 
	
}

/*******************************************************************************
* Function Name     : DMAx_Enable
* Function Purpose  : Start a DMA transfer
* Input Parameters  : DMAy_Channelx: DMA channel selection, @ref DMA_channel DMA_Channel_0~DMA_Channel_7
					 ndtr: Data transfer count
* Output Parameters : None
*******************************************************************************/ 
void DMAx_Enable(DMA_Channel_TypeDef *DMAy_Channelx,u16 ndtr)
{
 
	DMA_Cmd(DMAy_Channelx, DISABLE);                      //关闭DMA传输 
	
	DMA_SetCurrDataCounter(DMAy_Channelx,ndtr);          //数据传输量  
 
	DMA_Cmd(DMAy_Channelx, ENABLE);                      //开启DMA传输 
}	  
