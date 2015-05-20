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

//#include "stm32f10x.h"
#include "_Engine.h"
#include "_Parameters.h"

using namespace src;


//MenuEngine menuEngine;
//--------------------------------------------------------------------------------------------------------
// Метод PutToMenu
// Положить указатель на объект в вектор, содержащий все элементы меню
//--------------------------------------------------------------------------------------------------------
void  MenuEngine::putToMenu (IMenuItem* menuItem) // Положить ссылку на объект в карты  
{
  _menuIdVector.push_back( menuItem );
}


//=============================================================================================
// Метод findAvailableElements
// Производит поиск доступных элементов меню на данном уровне меню
//=============================================================================================
//findIndexMenuItems (vector<IMenuItem*> &resultVector, char* indexString)
void MenuEngine::findAvailableElements(vector<IMenuItem*> &resultVector, char* indexString)
{
  uint16_t i, n;
  uint16_t lenthIndexString;
  char* string_found, *first_point, *last_point;

  resultVector.clear();
  n = _menuIdVector.size();
  lenthIndexString = strlen(indexString);

  for (i=0; i < n; i++){
    string_found = strstr (_menuIdVector[i]->getMenu(),indexString);
    if(string_found){  // Символ найден
      // Если после indexString есть точка, и она является последней, то это элемент текущего меню 
      first_point = strchr((string_found + lenthIndexString),'.');
      last_point = strrchr((string_found + lenthIndexString),'.');
      if( first_point && (first_point == last_point) ){
        resultVector.push_back(_menuIdVector[i]);
      }
    }
  }
}


//=============================================================================================
// Метод findAvailableElements
// Производит поиск доступных элементов меню на данном уровне меню
//=============================================================================================
void MenuEngine::findAvailableElements(char* indexString)
{
/*  uint16_t i, n;
  uint16_t lenthIndexString;
  char* string_found;

  _availableElements.clear();
  n = _menuIdVector.size();
  lenthIndexString = strlen(indexString);

  for (i=0; i < n; i++){
    string_found = strstr (_menuIdVector[i]->getMenu(),indexString);
    if(string_found)  // Символ найден
    {
      if( strchr((string_found + lenthIndexString),'.') == strrchr((string_found + lenthIndexString),'.') ){
        _availableElements.push_back(_menuIdVector[i]);
        printf("   element %s added\n", _menuIdVector[i]->getMenu());
      }
    }
  }*/
  findAvailableElements(_availableElements, indexString);
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
IMenuItem*  MenuEngine::getAvailableElement(uint16_t index)
{
 return _availableElements[index];
}

