#ifndef MAIN_HPP
#define MAIN_HPP

//#include ".\Menu_Items\_Parameters.h"

#ifdef __cplusplus
 extern "C" {
#endif 

// Прототип функции-вектора прерывания
void DMA1_Channel4_IRQHandler(void);
void USART1_IRQHandler(void);
	 
/*using namespace src;

//extern Parameter* parameterPointer;
extern       Parameter par1( 1,    // _id        // Идентификатор параметра. Для привязки к FRAM
                      1,    // _menu      // Идентификатор меню.
                      256,  // _modbusAdr	// Адрес модбас
                      "Элемент меню 1", //_text      // Тестовая информация
                      123,  // _value     // Значение параметра
                      1,    // _rw        // Разрешение на запись
                      0,    // _min       // Минимальное значение
                      100,  // _max       // Максимальное значение
                      1,    // _user      // Доступ в режиме пользователя
                      12),  // _def       // Значение по умолчанию
                par2( 2,    // _id        // Идентификатор параметра. Для привязки к FRAM
                      2,    // _menu      // Идентификатор меню.
                      257,  // _modbusAdr	// Адрес модбас
                      "Элемент меню 2", //_text      // Тестовая информация
                      321,  // _value     // Значение параметра
                      1,    // _rw        // Разрешение на запись
                      0,    // _min       // Минимальное значение
                      100,  // _max       // Максимальное значение
                      1,    // _user      // Доступ в режиме пользователя
                      21);  // _def       // Значение по умолчанию
*/
#ifdef __cplusplus
}
#endif
#endif	//MAIN_HPP
