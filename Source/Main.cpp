#include "stm32f10x_gpio.h"
//#include "stm32_eval.h"
#include "stm32f10x_usart.h"
#include "Main.hpp"
#include ".\_ADC\_ADC.hpp"
#include ".\_UART\_UART.h"
#include ".\_AnalogSensors\_AnalogSensors.h"
#include "_PWM\_PWM.h"
#include <vector>



//#define countof(a)   (sizeof(a) / sizeof(*(a)))
uint8_t UART_TxBuffer[256];

//---------------------------------------------------------------------------------------------------------
// Создание объектов
//---------------------------------------------------------------------------------------------------------
using namespace src;
using namespace std;

Adc_1					adc_1;	// АЦП1-1	20мкс
Adc_3					adc_3;	// АЦП3-х
CUART1				UART_1(32,32);
Pwm2phaseNONZ	pwm;

AnalogRmsSensor		current		(0.00002, 0.050);//(ts, tf)
AnalogRmsSensor		voltage		(0.00006, 0.001);//(ts, tf)
AnalogRmsSensor		voltageRms(0.00006, 0.050);//(ts, tf)

vector<int> v;

//---------------------------------------------------------------------------------------------------------
// Вектора обработчиков прерываний
//---------------------------------------------------------------------------------------------------------

//void DMA1_Channel4_IRQHandler(void);
void DMA1_Channel4_IRQHandler()
{
	UART_1.TxISR();

	//Clears the DMA1 Channel 14 pending flags.
	DMA_ClearFlag(DMA1_FLAG_TC4);
	//Clears the DMA1 Channel 14 interrupt pending bits.
	DMA_ClearITPendingBit(DMA1_IT_TC4);
}

// UART1 Rx no Empty
void USART1_IRQHandler()
	{

   if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
		 UART_1.RxISR();
     /* Disable the USARTy Receive interrupt */
//     USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    }
   
   if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
    {   
    }

	}

//---------------------------------------------------------------------------------------------------------
// Хуйня переключения пина
//---------------------------------------------------------------------------------------------------------

void RCC_Configuration(void)
{    
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
}

 void GPIO_Configuration(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;
// GPIO Init
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 }

//---------------------------------------------------------------------------------------------------------
// MAIN PROGRAM
//---------------------------------------------------------------------------------------------------------

 int main ()
{
// Переинициализация множителя
//  system_stm32f10x.c(124)		#define HSE_VALUE    ((uint32_t)12000000) - вернуть на 8МГц, если потребуется
//	system_stm32f10x.c(1056)	RCC_CFGR_PLLMULL6 Заменил множитель с 9 на 6. Из за кварца 12МГц вместо 8Мгц
	
  GPIO_Configuration();
//TIM_TypeDef *tim;
//	tim = TIM4;

//---------------------------------------------------------------------------------------------------------
// Инициализация объектов
//---------------------------------------------------------------------------------------------------------
	adc_1.Init();
	adc_3.Init();
	UART_1.Init();
	pwm.init();
	
	current.SetCalibration(123);
	voltage.SetCalibration(210);
	voltageRms.SetCalibration(321);

//---------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------

	v.push_back((int)1);
	v.push_back(2);
	v.push_back(3);
  
  pwm.setValue (0.2);
  pwm.setValue (0.4);
  pwm.setValue (0.6);
	
	while (1)
 {
	GPIOA->BSRR = 1;
	GPIOA->BRR = 1;
	current.PutSample(adc_1.GetSample());
	voltage.PutSample(adc_1.GetSample());
	voltageRms.PutSample(adc_1.GetSample());
 }
}

