#ifndef ADC_GETSAMPLE_HPP
#define ADC_GETSAMPLE_HPP

#ifdef __cplusplus
 extern "C" {
#endif 

// Интерфейс получения данных. Будет иметь различные реализации
class IGetable {
public:
	void GetSample(){}
};




#ifdef __cplusplus
};
#endif
#endif	//define ADC_GETSAMPLE_HPP
