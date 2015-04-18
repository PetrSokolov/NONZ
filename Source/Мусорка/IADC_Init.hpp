#ifndef ADC_INIT_HPP
#define ADC_INIT_HPP

#ifdef __cplusplus
 extern "C" {
#endif 
/*
// Абстрактный интерфейс инициализации
class IStrategy_ADC_Init
{
public:
	int i;
	IStrategy_ADC_Init(void){}
	~IStrategy_ADC_Init(void){}
 
	virtual void init(void) = 0;
};

// Первая реализация интерфейса инициализации
class iADC_Init_1: public IStrategy_ADC_Init
{
public:
	iADC_Init_1(){}
	~iADC_Init_1(){}
 
	void init(void);
};
// Вторая реализация интерфейса инициализации
class iADC_Init_2: public IStrategy_ADC_Init
{
public:
	iADC_Init_2(){}
	~iADC_Init_2(){}
 
	void init(void);
};

// Интерфейс, позволяющий подменять реалазации интерфейсу
class I_ADC_InitReplace
{
protected:
	IStrategy_ADC_Init* iADC_Init_p;// Указатель на абстрактный класс интерфейса
public:
	I_ADC_InitReplace(){}
	~I_ADC_InitReplace(){}
 
	virtual void UseStrategy(void) = 0;
	virtual void SetStrategy(IStrategy_ADC_Init* v) = 0;
};

// Базовый класс АЦП, реализующий интерфейс I_ADC_InitReplace
class ADC: public I_ADC_InitReplace
{
	public:
	ADC(){}
	~ADC(){}
 
	void UseStrategy(void)
	{
		iADC_Init_p->init();
	}
 
	void SetStrategy(IStrategy_ADC_Init* o)
	{
		iADC_Init_p = o;
	}
};
*/
#ifdef __cplusplus
};
#endif
#endif	//define ADC_INIT_HPP

