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


uint32_t  Parameter::editingValue;    // Статическая переменная, используемая при редактировании параметра


//========================================================================================================
//                                        Класс MapsOfParameters
//========================================================================================================
  
//--------------------------------------------------------------------------------------------------------
// Метод PutToMaps
// Положить настроечный объект-параметр в карты idMap и mbMap по идентификатору и ModBus адресу
//--------------------------------------------------------------------------------------------------------
void  MapsOfParameters::putToMaps (Parameter* parameter) // Положить ссылку на объект в карты  
{
  idMap[parameter->_id]        = parameter;
  mbMap[parameter->getMbAdr()] = parameter;

  // Если параметр состоит из 2 регистров, инициализирую второй регистр модбас
  if(parameter->getType() == TYPE_DOUBLE_REGISTER) {
    mbMap[parameter->getMbAdr2()] = parameter;
  }
/*  idMap[parameter._id]        = &parameter;
  mbMap[parameter.getMbAdr()] = &parameter;

  // Если параметр состоит из 2 регистров, инициализирую второй регистр модбас
  if(parameter.getType() == 1) {
    mbMap[parameter.getMbAdr2()] = &parameter;
  }*/
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


void MapsOfParameters::init()
{
  // Инициализация параметров (сделать из FRAM)
//  pwmValue.setValue(12);
//  pwmDeathTime.setValue(12);

}


//========================================================================================================
//                                        Класс Parameter
//========================================================================================================
  
//--------------------------------------------------------------------------------------------------------
// Parameter - Конструктор с параметрами
//--------------------------------------------------------------------------------------------------------
Parameter::Parameter(  uint16_t   id,
                uint32_t   menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   value,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   max,
                uint16_t   user,
                uint16_t   def,
                MapsOfParameters& mapsOfParameters
                 )
                    { 
                      _id          = id;
                      _menu        = menu;
                      _text        = text;
                      _modbusAdr   = modbusAdr;
                      _value       = value;
                      _min         = min;
                      _max         = max;
                      _def         = def;

                      _flags.rw    = rw;
                      _flags.type  = TYPE_SINGLE_REGISTER;
                      _flags.user  = user;
                      mapsOfParameters.putToMaps(this);
                    }


//--------------------------------------------------------------------------------------------------------
// Parameter - Конструктор с параметрами. Без записи в карты
//--------------------------------------------------------------------------------------------------------
Parameter::Parameter(  uint16_t   id,
                uint32_t   menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   value,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   max,
                uint16_t   user,
                uint16_t   def
                 )
                    { 
                      _id          = id;
                      _menu        = menu;
                      _text        = text;
                      _modbusAdr   = modbusAdr;
                      _value       = value;
                      _min         = min;
                      _max         = max;
                      _def         = def;

                      _flags.rw    = rw;
                      _flags.type  = TYPE_SINGLE_REGISTER;
                      _flags.user  = user;
                    }
//--------------------------------------------------------------------------------------------------------
// Обработчик ввода при редактировании параметра
// Определяется в файле Parameters_User.cpp
//--------------------------------------------------------------------------------------------------------
/*
void Parameter::enterHandler (void)
{
}*/

//========================================================================================================
//                                        Класс Parameter2reg
//========================================================================================================

// Конструктор без параметров
Parameter2reg::Parameter2reg() { _flags.type  = TYPE_DOUBLE_REGISTER; };
                    
//--------------------------------------------------------------------------------------------------------
// Parameter2reg - Конструктор с параметрами
//--------------------------------------------------------------------------------------------------------
Parameter2reg::Parameter2reg(  uint16_t   id,
                uint32_t   menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   modbusAdr2,
                uint16_t   value,
                uint16_t   value2,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   min2,
                uint16_t   max,
                uint16_t   max2,
                uint16_t   user,
                uint16_t   def,
                uint16_t   def2,
                MapsOfParameters& mapsOfParameters
                ):
    Parameter(     id,
                   menu,
                   text,
                   modbusAdr,
                   value,
                   rw,
                   min,
                   max,
                   user,
                   def,
                   mapsOfParameters
                )
                { _flags.type = TYPE_DOUBLE_REGISTER;
                  _modbusAdr2 = modbusAdr2;
                  _value2 = value2;
                  _min2 = min2;
                  _max2 = max2;
                  _def2 = def2;
                };


//--------------------------------------------------------------------------------------------------------
// Parameter2reg - Конструктор с параметрами. Без записи в карты
//--------------------------------------------------------------------------------------------------------
Parameter2reg::Parameter2reg(  uint16_t   id,
                uint32_t   menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   modbusAdr2,
                uint16_t   value,
                uint16_t   value2,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   min2,
                uint16_t   max,
                uint16_t   max2,
                uint16_t   user,
                uint16_t   def,
                uint16_t   def2
                ):
    Parameter(     id,
                   menu,
                   text,
                   modbusAdr,
                   value,
                   rw,
                   min,
                   max,
                   user,
                   def
                )
                { _flags.type = TYPE_DOUBLE_REGISTER;
                  _modbusAdr2 = modbusAdr2;
                  _value2 = value2;
                  _min2 = min2;
                  _max2 = max2;
                  _def2 = def2;
                };


//========================================================================================================
//                                        Класс ParameterFlt
//========================================================================================================

// Конструктор с параметрами
ParameterFlt::ParameterFlt(  uint16_t   id,
                uint32_t   menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   value,
                int16_t    power,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   max,
                uint16_t   user,
                uint16_t   def,
                MapsOfParameters& mapsOfParameters
                ):
    Parameter(     id,
                   menu,
                   text,
                   modbusAdr,
                   value,
                   rw,
                   min,
                   max,
                   user,
                   def,
                   mapsOfParameters
                )
                { _flags.type = TYPE_FLOAT;
                  _power = power;
                };
                

//--------------------------------------------------------------------------------------------------------
// ParameterFlt - Конструктор с параметрами. Без записи в карты
//--------------------------------------------------------------------------------------------------------
ParameterFlt::ParameterFlt(  uint16_t   id,
                uint32_t   menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   value,
                int16_t    power,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   max,
                uint16_t   user,
                uint16_t   def
                ):
    Parameter(     id,
                   menu,
                   text,
                   modbusAdr,
                   value,
                   rw,
                   min,
                   max,
                   user,
                   def
                )
                { _flags.type = TYPE_FLOAT;
                  _power = power;
                };

//========================================================================================================
            
                