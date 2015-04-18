#include "_AV_Sensors.h"
#include "_FXP_Math.h"
#include "stm32f10x.h"

namespace src{

//------------------------------------------------------------------------------------------------------------------------ 
// Class AvSensors
//------------------------------------------------------------------------------------------------------------------------

// Конструктор без параметров
AvSensors::AvSensors ()
 {}
 
	 
// Конструктор с параметрами
AvSensors::AvSensors (float ts, float tf)
 {}
 

inline void AvSensors::GetACValue	(Iq &v)
 { v=_ac_value; }


inline void AvSensors::GetDCValue	(Iq &v)
 { v=_dc_value; }

//------------------------------------------------------------------------------------------------------------------------ 
// Class Av_Rms_Sensors
//------------------------------------------------------------------------------------------------------------------------
 
// Constructor without parameters
Av_Rms_Sensors::Av_Rms_Sensors()
 {}

	 
// Constructor with parameters
Av_Rms_Sensors::Av_Rms_Sensors(float ts, float tf) : AvSensors(ts, tf)
{
 meanFilter.PutTsTf	(ts, tf);
}

	 
inline void Av_Rms_Sensors::GetRMSValue	(Iq &v)
{
 v=_rms_value; 
}


}

