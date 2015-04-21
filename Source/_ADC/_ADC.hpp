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
class CSingleADC{
	protected:
		uint16_t	_convertedSamples;	// Количество конвертированных данных
	public:
	  virtual void GetSample(uint16_t n, uint16_t &sample) =0;// Чистая виртуальная функция, ее нужно определить в производном классе
//		virtual void EOC(void) =0;	// Чистая виртуальная функция, ее нужно определить в производном классе
		virtual void Init(void) =0;		// Чистая виртуальная функция, ее нужно определить в производном классе
};

//-------------------------------------------------------------------------------------------------------
// Производный класс АЦП1(интерфейс).
//-------------------------------------------------------------------------------------------------------
class CADC_type1 : public CSingleADC{
	protected:
		uint16_t	_convertedBuf[2];	// Буфер для конвертированных данных
	public:
		CADC_type1();
		inline void GetSample(uint16_t n, uint16_t &sample) {sample = _convertedBuf[n];}
		void Init(void);
};
//-------------------------------------------------------------------------------------------------------
// Производный класс АЦП2(интерфейс).
//-------------------------------------------------------------------------------------------------------
class CADC_type2 : public CSingleADC{
	protected:
		uint16_t	_convertedBuf[3];	// Буфер для конвертированных данных
	public:
		CADC_type2();
		inline void GetSample(uint16_t n, uint16_t &sample) {sample = _convertedBuf[n];}
		void Init(void);
};
							
} // namespace
#ifdef __cplusplus
};
#endif
#endif	//define ADC_HPP
