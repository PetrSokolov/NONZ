#include "_FXP_Math.h"
//#include "stm32f10x.h"

namespace src{

//int64_t	Iq::_val64;
	int8_t	Iq::_overflow_mul=0;

// Class Iq

// Constructor without parameters
// Iq a;
 Iq::Iq () : val(0)
  { _point=10; }

 
// Constructor with parameters
// Iq a(_IQ12(0.01));
// a = _IQ12(0.01);
 Iq::Iq (long x) : val(x)
  { }


// Конструктор с параметрами (мантисса, показатель по основанию 2)
// Iq a(0.01, 12);
 Iq::Iq (float x, uint8_t y) : /*val(x),*/ _point(y)
  { val=x*(1<<_point); }

 
// Конструктор с параметрами (мантисса, показатель по основанию 2)
 Iq::Iq (long x, uint8_t y) : val(x<<y), _point(y)
  { }


//copy constructor:
 Iq::Iq (const Iq & x) : val(x.val)
  { }


	
// Перегрузка операторов. Реализация операций с фиксированной точкой

//assignment operators: (object +/-= object)
//	Iq Iq::operator = (const Iq & x)
//  { val = x.val;  return *this;}
 
    //arithmetic operators:

	
	

	
	
	
	
	
	
	
	
	
// --- Процедура извлечения квадратного корня -----------
unsigned int sqrt_newton(long L)
{
          long temp, divv; 
          unsigned long rslt = (unsigned long)L; 
          if (L <= 0) return 0;
              else if (L & 0xFFFF0000L)
                     if (L & 0xFF000000L)
                          divv = 0x3FFF; 
                      else
                          divv = 0x3FF; 
               else
                   if (L & 0x0FF00L) divv = 0x3F; 
                        else divv = (L > 4) ? 0x7 : L; 

          while (1)
          {
              temp = L/divv + divv; 
               divv = temp >> 1; 
               divv += temp & 1; 
               if (rslt > divv) rslt = (unsigned)divv; 
               else 
               {
              if (1/rslt == rslt-1 && 1%rslt==0) rslt--; 
              return rslt; 
              }
          }
}


}