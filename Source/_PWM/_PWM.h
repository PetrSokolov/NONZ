//#####################################################################################
//	Файл				PWM.h
//	Название:		Движок меню. На базе автомата состояний.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд |     	Кто		 		| Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 22 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#ifndef PWM_H
#define PWM_H

#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 

//======================================================================================================================== 
// Pwm - генератор 3 фазного ШИМ
//======================================================================================================================== 
//	Методы:
//	setFrequency	- Установить частоту модуляции ШИМ
//	setDeathTime	- Установить мертвое время ШИМ
//	setValue			- Установить амплитуду сигнала (1-максамальный)
//	setBlock			- Установить/снять режим блокировки
//	init					- Инициализация. Имеет несколько реализаций под разное железо
	
class Pwm{
	public:
						void setFrequency (float frequency);
						void setDeathTime (float deathtime);
						void setValue 		(float value);
						void setBlock 		(float block);
		virtual	void Init			 		(void) =0;
		
	protected:
		uint16_t	_deathTime;			//	Мертвое время ШИМ. deathtime
		uint16_t	_frequency;			//	Частота модуляции ШИМ
		float 		_value;					//	Амплитуда
		uint16_t	_block;					//	Блокировка. Отключение ШИМ
		uint16_t	_timerPeriod;		//	Период таймера(ШИМ) [в отсчетах таймера]

		float 		_dutyCycle1;		//	Скважность канала 1 (текущая)
		float 		_dutyCycle2;		//	Скважность канала 2 (текущая)
		float 		_dutyCycle3;		//	Скважность канала 3 (текущая)
		uint16_t	_channel1Pulse;	//	Значение регистра сравнения CH1
		uint16_t	_channel2Pulse;	//	Значение регистра сравнения CH2
		uint16_t	_channel3Pulse;	//	Значение регистра сравнения CH3
		uint32_t	_clkFrequency;	//	Частота синхронизации таймера [Гц]. Расчитывается при инициализации.
};



//======================================================================================================================== 
// Pwm2phaseNONZ- генератор 2 фазного ШИМ для НО/НЗ
//======================================================================================================================== 
//	Методы:
//	init					- Инициализация. Реализация под железо НО/НЗ

class Pwm2phaseNONZ : public Pwm{
	public:
		void Init	(void);
};

}	// namespace src
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP
