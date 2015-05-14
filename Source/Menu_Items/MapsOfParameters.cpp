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

#include "_Parameters.h"
#include "__Parameters_User.h"
#include "__MapsOfParameters.h"

#include "stdint.h"
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <algorithm>


using namespace src;
using namespace std;

//========================================================================================================
//                                        Класс MapsOfParameters
//========================================================================================================
  
//--------------------------------------------------------------------------------------------------------
// Метод PutToMaps
// Положить настроечный объект-параметр в карты idMap и mbMap по идентификатору и ModBus адресу
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
//void myfunction (int i) {  // function:
//  printf("foreach  element = %d", i);
//}
/*void findIndexString(pair<const uint16_t, Parameter*>& pair) // could be a class static method as well
{
  char* stringPosition;
  uint16_t stringLenth;
  
  printf("element id = %d,  ", pair.first);
  printf("Value = %#X \n", pair.second->getValue());

  stringLenth = strlen(pair.second->getMenu());

    printf("finding ""B"" at      %#X...\n", pair.second->getMenu());
  
  stringPosition = strstr (pair.second->getMenu(),"B.1");

    printf("symbolPosition =      %#X \n", stringPosition);
    printf("strlenth is           %d \n", stringLenth);
  
  if(stringPosition)  // Символ найден
  {
    printf("find element with B, id = %d, position = %#X \n", pair.first, stringPosition);
  }
    printf("\n");
}
*/

// Метод поиска элементов меню (параметров) по индексу. Формирует вектор с указателями на параметры-объекты, удовлетворяющие заданному уровню меню (index)
vector<Parameter> MapsOfParameters::findIndexMenuItems (string index)
{
  char* stringPosition;
  uint16_t stringLenth;
  uint16_t j, n;
  vector<Parameter> elements;
  vector<int> numbers;
  map<uint16_t, Parameter*>::iterator i;
  
  numbers.push_back(1);
  numbers.push_back(3);
  numbers.push_back(5);
  
//  for_each(_idMap.begin(), _idMap.end(), findIndexString);
  n = _idMap.size();
  i = _idMap.begin();
  for (j=0; j < n; j++){
    stringPosition = i->second->getMenu();

    printf("element id = %d,  ", i->first);
    printf("Value = %#X \n", i->second->getValue());

  stringLenth = strlen(i->second->getMenu());

    printf("finding ""B.1"" at      %#X...\n", i->second->getMenu());
  
  stringPosition = strstr (i->second->getMenu(),"B.1");

    printf("symbolPosition =      %#X \n", stringPosition);
    printf("strlenth is           %d \n", stringLenth);
  
  if(stringPosition)  // Символ найден
  {
    printf("find element with B, id = %d, position = %#X \n", i->first, stringPosition);
  }
    printf("\n");
    
    i++;
  }
  

/*  elements.push_back(par1);
  printf(" added par1 \n");
  elements.push_back(par2);
  printf(" added par2 \n");
  elements.push_back(pwmDeathTime);
  printf(" added pwmDeathTime \n");
*/
  return elements;
}


//--------------------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------------------
void MapsOfParameters::init()
{
  // Инициализация параметров (сделать из FRAM)
//  pwmValue.setValue(12);
//  pwmDeathTime.setValue(12);

}

