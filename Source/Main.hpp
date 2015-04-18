#ifndef MAIN_HPP
#define MAIN_HPP

#ifdef __cplusplus
 extern "C" {
#endif 

// Прототип функции-вектора прерывания
void DMA1_Channel4_IRQHandler(void);
void USART1_IRQHandler(void);
	 
class myclass {
int k;
	public:
		int h;
	myclass() {}
	~myclass() {}
};

class CAnalogSignal {
float y,z,t, mean, rms;
unsigned int *source_ptr;
	public:
	CAnalogSignal(float init_value, float init_filter_time) {y=init_value; z=init_value; t=init_filter_time;}
	~CAnalogSignal() {}
	inline void TakeSource(unsigned int *source) {source_ptr = source;};
	inline float Mean();
	inline void RMS(){}
	inline float Get_Mean() {return mean;}
	inline float Get_RMS() {return rms;}
};

inline float CAnalogSignal::Mean()
{
 y = y + ((*source_ptr-y)*t);
 z = z + ((y-z)*t);
return z;
}

class youclass {
	public:
	int you_cl;
};

class inheritance_myclass : myclass, youclass {
	public:
		int inh;
};

#ifdef __cplusplus
}
#endif
#endif	//MAIN_HPP
