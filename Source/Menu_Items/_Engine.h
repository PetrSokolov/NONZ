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

#include "stdint.h"
#include <stdio.h>
#include <vector>

//#include "__MapsOfParameters.h"


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace std;
   
namespace src{	 

class CTmp{
  public:
    int c;
}; 


//========================================================================================================
//                                   Интерфейс IMenuEngine
//========================================================================================================
class MenuItem;
class IMenuEngine{
  public:
    virtual void  putToMenu   (MenuItem* menuItem)=0;
};



  //===========================================================================================
  //  Движок меню. 
  //  Осуществляет навингацию по объектам IMenuItem
  //  Агрегирует объект, содержащий карты параметров. (Потом убрать)
  //===========================================================================================
  class MenuEngine : public IMenuEngine {
	public:
    // Конструктор с параметрами
//    MenuEngine(MapsOfParameters* mapsOfParameters)  { _mapsOfParameters = mapsOfParameters; }
    // Конструктор без параметров
    MenuEngine()  {}
  
    virtual void  putToMenu   (MenuItem* menuItem);   // Возвращает указатель на текст меню
    void          findAvailableElements(vector<MenuItem*> &resultVector, char* indexString); // Производит поиск доступных элементов меню на данном уровне меню
    void          findAvailableElements(char* indexString);                                  // Производит поиск доступных элементов меню на данном уровне меню
    uint16_t      getCountOfAvailableElements(void);  // Возвращает количество элементов на данном уровне
    MenuItem*     getAvailableElement(uint16_t index);// Возвращает указатель на элемент меню на данном уровне. index[0..getCountOfAvailableElements]
    inline void   setMenuValue(char* m) { _m = m; }   // Устанавливает текущий уровень (сигнатуру) меню
    inline char*  getMenuValue(void)    { return _m; }// Возвращает текущий уровень (сигнатуру) меню

	protected:
//    MapsOfParameters*   _mapsOfParameters;            // Агрегация объекта, содержащего карты
    vector<MenuItem*>  _availableElements;           // Список доступных элементов меню. На текущем уровне.
    vector<MenuItem*>  _menuIdVector;                // Вектор, содержащий все элементы меню
		char*              _m;	                          // Состояние автомата меню
//		int				          _im;                   	      // Индекс листига текущего меню
};

}	// namespace src

extern src::MenuEngine menuEngine;

#ifdef __cplusplus
}
#endif
#endif	//define MENU_ENGINE_H




