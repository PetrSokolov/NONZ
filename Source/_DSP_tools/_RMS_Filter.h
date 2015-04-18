#ifndef RMS_FILTER_H
#define RMS_FILTER_H
#include "stdint.h"
#include "math.h"

#include "_FXP_Math.h"
#include "_Mean_Filter.h"

#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 

	
// Базовый класс Цифрового фильтра второго порядка
	class RmsFilter : public MeanFilter
{
	public:
		inline	void GetRms				(Iq &rms);
	protected:
// Отнаследовать от MEAN
//		Iq				_sample;						// Отсчет сигнала
//		Iq				_mean_y_1;					// Компонента фильтра MEAN
//		Iq				_mean_z_1;					// Компонента фильтра MEAN
//		Iq				_tfm;								// Постоянная времени фильтра MEAN
//		Iq				_ts;								// Период дискретизациии сигнала
};



}	// namespace src
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP

