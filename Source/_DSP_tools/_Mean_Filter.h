#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 
	 

// Базовый класс Цифрового фильтра второго порядка
class MeanFilter
{
	public:
		inline	void PutSample	(uint16_t adc_sample);
		inline	void GetMean		(float &mean) { mean = _mean_value; }
						void PutTsTf		(float ts, float tf);
	protected:
		float				_sample;					// Отсчет сигнала
		float				_mean_value;			// Усредненное фильтром значение сигнала
		float				_mean_y_1;				// Компонента фильтра MEAN	(в формате фиксированной точки)
		float				_mean_z_1;				// Компонента фильтра MEAN	(в формате фиксированной точки)
		float				_tfm;							// Постоянная времени фильтра MEAN
		float				_ts;							// Период дискретизациии сигнала
		float				_tmp;							// Переменная для промежуточных расчетов
};


}	// namespace src
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP

