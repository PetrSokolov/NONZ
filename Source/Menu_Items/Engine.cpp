//#####################################################################################
//	Файл				Engine.cpp
//	Название:		Движок меню. На базе автомата состояний.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 22 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

//#include "..\Menu_Items\_Engine.h"

#include "stm32f10x.h"
#include "_Engine.h"
#include "_Parameters.h"

using namespace src;


MenuEngine menuEngine;
//--------------------------------------------------------------------------------------------------------
// Метод PutToMenu
// Положить указатель на объект в вектор, содержащий все элементы меню
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::putToMenu (MenuItem* menuItem) // Положить ссылку на объект в карты  
{
  _menuIdVector.push_back( menuItem );
}


//=============================================================================================
// Метод findAvailableElements
// Производит поиск доступных элементов меню на данном уровне меню
//=============================================================================================
//findIndexMenuItems (vector<IMenuItem*> &resultVector, char* indexString)
void MenuEngine::findAvailableElements(vector<MenuItem*> &resultVector, char* indexString)
{
  uint16_t i, n;

  resultVector.clear();
  n = _menuIdVector.size();

  for (i=0; i < n; i++){
    if(strstr (_menuIdVector[i]->getMenu(),indexString))  // Символ найден
    {
      resultVector.push_back(_menuIdVector[i]);
    }
  }
}


//=============================================================================================
// Метод findAvailableElements
// Производит поиск доступных элементов меню на данном уровне меню
//=============================================================================================
void MenuEngine::findAvailableElements(char* indexString)
{
  uint16_t i, n;

  _availableElements.clear();
  n = _menuIdVector.size();

  for (i=0; i < n; i++){
    if(strstr (_menuIdVector[i]->getMenu(),indexString))  // Символ найден
    {
      _availableElements.push_back(_menuIdVector[i]);
    }
  }
}

//=============================================================================================
// Метод getCountOfAvailableElements
// Возвращает количество элементов на данном уровне
//=============================================================================================
uint16_t MenuEngine::getCountOfAvailableElements(void)
{
  return _availableElements.size();
}


//=============================================================================================
// Метод getAvailableElement
// Возвращает указатель на элемент меню на данном уровне. index[0..getCountOfAvailableElements]
//=============================================================================================
MenuItem*  MenuEngine::getAvailableElement(uint16_t index)
{
 return _availableElements[index];
}

