//#####################################################################################
//	Файл				_Parameters.cpp
//	Название:		Методы настроечных параметров.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 27 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#include "_Parameters.h"
#include "stdint.h"
#include <map>

using namespace src;
using namespace std;



// Конструктор без аргументов
//Parameter::Parameter() : _modbusAdr(0), _id(0), _text(0)
//{}
  
// Конструктор с аргументами
//Parameter::Parameter( const uint32_t modbusAdr, const uint32_t id, const char* text ) : _modbusAdr(modbusAdr), _id(id), _text(text)
//{}


uint32_t  Parameter::editingValue;     // Статическая переменная, используемая при редактировании параметра

  
//--------------------------------------------------------------------------------------------------------
// Метод PutToMaps
// Положить настроечный объект-параметр в карты idMap и mbMap по идентификатору и ModBus адресу
//--------------------------------------------------------------------------------------------------------
void  MapsOfParameters::putToMaps (Parameter& parameter) // Положить ссылку на объект в карты  
{
  idMap[parameter._id]        = &parameter;
  mbMap[parameter.getMbAdr()] = &parameter;

  // Если параметр состоит из 2 регистров, инициализирую второй регистр модбас
  if(parameter.getType() == 1) {
    mbMap[parameter.getMbAdr2()] = &parameter;
  }
}



//--------------------------------------------------------------------------------------------------------
// Метод GetMbParameter
// По адресу ModBus возвращает указатель на объект-параметр
//--------------------------------------------------------------------------------------------------------
Parameter*  MapsOfParameters::getMbParameter (uint16_t mbAdr)
{
  Parameter* parameterPointer;
  map<uint16_t, Parameter*>::iterator i;
  i = mbMap.find(mbAdr);
  if(i == mbMap.end()){
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
  i = idMap.find(id);
  if(i == idMap.end()){
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
  i = mbMap.find(mbAdr);
  if(i == mbMap.end()){
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
  i = idMap.find(id);
    if(i == idMap.end()){
      // Такого идентификатора не существует
      // Разобраться и вставить try - throw - catch
      return 0;
    }
    parameterPointer = (*i).second;
    return parameterPointer->getValue();
    
}

/*
Этот метод определяется в пользовательском файле "Parameters_User.cpp"
void  MapsOfParameters::MapsInit()
{
}
*/

