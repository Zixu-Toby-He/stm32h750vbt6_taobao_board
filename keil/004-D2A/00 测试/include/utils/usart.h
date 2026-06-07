#ifndef __USART_H__
#define __USART_H__

#include "stdio.h"
#include "sys.h"


// 信号发送
void uart_send(uint8_t msg);

// baudrate：波特率
// msghandler：信号处理函数
void uart_init(uint32_t baudrate, void (*msghandler)(uint8_t));

#endif