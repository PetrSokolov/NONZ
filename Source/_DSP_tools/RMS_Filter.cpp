#include "_RMS_Filter.h"
#include "_Mean_Filter.h"

using namespace src;


inline	void RmsFilter::GetRms	(Iq &rms)
{
	rms = _iqMean_value;
}