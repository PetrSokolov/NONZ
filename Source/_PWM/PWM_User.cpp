//########################################################################################
//	Файл				PWM.cpp
//	Название:		ШИМ для НО/НЗ.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 23 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
// Примечание:  Методы общего класса, реализация которых привязанна к конкретному проекту.
//########################################################################################

#include "_PWM.h"
#include "stdint.h"
#include "math.h"
#include "stm32f10x_rcc.h"



using namespace src;

//======================================================================================================================== 
// Pwm2phaseNONZ- генератор 2 фазного ШИМ для НО/НЗ
//======================================================================================================================== 
//	Методы:
//	setFrequency			- Установить частоту модуляции ШИМ
//	setValue					- Установить амплитуду сигнала (1-максамальный)
//	setBlock					- Установить/снять режим блокировки
//	computeDeathTime	- Установить мертвое время ШИМ. Имеет несколько реализаций под разное железо
//	init							- Инициализация. Имеет несколько реализаций под разное железо


void Pwm2phaseNONZ::setValue (float value)
{
	_channel1Pulse = (uint16_t) (value * (_timerPeriod - 1));
	_channel2Pulse = (uint16_t) (value * (_timerPeriod - 1));
	_channel3Pulse = (uint16_t) (value * (_timerPeriod - 1));
  *_compare1 = _channel1Pulse;
  *_compare2 = _channel2Pulse;
  *_compare3 = _channel3Pulse;
}


//	Установка Death Time. Задается в микросекундах deathtime[мкс]
//  Возвращает значение, записываемое в регистр
uint16_t Pwm2phaseNONZ::computeDeathTime (float deathTime)
{
	// Расчет death time заключается в выборе множителя периода дискретизации и значения счетчика death time

	uint16_t	reg;						// временный контейнер регистра
	uint32_t	n1, n2, n3, n4;	// счетчик death time
	float			td;							// Период дискретизации таймера

	// Пересчет микросекунд в число периодов синхронизации
	td = (float)1/_clkDeathTime;
	
	n1	= (uint32_t)(deathTime * 1e-6 / td);
	n2	= (uint32_t)(deathTime*1e-6 - 2*64*td 	/ (2*td));
	n3	= (uint32_t)(deathTime*1e-6 - 8*32*td		/ (8*td));
	n4 	= (uint32_t)(deathTime*1e-6 - 16*32*td 	/ (16*td));
	reg =0;
	if( n1 <= 0x7F ){
		reg = 0x00 + n1;
	}
	 else{
	  if( n2 <= 0x3F ){
			reg = 0x80 + n2;
		}
		 else{
			 if( n3 <= 0x1F ){
				reg = 0xC0 + n3;
			}
			 else{
				if( n4 <= 0x1F ){
					reg = 0xE0 + n4;
				}
				else{ reg = 11; }	// Значение в случае исключения
			 }
	   }
	 }
	return reg;
}




//---------------------------------------------------------------------------------------------
//	init	- Инициализация. Реализация под железо НО/НЗ. На базе TIM1
//---------------------------------------------------------------------------------------------

void Pwm2phaseNONZ::init (void)
{


  // Инизиализация указателей на регистры перифирии
	TIM_TypeDef*	tim = TIM1;   //	Указатель на таймер TIMx
  _compare1 = &TIM1->CCR1;    //  Указатель на регистр сравнения CH1
  

  // Инизиализация указателей на настроечные параметры
  _deathTime = &pwmDeathTime;     //  Указатель на настроечный параметр. death time[мкс]
  _value     = &pwmValue;         //  Указатель на настроечный параметр. Амплитуда [%]
  
  
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


// Расчет значения регистра ARR для генерации ШИМ 50КГц (периода таймера			)
	RCC_ClocksTypeDef rcc_ClocksStatus;
		// Расчет базовых частот синхронизации
		RCC_GetClocksFreq(&rcc_ClocksStatus);

		// Проверка предделителя APB2. Если есть, то TIM1CLK = (PCLK2 x 2). Иначе TIM1CLK = PCLK2
		#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
		switch(RCC->CFGR & CFGR_PPRE2_Set_Mask){
			case 0:		{ _clkTimer = rcc_ClocksStatus.PCLK2_Frequency / (tim->PSC+1); 		}break;
			default:	{ _clkTimer = rcc_ClocksStatus.PCLK2_Frequency / (2*(tim->PSC+1));	}break;
		}
		// Расчет частоты семплирования dead-time (dead-time and sampling clock)
		#define  TIM_CR1_CKD              ((uint16_t)0x0300)            /*!< CKD[1:0] bits (clock division) */
		switch(tim->CR1 & TIM_CR1_CKD){
			case TIM_CR1_CKD_0:		{_clkDeathTime = _clkTimer>>1;}	break;
			case TIM_CR1_CKD_1:		{_clkDeathTime = _clkTimer>>2;}	break;
			case 0:
			default: 							{_clkDeathTime = _clkTimer; }		break;
		}
		
	
	_timerPeriod = (_clkTimer / 50000) - 1;
	_dutyCycle1 = 0.5;
	_dutyCycle2 = 0.5;
	_dutyCycle3 = 0.5;
	// Compute CCR1 value to generate a duty cycle for channel 1,2,3
	_channel1Pulse = (uint16_t) (_dutyCycle1 * (_timerPeriod - 1));
	_channel2Pulse = (uint16_t) (_dutyCycle2 * (_timerPeriod - 1));
	_channel3Pulse = (uint16_t) (_dutyCycle3 * (_timerPeriod - 1));

	// Time Base configuration
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Prescaler					= 0;
	TIM_TimeBaseStructure.TIM_CounterMode				= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period						= _timerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision 		= 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
 
	TIM_TimeBaseInit(tim, &TIM_TimeBaseStructure);


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

	TIM_OC1Init(tim, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = _channel2Pulse;
	TIM_OC2Init(tim, &TIM_OCInitStructure);
 
	TIM_OCInitStructure.TIM_Pulse = _channel3Pulse;
	TIM_OC3Init(tim, &TIM_OCInitStructure);


	// Automatic Output enable, Break, dead time and lock configuration*/
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	TIM_BDTRInitStructure.TIM_OSSRState				= TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState				= TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel				= TIM_LOCKLevel_1;
	TIM_BDTRInitStructure.TIM_DeadTime				= computeDeathTime(pwmDeathTime.getValueFlt());
	TIM_BDTRInitStructure.TIM_Break						= TIM_Break_Disable;//TIM_Break_Enable;
	TIM_BDTRInitStructure.TIM_BreakPolarity		= TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
 
	TIM_BDTRConfig(tim, &TIM_BDTRInitStructure);
 
	// tim counter enable
	TIM_Cmd(tim, ENABLE);

	// Main Output Enable
	TIM_CtrlPWMOutputs(tim, ENABLE);

}



