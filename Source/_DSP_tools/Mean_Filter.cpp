//#include "stdint.h"
//#include "math.h"

#include "_Mean_Filter.h"

//*****************************************************************************************************************
// Автор: Бабкин П.А
// 
// Дата 2015.04.19
//*****************************************************************************************************************

using namespace src;

// Положить новое значение в фильтр и обсчитать фильтр.
inline void MeanFilter::PutSample		(uint32_t adc_sample)
{
	// MEAN
	// Перевод в формат iqN[PU]. 0xFFF(ADC)->0.999[PU]
	if (_iqSample._point<=12)	{
		_iqSample.val = adc_sample >> (12 - _iqSample._point );
	}
	else {
		_iqSample.val = adc_sample >> ( _iqSample._point - 12 );
	}

	_tmp = adc_sample - _y_1;
	_iqTmp = _iqTfm;
	_iqTmp *= _tmp;
	_iqTmp += _iqMean_y_1;
	_iqMean_y_1 = _iqTmp;
	_y_1 = _iqMean_y_1.val >> _iqMean_y_1._point;
	
	_tmp = _y_1 - _z_1;
	_iqTmp = _iqTfm;
	_iqTmp *= _tmp;
	_iqTmp += _iqMean_z_1;
	_iqMean_z_1 = _iqTmp;
	_z_1 = _iqMean_z_1.val >> _iqMean_z_1._point;

}


// Возвращает результат фильтрации
inline void MeanFilter::GetMean		(Iq &mean)
{
 mean = _iqMean_value;
}


// Установить значения частоты дискретизации(ts) и постоянной времени фильтра(tf)
void MeanFilter::PutTsTf		(float ts, float tf)
{
//	_iqTs.val = ts*(1<<_iqTs._point);

	// *(1<<_point) второй раз, так как _tfm в фильтре будет умножаться на величину без *(1<<_point)
	// таким образом из околонулевого _tfm получается более существенная величина
	//_tfm=2*Ts/Tf
	tf = (2*ts)/tf;
	_iqTfm.val = tf*(1<<_iqTfm._point)*(1<<_iqTfm._point);

}
