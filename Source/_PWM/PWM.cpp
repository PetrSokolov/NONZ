//#####################################################################################
//	Файл				PWM.cpp
//	Название:		Движок меню. На базе автомата состояний.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 23 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#include "_PWM.h"
#include "stdint.h"
#include "stm32f10x_rcc.h"



using namespace src;

//======================================================================================================================== 
// Pwm - генератор 3 фазного ШИМ
//======================================================================================================================== 
//	Методы:
//	setFrequency	- Установить частоту модуляции ШИМ
//	setDeathTime	- Установить мертвое время ШИМ
//	setValue			- Установить амплитуду сигнала (1-максамальный)
//	setBlock			- Установить/снять режим блокировки
//	init					- Инициализация. Имеет несколько реализаций под разное железо



//======================================================================================================================== 
// Pwm2phaseNONZ- генератор 2 фазного ШИМ для НО/НЗ
//======================================================================================================================== 
//	init					- Инициализация. Реализация под железо НО/НЗ. На базе TIM1

void Pwm2phaseNONZ::Init (void)
{
/*
TIM2->CR1 = 0x00000000; //по умолчанию
TIM2->PSC = 0x000000FF; //установка макс. знач. предделителя
TIM2->ARR = 0x00000FFF; //установка макс. перезагружаемого знач.
TIM2->CCMR1 = 0x00000068; //Устанавливаем режим ШИМ
TIM2->CCR1 = 0x000000FF; //Задаем стартовое значение ШИМ
TIM2->CCER = 0x00000101; //разрешаем выхода канала 1
TIM2->DIER = 0x00000000; //разрешаем обновление прерывания
TIM2->EGR = 0x00000001; //разрешаем обновление
TIM2->CR1 = 0x00000001; //разрешаем работу таймера	
*/

	// Включение синхронизации таймера и пинов-выходов
	// TIM1, GPIOA, GPIOB, GPIOE and AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE|
                         RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);



	// GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	// GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 
// GPIOB Configuration: BKIN pin
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);  


// Расчет значения регистра ARR для генерации ШИМ 50КГц
	RCC_ClocksTypeDef rcc_ClocksStatus;
	// Расчет базовых частот синхронизации
	RCC_GetClocksFreq(&rcc_ClocksStatus);

// Проверка предделителя APB2. Если есть, то TIM1CLK = (PCLK2 x 2). Иначе TIM1CLK = PCLK2
	#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
	if(RCC->CFGR & CFGR_PPRE2_Set_Mask){
		_сlkFrequency = rcc_ClocksStatus.PCLK2_Frequency<<1;
	}
	else{
		_сlkFrequency = rcc_ClocksStatus.PCLK2_Frequency;
	}
	
	// Расчет периода таймера
	_timerPeriod = (SystemCoreClock / 50000) - 1;
	_dutyCycle1 = 0.5;
	_dutyCycle2 = 0.5;
	_dutyCycle3 = 0.5;
	// Compute CCR1 value to generate a duty cycle for channel 1,2,3
	_channel1Pulse = (uint16_t) _dutyCycle1 * (_timerPeriod - 1);
	_channel2Pulse = (uint16_t) _dutyCycle2 * (_timerPeriod - 1);
	_channel3Pulse = (uint16_t) _dutyCycle3 * (_timerPeriod - 1);

	// Time Base configuration
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Prescaler					= 0;
	TIM_TimeBaseStructure.TIM_CounterMode				= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period						= _timerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision 		= 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


	// Channel 1, 2 and 3 Configuration in PWM mode
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode				= TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState		= TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState	= TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse					= _channel1Pulse;
	TIM_OCInitStructure.TIM_OCPolarity		= TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity		= TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState		= TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = _channel2Pulse;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
 
	TIM_OCInitStructure.TIM_Pulse = _channel3Pulse;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);


	// Automatic Output enable, Break, dead time and lock configuration*/
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;

	TIM_BDTRInitStructure.TIM_OSSRState				= TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState				= TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel				= TIM_LOCKLevel_1;
	TIM_BDTRInitStructure.TIM_DeadTime				= 11;
	TIM_BDTRInitStructure.TIM_Break						= TIM_Break_Enable;
	TIM_BDTRInitStructure.TIM_BreakPolarity		= TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
 
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
 
	// TIM1 counter enable
	TIM_Cmd(TIM1, ENABLE);

	// Main Output Enable
	TIM_CtrlPWMOutputs(TIM1, ENABLE);


}



