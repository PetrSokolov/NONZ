#include "_Parameters.h"
#include "__Parameters_User.h"

using namespace src;
using namespace std;


//--------------------------------------------------------------------------------------------------------
// Обработчик декремента при редактировании параметра
//--------------------------------------------------------------------------------------------------------
/*void Parameter::decValueHandler(uint16_t x, uint8_t power)
{
 if(editingValue - x >= _min) {editingValue -= x;} else { editingValue = _max; } 
}


//--------------------------------------------------------------------------------------------------------
// Обработчик инкремента при редактировании параметра
//--------------------------------------------------------------------------------------------------------
void Parameter::incValueHandler (uint16_t x, uint8_t power)
{
 if(editingValue + x <= _max) {editingValue += x;} else { editingValue = _min; } 
}



//--------------------------------------------------------------------------------------------------------
// Обработчик ввода при редактировании параметра
//--------------------------------------------------------------------------------------------------------

void Parameter::enterHandler (void)
{
 if(this == &par1)
   { Обработчик для этого параметра }
}

*/


//========================================================================================================
//          DecoratorCalibrated
// Декоратор параметра. Калибруемый
//========================================================================================================

void DecoratorCalibrated::enterHandler  (void)
{
  if(_parameter->getEditingValue() == 1){
    _calibrating =1;
  }
   else{
    _parameter->enterHandler(); 
   }
     
}



