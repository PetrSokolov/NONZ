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
#include "_Engine.h"
#include <vector>
#include <stdio.h>

using namespace src;



//=====================================================================================
// Метод getAvailableElements
// Производит поиск доступных элементов меню на данном уровне
//=====================================================================================
void MenuEngine::findAvailableElements()
{
  uint16_t size, i;
  printf("Method findAvailableElements \n");
  printf("vector = %d \n", _availableElements.size() );
  
  _availableElements = _mapsOfParameters->findIndexMenuItems("B.1");
  
  size = _availableElements.size();
  printf("After find. IMeniItem vector = %d \n", size );
  
  for (i=0; i<size; i++){
    printf("find Item id= %d  ,", _availableElements[i]->getId() );
    printf("menu = %s  ,", _availableElements[i]->getMenu() );
    printf("text = %s \n", _availableElements[i]->getText() );
  }
   
  
}

