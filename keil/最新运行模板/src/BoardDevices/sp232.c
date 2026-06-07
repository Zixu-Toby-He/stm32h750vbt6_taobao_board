#include "stm32h7xx_hal.h"

#include "uart8.h"

#include "sp232.h"


// 发送单字节数据
void db9_send(uint8_t msg)
{
	uart8_send(msg);
}

// 发送字符串
void db9_sendstr(char* msg)
{
	uart8_sendstr(msg);
}

// db9 初始化函数
void db9_init(uint32_t baudrate, void (*msghandler)(uint8_t))
{
	uart8_init(baudrate, msghandler);
}
