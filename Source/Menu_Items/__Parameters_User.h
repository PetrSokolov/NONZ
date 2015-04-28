//#####################################################################################
//	Файл				_Parameters_User.h
//	Название:		Настроечные параметры.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 27 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#ifndef PARAMETERS_USER_H
#define PARAMETERS_USER_H

#include "stdint.h"
#include "_Parameters.h"


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace src;

extern Parameter par1, par2;
extern MapsOfParameters mapsOfParameters;
   
// }	// namespace src

#ifdef __cplusplus
};
#endif
#endif	//define PARAMETERS_USER_H

