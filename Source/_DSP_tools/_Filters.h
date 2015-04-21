//#####################################################################################
//	File:			_Filters.h
//	Title:		Filters library
//	Author:		Бабкин.П.А
//	Ver  | dd-mmm-yyyy |        Who 		| Description of changes
//	=====|=============|================|==============================================
// 	 1.0 | 2015 apr 21 | Babkin	P.A	 		| Original Release.
// 	-----|-------------|----------------|----------------------------------------------
//	Comment:
//#####################################################################################

#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

#include "stdint.h"
#include "math.h"


#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 
	 

//======================================================================================================================== 
// Mean - Фильтр второго порядка
//======================================================================================================================== 
//	Методы:
//	PutSample - Положить в фильтр отсчет АЦП и обработать. Аргумент adc_sample - значение АЦП. Выполняется каждый период дискретизации
//	GetMean		- Получить значение на выходе фильтра. Аргументу mean присваивается значение. Либо возвращается, если нет аргумена.
//	PutTsTf		- Установить период дискретизации (ts) и постоянную времени фильтра (tf). ts и tf задаются в секундах (0.0002 сек и тп)
	
class MeanFilter
{
	public:
		inline	virtual void 	PutSample	(uint16_t adc_sample);
		inline					void 	GetMean		(float &mean);
		inline					float	GetMean		(void);
										void 	PutTsTf		(float ts, float tf);
	protected:
		float				_sample;					// Отсчет сигнала
		float				_mean_value;			// Усредненное фильтром значение сигнала
		float				_mean_y_1;				// Компонента фильтра MEAN	(в формате фиксированной точки)
		float				_mean_z_1;				// Компонента фильтра MEAN	(в формате фиксированной точки)
		float				_tfm;							// Постоянная времени фильтра MEAN
		float				_ts;							// Период дискретизациии сигнала
		float				_tmp;							// Переменная для промежуточных расчетов
};


//======================================================================================================================== 
// RMS Mean - Фильтр второго порядка
//======================================================================================================================== 
//	Методы:
//	PutSample - Положить в фильтр отсчет АЦП и обработать. Аргумент adc_sample - значение АЦП. Выполняется каждый период дискретизации
//	GetMean		- Получить значение на выходе фильтра. Аргументу mean присваивается значение.
//	PutTsTf		- Установить период дискретизации (ts) и постоянную времени фильтра (tf). ts и tf задаются в секундах (0.0002 сек и тп)

class RmsFilter : public MeanFilter
{
	inline	void PutSample	(uint16_t adc_sample);
};


//======================================================================================================================== 
//	Inline методы
//======================================================================================================================== 
//	Mean - Фильтр второго порядка
//-------------------------------------------------------------------------------------------------------------------
//	PutSample - Положить в фильтр отсчет АЦП и обработать. Аргумент adc_sample - значение АЦП. Выполняется каждый период дискретизации
//-------------------------------------------------------------------------------------------------------------------
inline void MeanFilter::PutSample		(uint16_t adc_sample)
{
	_sample = adc_sample;
	_mean_y_1 = _mean_y_1 + (_sample		- _mean_y_1)*_tfm;
	_mean_z_1 = _mean_z_1 + (_mean_y_1 - _mean_z_1)*_tfm;
	_mean_value = _mean_z_1;
}


//-------------------------------------------------------------------------------------------------------------------
//	GetMean		- Получить значение на выходе фильтра. Аргументу mean присваивается значение.
//-------------------------------------------------------------------------------------------------------------------
inline	void MeanFilter::GetMean		(float &mean)
{
	mean = _mean_value;
}

inline	float MeanFilter::GetMean		(void)
{
	return _mean_value;
}

//-------------------------------------------------------------------------------------------------------------------
//	Rms - Фильтр второго порядка
//-------------------------------------------------------------------------------------------------------------------
//	PutSample - Положить в фильтр отсчет АЦП и обработать. Аргумент adc_sample - значение АЦП. Выполняется каждый период дискретизации
//-------------------------------------------------------------------------------------------------------------------
inline void RmsFilter::PutSample		(uint16_t adc_sample)
{
	_sample = adc_sample;
	_mean_y_1 = _mean_y_1 + (_sample * _sample	- _mean_y_1)*_tfm;
	_mean_z_1 = _mean_z_1 + (_mean_y_1 - _mean_z_1)*_tfm;
	_mean_value = sqrt( _mean_z_1 );
}


}	// namespace src
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP

