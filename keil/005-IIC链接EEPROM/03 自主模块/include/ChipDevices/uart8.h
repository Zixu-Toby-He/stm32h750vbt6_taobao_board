#ifndef __UART8_H__
#define __UART8_H__

#include <stdint.h>

// 第一套端口组（Tx = PD2、Rx = PC12、UART5）
// 第二套端口组（Tx = PE0、Rx = PE 1、UART8）
// 信号发送
void uart8_send(uint8_t msg);
void uart8_sendstr(char* msg);

// baudrate：波特率
// msghandler：信号处理函数
void uart8_init(uint32_t baudrate, void (*msghandler)(uint8_t));

#endif

