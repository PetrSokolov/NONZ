//#####################################################################################
//	Файл				Engine.h
//	Название:		Движок меню. На базе автомата состояний.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 23 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#ifndef MENU_ENGINE_H
#define MENU_ENGINE_H

#include "_Parameters.h"
#include <vector>

#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 

class MenuEngine{
	public:
    // Конструктор с параметрами
    MenuEngine(MapsOfParameters* mapsOfParameters)  { _mapsOfParameters = mapsOfParameters; }
  
	protected:
    void              getAvailableElements(); // Формирует список доступных элементов меню. На текущем уровне.
    MapsOfParameters* _mapsOfParameters;      // Агрегация объекта, содержащего карты
    vector<Parameter> _availableElements;     // Список доступных элементов меню. На текущем уровне.
		long long       	M;	                    // Состояние автомата меню
		int				        IM;                   	// Индекс листига текущего меню

};
	
}	// namespace src
#ifdef __cplusplus
}
#endif
#endif	//define MENU_ENGINE_H




