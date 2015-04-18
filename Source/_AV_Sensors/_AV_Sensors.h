#ifndef AV_SENSORS_HPP
#define AV_SENSORS_HPP
#include "stdint.h"

#include "_FXP_Math.h"
#include "_Mean_Filter.h"
#include "_Rms_Filter.h"

#ifdef __cplusplus
 extern "C" {
#endif 


namespace src{	 

// Базовый класс силовых датчиков
class AvSensors{
	public:
		AvSensors();
		AvSensors (float ts, float tf);

		inline	void GetACValue	(Iq &v);
		inline	void GetDCValue	(Iq &v);
//		inline	virtual void PutSample			(uint16_t adc_sample);	// virtual - В производном классе можно поменять реализацию
//						virtual void PutCalibration	(uint16_t calibration);	// virtual - В производном классе можно поменять реализацию
	protected:
		Iq				_ac_value;					// Переменная составляющая сигнала
		Iq				_dc_value;					// Постоянная составляющая сигнала
		uint16_t	_calibration_value;	// Калибровочный коэффичиент
};


//-------------------------------------------------------------------------------------------------------------------------
// Производный класс силовых датчиков напряжения
// Имеет члены класса фильтров Mean и RMS в виде соответствующих объектов
//-------------------------------------------------------------------------------------------------------------------------
class Av_Rms_Sensors : public AvSensors {
	public:
		Av_Rms_Sensors();
		Av_Rms_Sensors(float ts, float tf);

		inline void GetRMSValue	(Iq &v);

		MeanFilter	meanFilter;		// Фильтр Mean
		RmsFilter		rmsFilter;		// Фильтр RMS
	protected:
		Iq	_rms_value;	// RMS значение сигнала
};

}
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP
