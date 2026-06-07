#ifndef __USART_UNI_H__
#define __USART_UNI_H__

#include <stdint.h>

#include "stm32h750xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"


void msghandler_default(uint8_t);

typedef enum
{
	usart_select_none   = 0,
	usart_select_usart1 = 1,
	usart_select_usart2 = 2,
	usart_select_usart3 = 3,
	usart_select_uart4  = 4,
	usart_select_uart5  = 5,
	usart_select_usart6 = 6,
	usart_select_uart7  = 7,
	usart_select_uart8  = 8,
}
usart_select_t;
typedef struct 
{
	usart_select_t usart_select;
	void (*msghandler)(uint8_t);
}
usart_uni_t;




// 该函数不对任何端口进行初始化，仅对多接口统一功能进行初始化
// 参数格式：{ status_usart, status_usart, ... , {0,NULL} }
// 最多初始化 8 个，不会对参数格式进行检查，请务必按格式赋值
void usart_uni_init(usart_uni_t*);
void usart_uni_register_many(usart_uni_t*);
void usart_uni_register(usart_uni_t);



// 缓冲区
__attribute__((always_inline)) uint8_t* get_rx_byte_ptr(usart_select_t n);
__attribute__((always_inline)) uint8_t  get_rx_byte    (usart_select_t n);

#endif
