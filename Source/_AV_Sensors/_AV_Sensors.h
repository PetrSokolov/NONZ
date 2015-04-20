#ifndef AV_SENSORS_HPP
#define AV_SENSORS_HPP
#include "stdint.h"

#include "_Mean_Filter.h"
#include "_Rms_Filter.h"

#ifdef __cplusplus
 extern "C" {
#endif 


namespace src{	 

// Базовый класс силовых датчиков
class AnalogSensor{
	public:
		// Конструкторы
		AnalogSensor();
		AnalogSensor (float ts, float tf);
		
		// Данные
		MeanFilter	meanFilter;		// Фильтр Mean
		
		// Методы
		inline	void GetMeanPu	(float &v);
						void PutCalibration	(uint16_t calibration);	// Положить калибровочный коэффициент
//						void PutTf_Ts	(float ts, float tf);					// Положить период дискретизации и постоянную времени фильтра
	protected:
		float			_rms_value;					// Переменная составляющая сигнала
		float			_mean_value;				// Постоянная составляющая сигнала
		float			_calibration_value;	// Калибровочный коэффициент
	
};


//-------------------------------------------------------------------------------------------------------------------------
// Производный класс силовых датчиков напряжения
// Имеет члены класса - фильтры Mean и RMS в виде соответствующих объектов
//-------------------------------------------------------------------------------------------------------------------------
class AnalogRmsSensor : public AnalogSensor {
	public:
		// Конструкторы
		AnalogRmsSensor();
		AnalogRmsSensor(float ts, float tf);

		// Данные
		RmsFilter		rmsFilter;		// Фильтр RMS

		// Методы
		inline	void GetRmsV			(float &v);
		inline	void GetRmsPu		(float &v);
	protected:
		float	_rms_value;	// RMS значение сигнала
};

}
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP
