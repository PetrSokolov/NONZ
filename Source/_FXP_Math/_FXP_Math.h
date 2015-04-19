#ifndef FXP_MATH_H
#define FXP_MATH_H
#include "stdint.h"
#include "math.h"

#ifdef __cplusplus
 extern "C" {
#endif 
//*****************************************************************************************************************
// Автор: Бабкин П.А
// Математика с фиксированной точкой
// Дата 2015.04.19
//*****************************************************************************************************************

#define		GLOBALQ				10
	 
namespace src{	 

extern unsigned int sqrt_newton(long L);

class Iq {
	public:
		int8_t _point;	// Положение фиксированной точки [бит]
		//constructors:
    Iq ();// : val(0);// { _point=10; }
    Iq (long x);// : val(x) { }
    Iq (float x, uint8_t y);// : val(x), _point(y) { }
    Iq (long x, uint8_t y);// : val(x), _point(y) { }

    //copy constructor:
    Iq (const Iq & x);// : val(x.val) { }

    //assignment operators: (object +/-= object)
    inline Iq & operator = (const Iq & x);

    //arithmetic operators:
		inline Iq & operator	+= (const Iq	&x);
	  inline Iq & operator	+= (long	 		&x);
    inline Iq & operator	-= (const	Iq	&x);
    inline Iq & operator	-= (long		 	&x);
    inline Iq & operator	*= (const Iq	&x);
    inline Iq & operator	*= (long			&x);
    inline Iq & operator	/= (const Iq	&x);
    inline Iq & operator	/= (long			&x);
//    inline Iq & operator	/= (float		&x);//				{ val=x*(1<<_point);//x;/*_val64=val; _val64<<=GLOBALQ; _val64/= x; val=_val64;			return *this;*/ }

    //bitwise operators:
    inline Iq & operator &= (const long &x);
    inline Iq & operator |= (const long &x);
    inline Iq & operator ^= (const long &x);

    long val;
		
		// Methods
		inline int32_t integer() { return val>>_point;}

	private:
//		/*static*/ int64_t _val64;	// static убран из за возможных сбоев _val64 в прерываании
		static int8_t _overflow_mul;
};


//---------------------------------------------------------------------------
// inline описываются непосредственно в заголовочном файле
//---------------------------------------------------------------------------
// Operators: "*", "*="
//---------------------------------------------------------------------------
inline Iq operator * (const Iq &x, const Iq &y)
{
   Iq temp;
   temp.val = (x.val * y.val)>>x._point;
   return temp;
}

inline Iq & Iq :: operator *= (const Iq &x)
{
   val = (val * x.val)>>_point;
   return *this;
}

inline Iq & Iq :: operator *= (long	&x)
{
   val *= x;
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "/", "/="
//---------------------------------------------------------------------------
inline Iq operator / (const Iq &x, const Iq &y)
{
   Iq temp;
//   temp.val = _IQdiv(x.val, y.val);
	 temp.val=(x.val<<x._point)/y.val;
   return temp;
}

inline Iq & Iq :: operator /= (const Iq &x)
{
//   val = _IQdiv(val, x.val);
	 val=(val<<_point)/x.val;
   return *this;
}

inline Iq & Iq :: operator /= (long	&x)
{
   val /= x;
   return *this;
}

//inline Iq & Iq :: operator /= (float	&x)
//{
//   val /= x;
//   return *this;
//}
//---------------------------------------------------------------------------
// Operator: "="
//---------------------------------------------------------------------------
inline Iq & Iq :: operator = (const Iq & x)
{
   val = x.val;
   return *this;
}


//---------------------------------------------------------------------------
// Operators: "-", "-=":
//---------------------------------------------------------------------------
inline Iq operator - (const Iq &x, const Iq &y)
{
   Iq temp;
   temp.val = x.val - y.val;
   return temp;
}

/*inline Iq operator - (const Iq &x)
{
   Iq temp;
   temp.val = - x.val;
   return temp;
}*/

inline Iq & Iq :: operator -= (const Iq &x)
{
   val -= x.val;
   return *this;
}

inline Iq & Iq :: operator -= (long	&x)
{
   val -= x*(1<<_point);
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "+", "+="
//---------------------------------------------------------------------------
inline Iq operator + (const Iq &x, const Iq &y)
{
   Iq temp;
   temp.val = x.val + y.val;
   return temp;
}

inline Iq & Iq :: operator += (const Iq &x)
{
   val += x.val;
   return *this;
}

inline Iq & Iq::operator	+= (long	&x)
{
   val += x*(1<<_point);
   return *this;

}


//---------------------------------------------------------------------------
// Operators: "==", "!=", "<", ">", "<=", ">=", "&&", "||"
//---------------------------------------------------------------------------
inline bool operator == (const Iq &x, const Iq& y)     { return (x.val == y.val); }
inline bool operator != (const Iq &x, const Iq& y)     { return (x.val != y.val); }
inline bool operator <  (const Iq &x, const Iq &y)     { return (x.val <  y.val); }
inline bool operator >  (const Iq &x, const Iq &y)     { return (x.val >  y.val); }
inline bool operator <= (const Iq &x, const Iq &y)     { return (x.val <= y.val); }
inline bool operator >= (const Iq &x, const Iq &y)     { return (x.val >= y.val); }
inline bool operator && (const Iq &x, const Iq &y)     { return (x.val && y.val); }
inline bool operator || (const Iq &x, const Iq &y)     { return (x.val || y.val); }

//---------------------------------------------------------------------------
// Operators: "&", "&="
//---------------------------------------------------------------------------
inline Iq operator & (const Iq &x, const long &y)
{
   Iq temp;
   temp.val = x.val & y;
   return temp;
}

inline Iq & Iq :: operator &= (const long &x)
{
   val &= x;
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "|", "|="
//---------------------------------------------------------------------------
inline Iq operator | (const Iq &x, const long &y)
{
   Iq temp;
   temp.val = x.val | y;
   return temp;
}

inline Iq & Iq :: operator |= (const long &x)
{
   val |= x;
   return *this;
}

//---------------------------------------------------------------------------
// Operators: "^", "^="
//---------------------------------------------------------------------------

inline Iq operator ^ (const Iq &x, const long &y)
{
   Iq temp;
   temp.val = x.val ^ y;
   return temp;
}

inline Iq & Iq :: operator ^= (const long &x)
{
   val ^= x;
   return *this;
}

//---------------------------------------------------------------------------
// Functions: IQabs(A), IQNabs(A)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Functions: IQmpyI32(A,B), IQNmpyI32(A,B)
//---------------------------------------------------------------------------
inline  Iq  IQmpyI32(const Iq & y, long x)
{
   Iq temp;
   temp.val = (y.val * x);
   return temp;
}

/*inline  Iq  IQmpyI32(long y, const Iq & x)
{
   Iq temp;
   temp.val = (y * x.val);
   return temp;
}*/

//---------------------------------------------------------------------------
// Functions: IQint(A), IQNint(A)
//---------------------------------------------------------------------------

inline  long    IQint(const Iq & x)
{
	return x.val>>x._point;
}

//---------------------------------------------------------------------------

				
#define   _IQ(A)       (long) ((A) * (1<<GLOBALQ))

#define   _IQ30(A)      (long) ((A) * 1073741824.0L)
#define   _IQ29(A)      (long) ((A) * 536870912.0L)
#define   _IQ28(A)      (long) ((A) * 268435456.0L)
#define   _IQ27(A)      (long) ((A) * 134217728.0L)
#define   _IQ26(A)      (long) ((A) * 67108864.0L)
#define   _IQ25(A)      (long) ((A) * 33554432.0L)
#define   _IQ24(A)      (long) ((A) * 16777216.0L)
#define   _IQ23(A)      (long) ((A) * 8388608.0L)
#define   _IQ22(A)      (long) ((A) * 4194304.0L)
#define   _IQ21(A)      (long) ((A) * 2097152.0L)
#define   _IQ20(A)      (long) ((A) * 1048576.0L)
#define   _IQ19(A)      (long) ((A) * 524288.0L)
#define   _IQ18(A)      (long) ((A) * 262144.0L)
#define   _IQ17(A)      (long) ((A) * 131072.0L)
#define   _IQ16(A)      (long) ((A) * 65536.0L)
#define   _IQ15(A)      (long) ((A) * 32768.0L)
#define   _IQ14(A)      (long) ((A) * 16384.0L)
#define   _IQ13(A)      (long) ((A) * 8192.0L)
#define   _IQ12(A)      (long) ((A) * 4096.0L)
#define   _IQ11(A)      (long) ((A) * 2048.0L)
#define   _IQ10(A)      (long) ((A) * 1024.0L)
#define   _IQ9(A)       (long) ((A) * 512.0L)
#define   _IQ8(A)       (long) ((A) * 256.0L)
#define   _IQ7(A)       (long) ((A) * 128.0L)
#define   _IQ6(A)       (long) ((A) * 64.0L)
#define   _IQ5(A)       (long) ((A) * 32.0L)
#define   _IQ4(A)       (long) ((A) * 16.0L)
#define   _IQ3(A)       (long) ((A) * 8.0L)
#define   _IQ2(A)       (long) ((A) * 4.0L)
#define   _IQ1(A)       (long) ((A) * 2.0L)





}
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP
