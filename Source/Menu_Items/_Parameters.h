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


#ifdef __cplusplus
 extern "C" {
#endif 

namespace src{	 

  // Класс настроечного параметра. В ПЗУ хранится только текст (const char*)
class Parameter{
  public:
    Parameter( const uint16_t   id,
               const uint32_t   menu,
               const uint16_t   modbusAdr,
               const char*      text,
                     uint16_t   value,
               const uint16_t   rw,
               const uint16_t   min,
               const uint16_t   max,
               const uint16_t   user,
               const uint16_t   def
                 ) :
                    _id       (id),
                    _menu     (menu),
                    _modbusAdr(modbusAdr),
                    _text     (text),
                    _value    (value),
                    _rw       (rw),
                    _min      (min),
                    _max      (max),
                    _user     (user),
                    _def      (def)
                    {}
                      Описать параметр присваивания. Необходимо Для работы с контейнерами.
//  protected:
    const uint16_t  _id;        // Идентификатор параметра. Для привязки к FRAM
    const uint32_t  _menu;      // Идентификатор меню.
    const uint16_t  _modbusAdr;	// Адрес модбас
    const char*     _text;      // Тестовая информация
          uint16_t  _value;     // Значение параметра
    const uint16_t  _rw;        // Разрешение на запись
    const uint16_t  _min;       // Минимальное значение
    const uint16_t  _max;       // Максимальное значение
    const uint16_t  _user;      // Доступ в режиме пользователя
    const uint16_t  _def;       // Значение по умолчанию
};
	
}	// namespace src

#ifdef __cplusplus
};
#endif
#endif	//define PARAMETERS_H

	