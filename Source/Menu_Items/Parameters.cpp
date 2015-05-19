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
//#include "__Parameters_User.h"
//#include "_Engine.h"

//#include "stdint.h"
#include <stdio.h>
//#include <map>
//#include <vector>
//#include <string>
#include <algorithm>

using namespace src;
using namespace std;


uint32_t  Parameter::editingValue;    // Статическая переменная, используемая при редактировании параметра

//=================================================================================================
//                                     Класс GroupParameter
//  Класс, определяющий группу настроечных параметров
//  Пустой элемент меню, работает только на отображение
//=================================================================================================
  // Конструктор с параметрами    
  GroupParameter::GroupParameter( uint16_t   id,
                    char*      menu,
                    char*      text,
                    MenuEngine& menuEngine
                  )
                   { _id = id;
                     _menu = menu;
                     _text = text;
                     menuEngine.putToMenu(this);
                   }


//========================================================================================================
//                                        Класс Parameter
//========================================================================================================
  
//--------------------------------------------------------------------------------------------------------
// Parameter - Конструктор с параметрами
//--------------------------------------------------------------------------------------------------------
Parameter::Parameter(  uint16_t   id,
                char*      menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   value,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   max,
                uint16_t   user,
                uint16_t   def,
//                MapsOfParameters& mapsOfParameters,
                MenuEngine& menuEngine
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
//                      mapsOfParameters.putToMaps(this);
                      menuEngine.putToMenu(this);
                    }


//--------------------------------------------------------------------------------------------------------
// Parameter - Конструктор с параметрами. Без записи в карты
//--------------------------------------------------------------------------------------------------------
Parameter::Parameter(  uint16_t   id,
                char*      menu,
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

//void Parameter::enterHandler (void)
//{
//}

//========================================================================================================
//                                        Класс Parameter2reg
//========================================================================================================

// Конструктор без параметров
Parameter2reg::Parameter2reg() { _flags.type  = TYPE_DOUBLE_REGISTER; }
                    
//--------------------------------------------------------------------------------------------------------
// Parameter2reg - Конструктор с параметрами
//--------------------------------------------------------------------------------------------------------
Parameter2reg::Parameter2reg(  uint16_t   id,
                char*      menu,
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
//                MapsOfParameters& mapsOfParameters,
                MenuEngine& menuEngine
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
  //                mapsOfParameters.putToMaps(this);
                  menuEngine.putToMenu(this);
                }


//--------------------------------------------------------------------------------------------------------
// Parameter2reg - Конструктор с параметрами. Без записи в карты
//--------------------------------------------------------------------------------------------------------
Parameter2reg::Parameter2reg(  uint16_t   id,
                char*      menu,
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
                }


//========================================================================================================
//                                        Класс ParameterFlt
//========================================================================================================

// Конструктор с параметрами
ParameterFlt::ParameterFlt(  uint16_t   id,
                char*      menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   value,
                int16_t    power,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   max,
                uint16_t   user,
                uint16_t   def,
 //               MapsOfParameters& mapsOfParameters,
                MenuEngine& menuEngine
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
 //                 mapsOfParameters.putToMaps(this);
                  menuEngine.putToMenu(this);
                }
                

//--------------------------------------------------------------------------------------------------------
// ParameterFlt - Конструктор с параметрами. Без записи в карты
//--------------------------------------------------------------------------------------------------------
ParameterFlt::ParameterFlt(  uint16_t   id,
                char*      menu,
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
                }


				
//========================================================================================================
//                                        Декоратор класса DecoratorCalibrated
//  Изменяет поведение объекта под Функция калибровки по записи "1"
//========================================================================================================
 
  // Конструктор с параметрами
 DecoratorCalibrated::DecoratorCalibrated ( /*MapsOfParameters& mapsOfParameters,*/ MenuEngine& menuEngine, Parameter* parameter ) : Decorator( parameter )
  {
//    mapsOfParameters.putToMaps(this);
    menuEngine.putToMenu(this);
  }


