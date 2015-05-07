#ifndef ADC_HPP
#define ADC_HPP
#include "stdint.h"
//#include "IADC_GetSample.hpp"

#ifdef __cplusplus
 extern "C" {
#endif 
	 
namespace src{	 
	 
#define countof(a)   (sizeof(a) / sizeof(*(a)))	

// Базовый класс АЦП
class BaseAdc{
	protected:
		uint16_t	_convertedSamples;	// Количество конвертированных данных
	public:
	  virtual void 			getSample(uint16_t n, uint16_t &sample) =0;// Чистая виртуальная функция, ее нужно определить в производном классе
	  virtual uint16_t	getSample() =0;// Чистая виртуальная функция, ее нужно определить в производном классе
//		virtual void EOC(void) =0;	// Чистая виртуальная функция, ее нужно определить в производном классе
		virtual void Init(void) =0;		// Чистая виртуальная функция, ее нужно определить в производном классе
};

//-------------------------------------------------------------------------------------------------------
// Производный класс АЦП1
//-------------------------------------------------------------------------------------------------------
class Adc_1 : public BaseAdc{
	protected:
		uint16_t	_convertedBuf[2];	// Буфер для конвертированных данных
	public:
		Adc_1();
		virtual inline void			getSample(uint16_t n, uint16_t &sample) {sample = _convertedBuf[n];}
		virtual inline uint16_t	getSample() {return _convertedBuf[0];}
		virtual void Init(void);
};
//-------------------------------------------------------------------------------------------------------
// Производный класс АЦП2
//-------------------------------------------------------------------------------------------------------
class Adc_3 : public BaseAdc{
	protected:
		uint16_t	_convertedBuf[3];	// Буфер для конвертированных данных
	public:
		Adc_3();
		virtual inline void     getSample(uint16_t n, uint16_t &sample)	{sample = _convertedBuf[n];}
		virtual inline uint16_t	getSample()													{return _convertedBuf[0];}
		virtual void Init(void);
};
							
} // namespace
#ifdef __cplusplus
};
#endif
#endif	//define ADC_HPP
