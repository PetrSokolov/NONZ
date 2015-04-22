//#include "stm32f10x_gpio.h"
#include "_ADC.hpp"
#include "stm32f10x.h"
//#include "IADC_Init.hpp"

/*
ADC1			#[]		#[]		#[]		#[]		#[]		#[]		#[]		#[]		
ADC3			#[]#[]#[]					#[]#[]#[]					#[]#[]#[]					#[]#[]#[]
ADC2
TIM4_CC4	|CC4	|CC4	|CC4	|CC4	|CC4	|CC4	|CC4	|CC4	|CC4	|CC4	|CC4	
TIM3_CC1	|CC1							|CC1							|CC1							|CC1							
Time(mks)	|0		|20		|40		|60		|80		|100	|120	|140	|160	|180	|200
*/

//-------------------------------------------------------------------------------------------------------
// Различные реализации методов. Из которых буду выбирать метод интерфейса
// Здесь пользователь может написать свою реализацию
//-------------------------------------------------------------------------------------------------------
namespace src{

// Конструктор класса ADC1
Adc_1::Adc_1()
 {
 }
// Конструктор класса ADC2
Adc_3::Adc_3()
 {
 }

 // Реализация настройки АЦП1 для НО/НЗ
 // Преобразование запускается от TIM4:CC4, с периодом 20мкс
 // DMA1:ch1 переносит результат в буфер _convertedBuf, который зациклен размером буфера
 // 

 void Adc_1::Init(void)
 {
	// Clock config
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	/* DMA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 /* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

/* Configure PA.00 (ADC Channel 0) as analog input -------------------------*/
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
/* Configure PA.01 (ADC Channel 1) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
/* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
	 ADC_TypeDef *adc=ADC1;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&adc->DR;//DR_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&_convertedBuf;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = countof(_convertedBuf);
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
   /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

   // ADC1 configuration ------------------------------------------------------
  ADC_InitTypeDef ADC_InitStructure;
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//	 ADC_DiscModeChannelCountConfig(ADC1, 3);	// конвертировать 1-8 каналов за 1 триггер
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T4_CC4/*ADC_ExternalTrigConv_T3_TRGO*/;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 2;
  ADC_Init(ADC1, &ADC_InitStructure);

  // ADC1 regular channel 0 configuration
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
  // ADC1 regular channel 1 configuration
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
   // Enable ADC1 DMA
  ADC_DMACmd(ADC1, ENABLE);
  // Enable ADC1
  ADC_Cmd(ADC1, ENABLE);
	// External trigger ENABLE
	ADC_ExternalTrigConvCmd(ADC1, ENABLE);
  // Enable ADC1 reset calibration register
  ADC_ResetCalibration(ADC1);
  // Check the end of ADC1 reset calibration register
  while(ADC_GetResetCalibrationStatus(ADC1));
 
  // Start ADC1 calibration
  ADC_StartCalibration(ADC1);
  // Check the end of ADC1 calibration
  while(ADC_GetCalibrationStatus(ADC1));
      
  // Start ADC1 Software Conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	// Init Timer for this ADC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	// ENABLE clocks
	// Time Base configuration
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0x5A0;		// 50KHz at 72MHz CLK
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;	// No prescaler, TIM CLK is 72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// Compare register and Trigger output config
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
  TIM_OCInitStructure.TIM_Pulse = 0x7F; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
	
	TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_OC4Ref);
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_Cmd(TIM4, ENABLE);
 }

 // Реализация настройки АЦП3 для НО/НЗ
 // Преобразование запускается от TIM5:CC3, с периодом 60мкс
 // EOC - прерывание 60mks. В нем обрабатывается отсчет ADC3 и отсчеты ADC1
 // 
 void Adc_3::Init(void)
 {	 
 }

 
//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
// Объект АЦП с интерфейсом замены методов интерфейса
//CADC_1 ADC_1, ADC_2;
 
}//namespace


 

