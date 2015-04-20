//#include "stdint.h"
//#include "math.h"

#include "_Mean_Filter.h"

using namespace src;

// Положить новое значение в фильтр и обсчитать фильтр.
inline void MeanFilter::PutSample		(uint16_t adc_sample)
{
	// MEAN
	_sample = adc_sample;

 _mean_y_1 = _mean_y_1 + (_sample		- _mean_y_1)*_tfm;
 _mean_z_1 = _mean_z_1 + (_mean_y_1 - _mean_z_1)*_tfm;
 _mean_value = _mean_z_1;

}



// Установить значения частоты дискретизации(ts) и постоянной времени фильтра(tf)
void MeanFilter::PutTsTf		(float ts, float tf)
{
	_ts = ts;
	//_tfm=2*Ts/Tf - Перерасчет Tf в величину _tfm, используемую в фильтре с целью сократить дополнительные расчеты
	_tfm = (2*ts)/tf;
}
