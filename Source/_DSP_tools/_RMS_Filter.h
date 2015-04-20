#ifndef RMS_FILTER_H
#define RMS_FILTER_H
//#include "stdint.h"
//#include "math.h"

#include "_Mean_Filter.h"

#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 

	
// Базовый класс Цифрового фильтра второго порядка
class RmsFilter : public MeanFilter
{
	public:
		inline	void GetRms		(float &rms) { rms = _mean_value; }
	protected:
};



}	// namespace src
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP

