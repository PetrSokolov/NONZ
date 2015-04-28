//#####################################################################################
//	Файл				_Parameters.cpp
//	Название:		Классы настроечных параметров.
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

// Метод 
void MapsOfParameters::PutToMaps (Parameter& parameter) // Положить ссылку на объект в карты  
{
  idMap[parameter._id]        = &parameter;
  mbMap[parameter._modbusAdr] = &parameter;

  // Если параметр состоит из 2 регистров, инициализирую второй регистр модбас
  if((parameter._flags.size == 1) && (parameter._modbusAdr2)){
    mbMap[parameter._modbusAdr2] = &parameter;
  }
}

/*
Этот метод определяется в пользовательском файле "Parameters_User.cpp"
void MapsOfParameters::MapsInit()
{
}
*/