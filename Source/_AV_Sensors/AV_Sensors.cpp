#include "_AV_Sensors.h"
#include "stm32f10x.h"

namespace src{

//------------------------------------------------------------------------------------------------------------------------ 
// Class AnalogSensor
//------------------------------------------------------------------------------------------------------------------------

// Конструктор без параметров
AnalogSensor::AnalogSensor ()
 {}
 
	 
// Конструктор с параметрами
AnalogSensor::AnalogSensor (float ts, float tf)
{
//	meanFilter.PutTsTf(float ts, float tf);
}
 
// Методы
inline	void AnalogSensor::GetMeanPu	(float &v)
{
}

	 
void AnalogSensor::PutCalibration	(uint16_t calibration)	// Положить калибровочный коэффициент
{}


//------------------------------------------------------------------------------------------------------------------------ 
// Class AnalogRmsSensor
//------------------------------------------------------------------------------------------------------------------------
 
// Constructor without parameters
AnalogRmsSensor::AnalogRmsSensor()
 {}


// Конструктор с параметрами
AnalogRmsSensor::AnalogRmsSensor (float ts, float tf)
{
	meanFilter.PutTsTf	(ts, tf);
	rmsFilter.PutTsTf		(ts, tf);
}

// Методы
inline	void AnalogRmsSensor::GetRmsV	(float &v)
{
	rmsFilter.GetRms(v);
}


inline	void AnalogRmsSensor::GetRmsPu	(float &v)
{
	rmsFilter.GetMean(v);
}

	 

}

