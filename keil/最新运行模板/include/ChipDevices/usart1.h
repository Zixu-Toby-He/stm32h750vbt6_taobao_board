#ifndef __USART1_H__
#define __USART1_H__

#include <stdint.h>

// 信号发送
void usart1_send(uint8_t msg);
void usart1_sendstr(char* msg);

// baudrate：波特率
// msghandler：信号处理函数
void usart1_init(uint32_t baudrate, void (*msghandler)(uint8_t));

#endif
