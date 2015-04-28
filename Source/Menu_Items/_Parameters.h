//#####################################################################################
//	Файл				_Parameters.h
//	Название:		Классы настроечных параметров.
//	Автор:			Бабкин.П.А
//	Вер. | гггг-ммм-дд | Внес изменения | Описание изменений
//	=====|=============|================|==============================================
// 	 1.0 | 2015 апр 27 | Бабкин П.А	 		| Первый релиз
// 	-----|-------------|----------------|----------------------------------------------
//#####################################################################################

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "stdint.h"
#include <map>


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace std;
   
namespace src{	 

//=================================================================================================
//  Класс, определяющий настроечный параметр
//=================================================================================================
 
// Класс настроечного параметра. В ПЗУ хранится только текст (const char*)
class Parameter{
  public:
    // Конструктор без параметров
    Parameter()
                    { 
                      _id          = 0;
                      _menu        = 0;
                      _text        = 0;
                      _modbusAdr   = 0;
                      _modbusAdr2  = 0;
                      _min         = 0;
                      _max         = 0;
                      _def         = 0;

                      _flags.rw    = 0;
                      _flags.size  = 0;
                      _flags.user  = 0;
                      _value.xy    = 0;
                    }
  
    // Конструктор с параметрами
    Parameter(  uint16_t   id,
                uint32_t   menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   modbusAdr2,
                uint16_t   value,
                uint16_t   size,
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
                      _modbusAdr2  = modbusAdr2;
                      _min         = min;
                      _max         = max;
                      _def         = def;

                      _flags.rw    = rw;
                      _flags.size  = size;
                      _flags.user  = user;
                      _value.xy    = value;
                    }
//  protected:
     uint16_t  _id;        // Идентификатор параметра. Для привязки к FRAM
     uint32_t  _menu;      // Идентификатор меню.
     char*     _text;      // Тестовая информация
     uint16_t  _modbusAdr; // Адрес модбас
     uint16_t  _modbusAdr2;// Адрес модбас. Дополнительный, если параметр 32 бита.
     uint16_t  _min;       // Минимальное значение
     uint16_t  _max;       // Максимальное значение
     uint16_t  _def;       // Значение по умолчанию
     
     union{
       uint16_t  x;        // Значение параметра (мл - один регистр)
       uint16_t  x_y[2];   // Значение параметра (ст + мл регистры)
       uint32_t  xy;       // Значение параметра ([ст:мл] из двух регистров)
     }_value;              // Значение параметра (объединение)

     struct {
       uint8_t size  :2;   // Размер параметра 0-16bit, 1-32bit, 3-резерв
       uint8_t rw    :1;   // Разрешение на запись
       uint8_t user  :1;   // Доступ в режиме пользователя
       }_flags;            // Флаги дополнительных атрибутов

    inline Parameter & operator = (const Parameter & x);

};

//---------------------------------------------------------------------------
// Перегрузка операторов. Может потребоваться при работе с контейнерами.
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Operator: "="
//---------------------------------------------------------------------------
inline Parameter & Parameter :: operator = (const Parameter & x)
{
  _id        = x._id;
  _menu      = x._menu;
  _modbusAdr = x._modbusAdr;
  _text      = x._text;
  _value     = x._value;
  _min       = x._min;
  _max       = x._max;
  _def       = x._def;
  
  _flags.rw     = x._flags.rw;
  _flags.size   = x._flags.size;
  _flags.user   = x._flags.user;

  _value.xy  = x._value.xy;
   return *this;
}


//---------------------------------------------------------------------------
// Operators: "==", "!=", "<", ">", "<=", ">=", "&&", "||"
//---------------------------------------------------------------------------
inline bool operator == (const Parameter &x, const Parameter& y)     { return (x._value.xy == y._value.xy); }
inline bool operator != (const Parameter &x, const Parameter& y)     { return (x._value.xy != y._value.xy); }
inline bool operator <  (const Parameter &x, const Parameter& y)     { return (x._value.xy <  y._value.xy); }
inline bool operator >  (const Parameter &x, const Parameter& y)     { return (x._value.xy >  y._value.xy); }
inline bool operator <= (const Parameter &x, const Parameter& y)     { return (x._value.xy <= y._value.xy); }
inline bool operator >= (const Parameter &x, const Parameter& y)     { return (x._value.xy >= y._value.xy); }
inline bool operator && (const Parameter &x, const Parameter& y)     { return (x._value.xy && y._value.xy); }
inline bool operator || (const Parameter &x, const Parameter& y)     { return (x._value.xy || y._value.xy); }




//====================================================================================================
//  Класс, определяющий организацию настроечных параметров и ModBus регистров. И работу с ними
//  Содержит 2 объекта класса MAP. map[id / Parameter*] и сформированую по ней map[mbAdr / Parameter*]
//  Метод PutToMaps прописывает объект-параметр в карты. И дальше все должно само работать.
//====================================================================================================

class MapsOfParameters{
  public:
    void PutToMaps (Parameter& parameter); // Положить ссылку на объект в карты
    void Init();                           // Инициализация карт
  
    map<uint16_t, Parameter*> idMap;       // Карта ассоциаций  id параметров    [id    / Parameter*]
    map<uint16_t, Parameter*> mbMap;       // Карта ассоциаций  ModBus регистров [mbAdr / Parameter*]
};

}	// namespace src

#ifdef __cplusplus
};
#endif
#endif	//define PARAMETERS_H

	