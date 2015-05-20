#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "Main.hpp"
#include ".\_ADC\_ADC.hpp"
#include ".\_UART\_UART.h"
#include ".\_RTC\__RTC.h"
#include ".\_AnalogSensors\_AnalogSensors.h"
#include "_PWM\_PWM.h"
//#include ".\Menu_Items\_Engine.h"
#include ".\Menu_Items\_Parameters.h"
#include ".\Menu_Items\__Parameters_User.h"
#include <vector>
#include <map>
#include <string>
#include <stdio.h>




//#define countof(a)   (sizeof(a) / sizeof(*(a)))

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


Rtc rtc;  // Таймер реального времени

string str1 ("First string");
string str2 ("Second string");
string str3;


//---------------------------------------------------------------------------------------------------------
// Создание временных переменных. После отладки удалить.
//---------------------------------------------------------------------------------------------------------
uint16_t tmp_mbSize, tmp_idSize;
uint32_t tmp32_1, tmp32_2, tmp32_3, tmp32_4, tmp32_5, tmp32_6;
uint32_t tmp32_256, tmp32_257, tmp32_258, tmp32_259, tmp32_260, tmp32_261, tmp32_262, tmp32_263;
uint16_t tmp16_1, tmp16_2;
Parameter* par_ptr;
//Parameter2reg* par32_ptr;


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
// Переинициализация множителя. Не стирать. Для информации.
//  system_stm32f10x.c(124)		#define HSE_VALUE    ((uint32_t)12000000) - вернуть на 8МГц, если потребуется
//	system_stm32f10x.c(1056)	RCC_CFGR_PLLMULL6 Заменил множитель с 9 на 6. Из за кварца 12МГц вместо 8Мгц
	
  GPIO_Configuration();
//TIM_TypeDef *tim;
//	tim = TIM4;

//---------------------------------------------------------------------------------------------------------
// Инициализация объектов
//---------------------------------------------------------------------------------------------------------
//	mapsOfParameters.init();
  adc_1.Init();
	adc_3.Init();
	UART_1.Init();
	pwm.init();
  rtc.init();
	
	current.SetCalibration(123);
	voltage.SetCalibration(210);
	voltageRms.SetCalibration(321);

//---------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------

/*Parameter* parameterPointer;
parameterPointer = mapsOfParameters.GetMbParameter(256);
 tmp32_1 = parameterPointer->GetValue();
parameterPointer = mapsOfParameters.GetMbParameter(257);
 tmp32_1 = parameterPointer->GetValue();
parameterPointer = mapsOfParameters.GetMbParameter(5);
 tmp32_1 = parameterPointer->GetValue();
parameterPointer = mapsOfParameters.GetMbParameter(6);
 tmp32_1 = parameterPointer->GetValue();

parameterPointer = mapsOfParameters.GetIdParameter(1);
 tmp32_1 = parameterPointer->GetValue();
parameterPointer = mapsOfParameters.GetIdParameter(2);
 tmp32_1 = parameterPointer->GetValue();
parameterPointer = mapsOfParameters.GetIdParameter(3);
 tmp32_1 = parameterPointer->GetValue();
*/
/*
tmp32_256 = mapsOfParameters.getMbValue(256);
tmp32_257 = mapsOfParameters.getMbValue(257);
tmp32_258 = mapsOfParameters.getMbValue(258);
tmp32_259 = mapsOfParameters.getMbValue(259);
tmp32_260 = mapsOfParameters.getMbValue(260);
tmp32_261 = mapsOfParameters.getMbValue(261);
tmp32_262 = mapsOfParameters.getMbValue(262);
tmp32_263 = mapsOfParameters.getMbValue(263);

tmp_mbSize = mapsOfParameters.mbMapSize();
tmp_idSize = mapsOfParameters.idMapSize();


tmp32_1 = mapsOfParameters.getIdValue(1);
tmp32_2 = mapsOfParameters.getIdValue(2);
tmp32_3 = mapsOfParameters.getIdValue(3);
tmp32_4 = mapsOfParameters.getIdValue(4);
tmp32_5 = mapsOfParameters.getIdValue(5);
tmp32_6 = mapsOfParameters.getIdValue(6);
*/
/*
tmp32_1 = calibratedParameter.getValue();
calibratedParameter.setCalibrating();
calibratedParameter.startEditing();
calibratedParameter.incValueHandler(1, 0);
calibratedParameter.endEditing();
tmp32_2 = calibratedParameter.getEditingValue();
tmp32_3 = calibratedParameter.getValue();
*/


uint16_t i, size;

menuEngine.setMenuValue("A");
menuEngine.findAvailableElements(menuEngine.getMenuValue());
  printf("After find %s  items in vector = %d \n", menuEngine.getMenuValue(), menuEngine.getCountOfAvailableElements() );
size = menuEngine.getCountOfAvailableElements();
if (size)
{
  for (i=0; i<size; i++){
    printf("find Item id= %d  ,", menuEngine.getAvailableElement(i)->getId() );
    printf("menu = %s  \n", menuEngine.getAvailableElement(i)->getMenu() );
  }
}
printf("\n");

menuEngine.setMenuValue("B.1");
menuEngine.findAvailableElements(menuEngine.getMenuValue());
  printf("After find %s  items in vector = %d \n", menuEngine.getMenuValue(), menuEngine.getCountOfAvailableElements() );
size = menuEngine.getCountOfAvailableElements();
if (size)
{
  for (i=0; i<size; i++){
    printf("find Item id= %d  ,", menuEngine.getAvailableElement(i)->getId() );
    printf("menu = %s  \n", menuEngine.getAvailableElement(i)->getMenu() );
  }
}
printf("\n");

menuEngine.setMenuValue("B.2");
menuEngine.findAvailableElements(menuEngine.getMenuValue());
  printf("After find %s  items in vector = %d \n", menuEngine.getMenuValue(), menuEngine.getCountOfAvailableElements() );
size = menuEngine.getCountOfAvailableElements();
if (size)
{
  for (i=0; i<size; i++){
    printf("find Item id= %d  ,", menuEngine.getAvailableElement(i)->getId() );
    printf("menu = %s  \n", menuEngine.getAvailableElement(i)->getMenu() );
  }
}
printf("\n");

menuEngine.setMenuValue("B");
menuEngine.findAvailableElements(menuEngine.getMenuValue());
  printf("After find %s  items in vector = %d \n", menuEngine.getMenuValue(), menuEngine.getCountOfAvailableElements() );
size = menuEngine.getCountOfAvailableElements();
if (size)
{
  for (i=0; i<size; i++){
    printf("  find Item id= %d  ,", menuEngine.getAvailableElement(i)->getId() );
    printf("menu = %s  \n", menuEngine.getAvailableElement(i)->getMenu() );
  }
}
  
  pwm.setValue (0.2);
  pwm.setValue (0.4);
  pwm.setValue (0.6);
  

//tmp32_5 =0;
	while (1)
 {
	GPIOA->BSRR = 1;
	GPIOA->BRR = 1;
	current.putSample(adc_1.getSample());
	voltage.putSample(adc_1.getSample());
	voltageRms.putSample(adc_1.getSample());
//  tmp32_6 = RTC_GetDivider();
//  if (tmp32_6>tmp32_5) 
//  { tmp32_5 = tmp32_6; }
 }
}

