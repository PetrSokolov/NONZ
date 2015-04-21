//#####################################################################################
//	File:			Filters.cpp
//	Title:		Filters library
//	Author:		Бабкин.П.А
//	Ver  | dd-mmm-yyyy |        Who 		| Description of changes
//	=====|=============|================|==============================================
// 	 1.0 | 2015 apr 21 | Babkin	P.A	 		| Original Release.
// 	-----|-------------|----------------|----------------------------------------------
//	Comment:
//#####################################################################################

#include "_Filters.h"

using namespace src;

//-------------------------------------------------------------------------------------------------------------------
// Inline методы описаны непосредственно в заголовочном файле
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//	PutTsTf		- Установить период дискретизации (ts) и постоянную времени фильтра (tf). ts и tf задаются в секундах (0.0002 сек и тп)
//-------------------------------------------------------------------------------------------------------------------
void MeanFilter::PutTsTf		(float ts, float tf)
{
	_ts = ts;
	//_tfm=2*Ts/Tf - Перерасчет Tf в величину _tfm, используемую в фильтре с целью сократить дополнительные расчеты
	_tfm = (2*ts)/tf;
}

