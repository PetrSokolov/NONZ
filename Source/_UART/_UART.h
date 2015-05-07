#ifndef UART_HPP
#define UART_HPP
#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif 


namespace src{	 
#define countof(a)   (sizeof(a) / sizeof(*(a)))	
	
// Базовый класс
class CUART_Base{
	protected:
		uint8_t	txbufer[32];
		uint8_t	rxbufer[32];
	public:
		uint8_t	tmp;
		virtual void Tx() =0;
		virtual void Rx() =0;
		virtual void Init() =0;
}; 

// Производный класс UART1
// В конструкторе задаются размеры буферов

class CUART1 : public CUART_Base{
	public:
		CUART1(uint16_t rx_size, uint16_t tx_size)
			{/* rxbufer = new uint16_t [rx_size];
				 sizeof_rxbufer = rx_size;
			  txbufer = new uint16_t [tx_size];
				 sizeof_txbufer = tx_size;*/
			}
		virtual void Tx();
		virtual void Rx();
		virtual void Init();
		virtual void TxISR();
		virtual void RxISR();
};



}//namespace
#ifdef __cplusplus
};
#endif
#endif	//define UART_HPP


