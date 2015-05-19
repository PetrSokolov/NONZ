//#####################################################################################
//	Файл				__MapsOfParameters.cpp
//	Название:		Карты настроечных параметров-объектов.
//                  Ассоциативные списки id-Parameter, ModBus-Parameter
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 май 14 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

//#include "_Parameters.h"
#include "__Parameters_User.h"
#include "__MapsOfParameters.h"

//#include "stdint.h"
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "_Parameters.h"

using namespace src;
using namespace std;


//========================================================================================================
//                                        Класс MapsOfParameters
//  Работает через интерфейс IMenuItem
//========================================================================================================
  
//--------------------------------------------------------------------------------------------------------
// Метод PutToMaps
// Положить указатель на настроечный объект-параметр в карты idMap и mbMap по идентификатору и ModBus адресу
//--------------------------------------------------------------------------------------------------------
void  MapsOfParameters::putToMaps (Parameter* parameter) // Положить ссылку на объект в карты  
{
  _idMap[parameter->getId()]    = parameter;
  _mbMap[parameter->getMbAdr()] = parameter;

  // Если параметр состоит из 2 регистров, инициализирую второй регистр модбас
  if(parameter->getType() == TYPE_DOUBLE_REGISTER) {
    _mbMap[parameter->getMbAdr2()] = parameter;
  }
}

/*
//--------------------------------------------------------------------------------------------------------
// Метод mbMapsSize
// Возвращает количество элементов в карте mbMap
//--------------------------------------------------------------------------------------------------------
uint16_t  MapsOfParameters::mbMapSize (void)
{
  return _mbMap.size();
}



//--------------------------------------------------------------------------------------------------------
// Метод idMapsSize
// Возвращает количество элементов в карте idMap
//--------------------------------------------------------------------------------------------------------
uint16_t  MapsOfParameters::idMapSize (void)
{
  return _idMap.size();
}



//--------------------------------------------------------------------------------------------------------
// Метод GetMbParameter
// По адресу ModBus возвращает указатель на объект-параметр
//--------------------------------------------------------------------------------------------------------
Parameter*  MapsOfParameters::getMbParameter (uint16_t mbAdr)
{
  Parameter* parameterPointer;
  map<uint16_t, Parameter*>::iterator i;
  i = _mbMap.find(mbAdr);
  if(i == _mbMap.end()){
    // Такого адреса нет в таблице
    parameterPointer = 0;
  }
   else{ parameterPointer = (*i).second; }
  return parameterPointer;
}



//--------------------------------------------------------------------------------------------------------
// Метод GetIdParameter
// По идентификатору ID возвращает указатель на объект-параметр
//--------------------------------------------------------------------------------------------------------
Parameter*  MapsOfParameters::getIdParameter (uint16_t id)    
{
  Parameter* parameterPointer;
  map<uint16_t, Parameter*>::iterator i;
  i = _idMap.find(id);
  if(i == _idMap.end()){
    // Такого адреса нет в таблице
    parameterPointer = 0;
  }
   else{ parameterPointer = (*i).second; }
  return parameterPointer;
}



//--------------------------------------------------------------------------------------------------------
// Метод GetMbValue
// По адресу ModBus возвращает значение параметра (заданного регистра регистра)
//--------------------------------------------------------------------------------------------------------
uint16_t  MapsOfParameters::getMbValue     (uint16_t mbAdr)
{
  Parameter* parameterPointer;
  map<uint16_t, Parameter*>::iterator i;
  i = _mbMap.find(mbAdr);
  if(i == _mbMap.end()){
    // Такого идентификатора не существует
    // Разобраться и вставить try - throw - catch
    return 0;
  }
  parameterPointer = (*i).second;
  // Если параметр состоит из 1 регистра, возвращаю значение _value. Иначе возвращаю либо _value, либо _value2
  if(parameterPointer->getType  () == 0){
   return parameterPointer->getValue();
  }
  else{
    if (mbAdr == parameterPointer->getMbAdr()){ // Первый регистр
      return parameterPointer->getValue1();
    }
    else{ return parameterPointer->getValue2(); } 
   }
  
}


//--------------------------------------------------------------------------------------------------------
// Метод GetIdParameter
// По идентификатору ID возвращает значение параметра
//--------------------------------------------------------------------------------------------------------
uint32_t  MapsOfParameters::getIdValue     (uint16_t id)
{
  Parameter* parameterPointer;
  map<uint16_t, Parameter*>::iterator i;
  i = _idMap.find(id);
    if(i == _idMap.end()){
      // Такого идентификатора не существует
      // Разобраться и вставить try - throw - catch
      return 0;
    }
    parameterPointer = (*i).second;
    return parameterPointer->getValue();
    
}



//--------------------------------------------------------------------------------------------------------
// Методы поиска в контейнерах
// Ищет элементы, содержащие индекс меню index (пока так)
//--------------------------------------------------------------------------------------------------------

// Метод поиска элементов меню (параметров) по индексу. Формирует вектор с указателями на параметры-объекты, удовлетворяющие заданному уровню меню (indexString)
void MapsOfParameters::findIndexMenuItems (vector<IMenuItem*> &resultVector, char* indexString)
{
//  char* stringPosition;
  uint16_t i, n;
//  vector<IMenuItem*> elements;

  resultVector.clear();
//  n = _menuIdVector.size();

  for (i=0; i < n; i++){

//    stringPosition = strstr (_menuIdVector[i]->getMenu(),indexString);
    if(strstr (_menuIdVector[i]->getMenu(),indexString))  // Символ найден
    {
      resultVector.push_back(_menuIdVector[i]);
//      printf("find element with B.1, id = %d, position = %#X \n", _menuIdVector[i]->getId(), (unsigned int)stringPosition);
    }
//    printf("\n");
  }

//  printf("After find. IMenuItem elements = %d \n", elements.size() );
//  return elements;
}


//--------------------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------------------
void MapsOfParameters::init()
{
  // Инициализация параметров (сделать из FRAM)
//  pwmValue.setValue(12);
//  pwmDeathTime.setValue(12);

}*/

