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
#include <map>

#include "__IControlCommands.h"


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace std;
   
namespace src{	 


//========================================================================================================
//                                   Интерфейс IMenuEngine
//========================================================================================================
class IMenuItem;

  //===========================================================================================
  //  Движок меню. 
  //  Осуществляет навингацию по объектам IMenuItem
  //  Агрегирует объект, содержащий карты параметров. (Потом убрать)
  //===========================================================================================
  class MenuEngine {
	public:
    // Конструктор без параметров
    MenuEngine()  {}
  
    // Методы работы с элементами меню
    void          putToMenu   (IMenuItem* menuItem);    // Положить в карту элемент
    void          findAvailableElements(vector<IMenuItem*> &resultVector, char* indexString);// Производит поиск доступных элементов меню на данном уровне меню
    void          findAvailableElements(char* indexString);                                  // Производит поиск доступных элементов меню на данном уровне меню
    uint16_t      getCountOfAvailableElements(void);   // Возвращает количество элементов на данном уровне
    IMenuItem*     getAvailableElement(uint16_t index);// Возвращает указатель на элемент меню на данном уровне. index[0..getCountOfAvailableElements]
    inline void   setMenuValue(char* m) { _m = m; }    // Устанавливает текущий уровень (сигнатуру) меню
    inline char*  getMenuValue(void)    { return _m; } // Возвращает текущий уровень (сигнатуру) меню

    // Методы навигации по элементам меню
    inline void     setIm (uint16_t im) { _im = im; }
    inline uint16_t getIm (void)        { return _im; }
           void     menuMoveDown (void);
           void     menuMoveUp (void);
           void     menuMoveForward (void);
           void     menuMoveBackward (void);
    
  
	protected:
    vector<IMenuItem*>  _availableElements;           // Список доступных элементов меню. На текущем уровне.
    vector<IMenuItem*>  _menuIdVector;                // Вектор, содержащий все элементы меню
		char*               _m;	                          // Текущее состояние (уровень) меню
		uint16_t            _im;                   	      // Индекс листига текущего меню
};

}	// namespace src

//extern src::MenuEngine menuEngine;

#ifdef __cplusplus
}
#endif
#endif	//define MENU_ENGINE_H




