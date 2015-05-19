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
#include "math.h"
#include <map>
#include <vector>
#include <string>
//#include "__MapsOfParameters.h"
//#include "__Parameters_User.h"
#include "_Engine.h"

#ifdef __cplusplus
 extern "C" {
#endif 

#define BYTES_TO_LONG(st,ml) (((uint32_t)st<<16)|(ml&0xFFFF))
   
using namespace std;


namespace src{	 

//====================================================================================================
  // Список типов параметров
enum {
  TYPE_SINGLE_REGISTER,
  TYPE_DOUBLE_REGISTER,
  TYPE_FLOAT
};
 

//=================================================================================================
//  Класс, определяющий элемент меню 
//=================================================================================================
class MenuItem{
  public:
    virtual inline uint16_t getId     (void) { return 0; }       // Возвращает id параметра
    virtual inline char*    getMenu   (void) { return 0; }       // Возвращает указатель на индекс меню
    virtual inline char*    getText   (void) { return 0; }       // Возвращает указатель на текст меню

     uint16_t  _id;        // Идентификатор параметра. Для привязки к FRAM
     char*     _menu;      // Идентификатор меню.
     char*     _text;      // Тестовая информация
};



//=================================================================================================
//  Класс, определяющий группу настроечных параметров
//  Пустой элемент меню, работает только на отображение
//=================================================================================================
class GroupParameter : public MenuItem{
  public:
      // Конструктор с параметрами    
    GroupParameter( uint16_t   id,
                    char*      menu,
                    char*      text,
                    MenuEngine& menuEngine
                  );

    // Переопределение методов интерфейса  IMenuItem
    virtual inline uint16_t getId     (void)           { return _id; }         // Возвращает id параметра
    virtual inline char*    getMenu   (void)           { return _menu; }       // Возвращает указатель на индекс меню
    virtual inline char*    getText   (void)           { return _text; }       // Возвращает указатель на текст меню
};
 
// Класс настроечного параметра. В ПЗУ хранится только текст (const char*)
class Parameter : public MenuItem{
  public:
    // Конструктор без параметров
    Parameter() { }
  
    // Конструктор с параметрами
    Parameter(  uint16_t   id,
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
             );

   // Конструктор с параметрами. Без записи в карты
    Parameter(  uint16_t   id,
                char*      menu,
                char*      text,
                uint16_t   modbusAdr,
                uint16_t   value,
                uint16_t   rw,
                uint16_t   min,
                uint16_t   max,
                uint16_t   user,
                uint16_t   def
             );

// Интерфейс работы с данными. В зависимости от типа данных.
// Объявляются стандартные методы (виртуально). Определяются при инициализации, в зависимости от размера параметра (16 или 32 бит)
  // Методы, возвращающие значение параметра
  virtual inline uint32_t getValue  (void)           { return _value; }      // Возвращает значение параметра
  virtual inline uint32_t getValue1 (void)           { return _value; }      // Возвращает значение параметра1. Заготовка для параметра из 2 регистров
  virtual inline uint32_t getValue2 (void)           { return _value; }      // Возвращает значение параметра2. Заготовка для параметра из 2 регистров
  virtual inline float    getValueFlt(void)          { return _value; }      // Возвращает значение параметра в формате float.  Заготовка для параметра, содержащего расчитавыемый float
  virtual inline void     setValue  (uint32_t value) { _value = value; }     // Устанавливает значение параметра
  virtual inline void     setValue1 (uint16_t value) { _value = value; }     // Устанавливает значение параметра. Заготовка для параметра из 2 регистров
  virtual inline void     setValue2 (uint16_t value) { _value = value; }     // Устанавливает значение параметра. Заготовка для параметра из 2 регистров
  // Методы, возвращающие атрибуты
  virtual inline uint16_t getType   (void)           { return _flags.type; } // Возвращает тип параметра
  virtual inline uint16_t getMbAdr  (void)           { return _modbusAdr; }  // Возвращает модбас адрес параметра
  virtual inline uint16_t getMbAdr2 (void)           { return _modbusAdr; }  // Возвращает дополнительный модбас адрес параметра. Заготовка для параметра из 2 регистров
  virtual inline uint32_t getMin    (void)           { return _min; }        // Возвращает минимальное значение параметра
  virtual inline uint32_t getMax    (void)           { return _max; }        // Возвращает максимальное значение параметра

  // Переопределение методов интерфейса  IMenuItem
    virtual inline uint16_t getId     (void)           { return _id; }         // Возвращает id параметра
    virtual inline char*    getMenu   (void)           { return _menu; }       // Возвращает указатель на индекс меню
    virtual inline char*    getText   (void)           { return _text; }       // Возвращает указатель на текст меню

  // Методы, используемые при редактировании параметра через меню
  virtual inline void startEditing  (void)           { editingValue = _value; }     // Начало редактирования параметра
  virtual inline void endEditing    (void)           { setValue ( editingValue ); } // Завершение редактирования параметра. С последующей командой на сохранение.
  virtual inline void exitEditing   (void)           { }                     // Выход из редактирования параметра (без сохранения результата)
  virtual        void incValueHandler(uint16_t x, uint8_t power);            // Инкремент параметра
  virtual        void decValueHandler(uint16_t x, uint8_t power);            // Декремент параметра
  virtual        void enterHandler  (void);                                  // Обработчик ввода при редактировании параметра
  virtual inline uint32_t getEditingValue(void)      { return editingValue; }// Выход из редактирования параметра (без сохранения результата)


  // Перегрузка операторов
  inline Parameter & operator = (const Parameter & x);

  // Поле данных
  protected:
//     uint16_t  _id;        // Идентификатор параметра. Для привязки к FRAM
//     char*     _menu;      // Идентификатор меню.
//     char*     _text;      // Тестовая информация

     uint16_t  _modbusAdr; // Адрес модбас
     uint16_t  _value;     // Значение параметра
     uint16_t  _min;       // Минимальное значение
     uint16_t  _max;       // Максимальное значение
     uint16_t  _def;       // Значение по умолчанию
     static uint32_t  editingValue;     // Переменная, используемая при редактировании параметра
     
     struct {
       uint8_t type  :5;   // Тип параметра. Определяется в конструкторе. 0-Parameter, 1-Parameter2reg, 2-ParameterFlt, 3-резерв
       uint8_t rw    :1;   // Разрешение на запись
       uint8_t user  :1;   // Доступ в режиме пользователя
       }_flags;            // Флаги дополнительных атрибутов

};

//---------------------------------------------------------------------------
// Перегрузка операторов. Может потребоваться при работе с контейнерами.
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Operator: "="
//---------------------------------------------------------------------------
inline Parameter & Parameter :: operator = (const Parameter & x)
{
//  setId   ( x.getId()   );
//  setMenu ( x.getMenu() );
//  setText ( x.getText() );
  _id        = x._id;
  _menu      = x._menu;
  _text      = x._text;

  _modbusAdr = x._modbusAdr;
  _value     = x._value;
  _min       = x._min;
  _max       = x._max;
  _def       = x._def;
  
  _flags.rw     = x._flags.rw;
  _flags.type   = x._flags.type;
  _flags.user   = x._flags.user;

   return *this;
}


//---------------------------------------------------------------------------
// Operators: "==", "!=", "<", ">", "<=", ">=", "&&", "||"
//---------------------------------------------------------------------------
inline bool operator == (Parameter &x, Parameter& y)     { return (x.getValue() == y.getValue()); }
inline bool operator != (Parameter &x, Parameter& y)     { return (x.getValue() != y.getValue()); }
inline bool operator <  (Parameter &x, Parameter& y)     { return (x.getValue() <  y.getValue()); }
inline bool operator >  (Parameter &x, Parameter& y)     { return (x.getValue() >  y.getValue()); }
inline bool operator <= (Parameter &x, Parameter& y)     { return (x.getValue() <= y.getValue()); }
inline bool operator >= (Parameter &x, Parameter& y)     { return (x.getValue() >= y.getValue()); }
inline bool operator && (Parameter &x, Parameter& y)     { return (x.getValue() && y.getValue()); }
inline bool operator || (Parameter &x, Parameter& y)     { return (x.getValue() || y.getValue()); }




//=================================================================================================
//  Класс, определяющий настроечный параметр, состоящий из 2 регистров (size = 1 - 32 бит)
//=================================================================================================
class Parameter2reg : public Parameter{
public:
    // Конструктор без параметров
    Parameter2reg(); //{ _flags.type  = TYPE_DOUBLE_REGISTER; };

  
    // Конструктор с параметрами
    Parameter2reg(  uint16_t   id,
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
                );

   // Конструктор с параметрами. Без записи в карты
    Parameter2reg(  uint16_t   id,
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
                );

  // Поле с дополнительными параметрами              
  uint16_t   _modbusAdr2;
  uint16_t   _value2;
  uint16_t   _min2;
  uint16_t   _max2;
  uint16_t   _def2;


// Переопределение методов под данный тип параметра

  // Методы, возвращающие значение параметра
 virtual inline uint32_t getValue  (void)           { return BYTES_TO_LONG(_value2, _value); }   // Возвращает значение параметра
 virtual inline uint32_t getValue1 (void)           { return _value; }                           // Возвращает значение параметра.
 virtual inline uint32_t getValue2 (void)           { return _value2; }                          // Возвращает значение параметра.
 virtual inline void     setValue  (uint32_t value) { _value2 = value >> 16; _value = value & 0xFFFF; } // Устанавливает значение параметра.
 virtual inline void     setValue1 (uint16_t value) { _value  = value; }                         // Устанавливает значение параметра.
 virtual inline void     setValue2 (uint16_t value) { _value2 = value; }                         // Устанавливает значение параметра.
 virtual inline uint16_t getMbAdr2 (void)           { return _modbusAdr2; }                      // Возвращает дополнительный модбас адрес параметра. Заготовка для 32бит параметра
 virtual inline uint32_t getMin    (void)           { return BYTES_TO_LONG(_min2, _min); }       // Возвращает минимальное значение параметра
 virtual inline uint32_t getMax    (void)           { return BYTES_TO_LONG(_max2, _max); }       // Возвращает максимальное значение параметра

  // Методы, используемые при редактировании параметра через меню
  virtual inline void startEditing  (void)           { editingValue = BYTES_TO_LONG(_value2, _value); }     // Начало редактирования параметра
  virtual inline void endEditing    (void)           { setValue ( editingValue ); } // Завершение редактирования параметра. С последующей командой на сохранение.
  virtual inline void exitEditing   (void)           { }                     // Выход из редактирования параметра (без сохранения результата)

};



//=================================================================================================
//  Класс, определяющий настроечный параметр c расчитаным float значением
//  Зная value и pow, расчитывается значение float
//=================================================================================================
class ParameterFlt : public Parameter{
public:
    // Конструктор без параметров
    ParameterFlt() { };

  
    // Конструктор с параметрами
    ParameterFlt(  uint16_t   id,
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
//                MapsOfParameters& mapsOfParameters,
                MenuEngine& menuEngine
                );

                // Конструктор с параметрами. Без записи в карты
    ParameterFlt(  uint16_t   id,
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
                );

  float   _valueFlt;  // Значение в формате float
  int16_t _power;     // Степень. Для перевода из int в float

// Переопределение методов под данный тип параметра
  virtual inline float getValueFlt (void)           { return _valueFlt; }                               // Возвращает значение параметра.
  virtual inline void  setValue    (uint32_t value) { _value = value; _valueFlt = (float)value * pow(10.0, (int)_power); } // Устанавливает значение параметра.

  // Методы, используемые при редактировании параметра через меню
  virtual inline void endEditing    (void)           { setValue ( editingValue ); } // Завершение редактирования параметра. С последующей командой на сохранение.
};



//=================================================================================================
//  Декоратор класса Parameter.
//  Содержит в себе декорируемый объект.
//=================================================================================================
class Decorator : public Parameter {
public:
    // Конструктор без параметров
    Decorator () { };

    // Конструктор с параметрами
    Decorator ( Parameter* parameter )
    {
	    _parameter = parameter;
    }

protected:
  Parameter*  _parameter;       // Декорируемый объект
};


//=================================================================================================
//  Декоратор класса.
//  Конкретная реализация Декоратора. Переопределение методов класса.
//  Изменяет поведение объекта под Функция калибровки по записи "1"
//=================================================================================================
class DecoratorCalibrated : public Decorator {
public:

  // Конструктор с параметрами
  DecoratorCalibrated ( /*MapsOfParameters& mapsOfParameters,*/ MenuEngine& menuEngine, Parameter* parameter );

// Переопределение методов под данный тип параметра

  // Методы, возвращающие значение параметра
  virtual inline uint32_t getValue  (void)           { return _parameter->getValue(); }    // Возвращает значение параметра
  virtual inline uint32_t getValue1 (void)           { return _parameter->getValue1(); }   // Возвращает значение параметра1. Заготовка для параметра из 2 регистров
  virtual inline uint32_t getValue2 (void)           { return _parameter->getValue2(); }   // Возвращает значение параметра2. Заготовка для параметра из 2 регистров
  virtual inline float    getValueFlt(void)          { return _parameter->getValueFlt(); } // Возвращает значение параметра в формате float.  Заготовка для параметра, содержащего расчитавыемый float
  virtual inline void     setValue  (uint32_t value) { _parameter->setValue  (value); }    // Устанавливает значение параметра
  virtual inline void     setValue1 (uint16_t value) { _parameter->setValue1 (value); }    // Устанавливает значение параметра. Заготовка для параметра из 2 регистров
  virtual inline void     setValue2 (uint16_t value) { _parameter->setValue2 (value); }    // Устанавливает значение параметра. Заготовка для параметра из 2 регистров

  // Методы, возвращающие атрибуты
  virtual inline uint16_t getType   (void)           { return _parameter->getType(); }     // Возвращает тип параметра
  virtual inline uint16_t getMbAdr  (void)           { return _parameter->getMbAdr(); }    // Возвращает модбас адрес параметра
  virtual inline uint16_t getMbAdr2 (void)           { return _parameter->getMbAdr2(); }   // Возвращает дополнительный модбас адрес параметра. Заготовка для параметра из 2 регистров
  virtual inline uint32_t getMin    (void)           { return _parameter->getMin(); }      // Возвращает минимальное значение параметра
  virtual inline uint32_t getMax    (void)           { return _parameter->getMax(); }      // Возвращает максимальное значение параметра

    // Методы интерфейса  IMenuItem
  virtual inline uint16_t getId     (void)           { return _parameter->getId(); }         // Возвращает id параметра
  virtual inline char*    getMenu   (void)           { return _parameter->getMenu(); }       // Возвращает указатель на индекс меню
  virtual inline char*    getText   (void)           { return _parameter->getText(); }       // Возвращает указатель на текст меню

  // Методы, используемые при редактировании параметра через меню
  virtual inline void startEditing  (void)           { _parameter->startEditing(); }       // Начало редактирования параметра
  virtual inline void endEditing    (void)           { _parameter->endEditing();   }       // Завершение редактирования параметра. С последующей командой на сохранение.
  virtual inline void exitEditing   (void)           { _parameter->exitEditing();  }       // Выход из редактирования параметра (без сохранения результата)
  virtual 		 void incValueHandler(uint16_t x, uint8_t power);                          // Инкремент параметра
  virtual 		 void decValueHandler(uint16_t x, uint8_t power);                          // Декремент параметра
  virtual        void enterHandler  (void);                                                // Обработчик ввода при редактировании параметра
  virtual inline uint32_t getEditingValue(void)      { return _parameter->getEditingValue(); }// 



  // Методы класса DecoratorCalibrated
          inline void setCalibrating(void)           { _calibrating = 1; }                 // Включить режим калибровки
          inline void clrCalibrating(void)           { _calibrating = 0; }                 // Выключить режим калибровки
private:

// Данные класса DecoratorCalibrated
  float    _autocalibratingValue;                                                          // Калибровочный коэффициент. Вычисленный автоматически.
  float    _calibratingValue;                                                              // Значение расчитанного калибровочного коэффициента
  uint8_t  _calibrating;                                                                   // Статус калибровки. 0-нет, 1-включена
};

}	// namespace src

#ifdef __cplusplus
};
#endif
#endif	//define PARAMETERS_H



