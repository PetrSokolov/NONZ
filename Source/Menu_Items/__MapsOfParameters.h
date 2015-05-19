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

#ifndef MAPSOFPARAMETERS_USER_H
#define MAPSOFPARAMETERS_USER_H

#include "stdint.h"
#include <map>


#ifdef __cplusplus
 extern "C" {
#endif 

using namespace std;
   
namespace src{	



//========================================================================================================
//                                   Интерфейс IMapsOfParameters
//========================================================================================================
class Parameter;
class IMapsOfParameters{
  public:
    virtual void  putToMaps   (Parameter* parameter)=0;
};

  
//====================================================================================================
//  Класс, определяющий организацию настроечных параметров и ModBus регистров. И работу с ними
//  Содержит 2 объекта класса MAP. map[id / Parameter*] и сформированую по ней map[mbAdr / Parameter*]
//  Метод PutToMaps прописывает объект-параметр в карты. И дальше все должно само работать.
//====================================================================================================
class MapsOfParameters : public IMapsOfParameters{
  public:

    virtual void putToMaps (Parameter* parameter); // Положить указатель на объект в карты параметров

  // Методы атрибутов контейнеров
/*    uint16_t   mbMapSize      (void);           // Возвращает количество элементов в карте mbMap
    uint16_t   idMapSize      (void);           // Возвращает количество элементов в карте idMap

  // Методы значений контейнеров
    Parameter* getMbParameter (uint16_t mbAdr); // По адресу ModBus возвращает указатель на параметр
    Parameter* getIdParameter (uint16_t id);    // По идентификатору ID возвращает указатель на параметр
    uint16_t   getMbValue     (uint16_t mbAdr); // По адресу ModBus возвращает значение параметра (заданного регистра регистра)
    uint32_t   getIdValue     (uint16_t id);    // По идентификатору ID возвращает значение параметра

  // Методы поиска в контейнерах
  // Поиск и формирования вектора из элементов меню, в которых содержится индекс меню indexString.
   // vector<IMenuItem*> //void findIndexMenuItems (vector<IMenuItem*> &vec, char* indexString);
  
    void init();                                // Инициализация карт
*/
  protected:
    map<uint16_t, Parameter*> _idMap;       // Карта ассоциаций  id параметров    [id    / Parameter*]
    map<uint16_t, Parameter*> _mbMap;       // Карта ассоциаций  ModBus регистров [mbAdr / Parameter*]
};  
  
}
   
#ifdef __cplusplus
};
#endif
#endif	//define MAPSOFPARAMETERS_USER_H

