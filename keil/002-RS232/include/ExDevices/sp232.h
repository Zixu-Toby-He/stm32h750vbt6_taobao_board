#ifndef __USART_H__
#define __USART_H__

#include <stdint.h>
#include "sys.h"

// 第一套端口组（Tx = PD2、Rx = PC12、UART5）
// 第二套端口组（Tx = PE0、Rx = PE 1、UART8）
// 信号发送
void db9_send(uint8_t msg);
HAL_StatusTypeDef db9_get_status(void);

// baudrate：波特率
// msghandler：信号处理函数
void db9_init(uint32_t baudrate, void (*msghandler)(uint8_t));

#endif
