#include "stm32f10x_gpio.h"
//#include "stm32_eval.h"
#include "stm32f10x_usart.h"
#include "Main.hpp"
#include "_ADC.hpp"
#include "_UART.h"
#include "_FXP_Math.h"
#include "_AV_Sensors.h"



//#define countof(a)   (sizeof(a) / sizeof(*(a)))
uint8_t UART_TxBuffer[256];

//---------------------------------------------------------------------------------------------------------
// Создание объектов
//---------------------------------------------------------------------------------------------------------
using namespace src;

CADC_type1	ADC_1;	// АЦП1-1	20мкс
CADC_type2	ADC_2;	// АЦП3-х
CUART1			UART_1(32,32);

Av_Rms_Sensors		I(0.00002, 0.001);//(ts, tf)

Iq a((float)0.1, 12);
//float b=2.1, c=0.3;
long tmp32_1,tmp32_2,tmp32_3,tmp32_4,tmp32_5;
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
  GPIO_Configuration();
//TIM_TypeDef *tim;
//	tim = TIM4;
//---------------------------------------------------------------------------------------------------------
// Инициализация объектов
//---------------------------------------------------------------------------------------------------------
	ADC_1.Init();
	ADC_2.Init();
	UART_1.Init();
//	I.PutSample((long)a.val);
/*	I.Set_ts(0.00002);
	U1.Set_ts(0.00006);
	U2.Set_ts(0.00006);
	I.Set_tf(0.2);
	U1.Set_tf(0.2);
	U2.Set_tf(0.2);*/

a=_IQ12(1.5);
/*c=_IQ(3.7);
tim->CNT =0;
tmp32_1 = tim->CNT;
	a += b;
tmp32_2 = tim->CNT;	//28 ,26
	c *= a;
tmp32_3 = tim->CNT;	//78, 76
	c*=_IQ(2);
tmp32_4 = tim->CNT;	//94, 86
	c /= a;	// 0.61mks, float 1.66mks
tmp32_5 = tim->CNT;	//294, 296(16:16), 42(6:10)

tmp32_1 /= tmp32_2;
tmp32_4 = tim->CNT;	//94, 86
 tmp32_3 = sqrt((float)c.val*(1<<GLOBALQ));	// 3.5mks
tmp32_1 = tim->CNT;
 tmp32_4 = sqrt_newton(c.val<<GLOBALQ);	// mks
tmp32_2 = tim->CNT;
//	tmp32 = c.integer();
	a=_IQ(123.77);
	b=_IQ(77.12);
//	c = a+_IQ(tmp32);
	c = b+_IQ(50);
*/
//---------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------

	while (1)
 {
	GPIOA->BSRR = 1;
	GPIOA->BRR = 1;
 }
}

