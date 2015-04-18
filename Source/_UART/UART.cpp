#include "_UART.h"
#include "stm32f10x.h"


// Обработчик прерывания DMA UART-TC
//using namespace src;


namespace src{

	void CUART1::Init()
	 {
		// Enable Clocks
		/* DMA clock enable */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		/* Enable GPIO,USART1 clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
		
		// UART I\O Init
		/* Configure USART1 Rx*/
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* Configure USART1 Tx as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		// UART DMA Tx Init (Channel_4)
		DMA_InitTypeDef DMA_InitStructure;
		USART_TypeDef *str=USART1;
		/* USART1_Tx_DMA_Channel (triggered by USART1 Tx event) Config */
		DMA_DeInit(DMA1_Channel4);
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&str->DR;
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)txbufer;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_BufferSize = countof(txbufer);
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel4, &DMA_InitStructure);

		// UART DMA Rx Init (Channel_5)
//		USART_TypeDef *str=USART1;
		/* USART1_Tx_DMA_Channel (triggered by USART1 Tx event) Config */
		DMA_DeInit(DMA1_Channel5);
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&str->DR;
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rxbufer;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		DMA_InitStructure.DMA_BufferSize = countof(rxbufer);
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel5, &DMA_InitStructure);

		// UART Init
		USART_InitTypeDef USART_InitStructure;
		USART_StructInit(&USART_InitStructure);
		//ReInit
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	// Rx no Empty

		// Настройка UART-DMA каналов
		NVIC_InitTypeDef NVIC_InitStructure;
		// Enable the UART1 Interrupt 
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		// UART Init
		USART_Cmd(USART1, ENABLE);
		// Настройка прерываний UART-DMA
		DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);	//Transfer complete interrupt enable
		/* Enable DMA1 channel4,channel5 */
		DMA_Cmd(DMA1_Channel4, ENABLE);
		DMA_Cmd(DMA1_Channel5, ENABLE);

	 }

	void CUART1::Tx()
	 {
	 }

	void CUART1::Rx()
	 {
	 }
	 void CUART1::TxISR()	// Обработчик прерывания TC
	 {
		if(!DMA1_Channel4->CNDTR)
		{ DMA_Cmd(DMA1_Channel4, DISABLE);
			DMA1_Channel4->CNDTR = 2; 
			DMA_Cmd(DMA1_Channel4, ENABLE);
		}	
	 }

	 void CUART1::RxISR()	// Обработчик прерывания Rx
	 {
		 tmp = rxbufer[0];
		 //txbufer[0] = rxbufer[0];
	 }
/*	void transm_complete_int()
	{
		if(!DMA1_Channel4->CNDTR)
		{ DMA_Cmd(DMA1_Channel4, DISABLE);
			DMA1_Channel4->CNDTR = 10; 
			DMA_Cmd(DMA1_Channel4, ENABLE);
		}	

		//Clears the DMA1 Channel 14 pending flags.
		DMA_ClearFlag(DMA1_FLAG_TC4);
		//Clears the DMA1 Channel 14 interrupt pending bits.
		DMA_ClearITPendingBit(DMA1_IT_TC4);
	}*/


	
}
	

