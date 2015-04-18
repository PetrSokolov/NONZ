#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

#include "_FXP_Math.h"


#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 
	 

// Базовый класс Цифрового фильтра второго порядка
class MeanFilter
{
	public:
		inline	void PutSample		(uint32_t adc_sample);
		inline	void GetMean		(Iq &mean);
						void PutTsTf		(float ts, float tf);
	protected:
		Iq				_iqSample;					// Отсчет сигнала
		Iq				_iqMean_value;			// Усредненное фильтром значение сигнала
		Iq				_iqMean_y_1;				// Компонента фильтра MEAN	(в формате фиксированной точки)
		Iq				_iqMean_z_1;				// Компонента фильтра MEAN	(в формате фиксированной точки)
		int32_t		_y_1;								// Компонента фильтра MEAN	(в формате целого)
		int32_t		_z_1;								// Компонента фильтра MEAN	(в формате целого)
		Iq				_iqTfm;							// Постоянная времени фильтра MEAN
//		Iq				_iqTs;							// Период дискретизациии сигнала
		Iq				_iqTmp;							// Переменная для промежуточных расчетов
		int32_t		_tmp;								// Переменная для промежуточных расчетов
};


}	// namespace src
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP

