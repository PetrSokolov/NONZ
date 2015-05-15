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
  
    void findAvailableElements(); // Формирует список доступных элементов меню. На текущем уровне.
    inline void  setMenuValue(char* m) { _m = m; }
    inline char* getMenuValue(void)    { return _m; }

	protected:
    MapsOfParameters* _mapsOfParameters;      // Агрегация объекта, содержащего карты
    vector<IMeniItem*> _availableElements;    // Список доступных элементов меню. На текущем уровне.
		char*             _m;	                    // Состояние автомата меню
		int				        _im;                   	// Индекс листига текущего меню

};
	
}	// namespace src
#ifdef __cplusplus
}
#endif
#endif	//define MENU_ENGINE_H




