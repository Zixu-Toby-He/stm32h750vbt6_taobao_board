#include "stm32h7xx_hal.h"

#include "usart_uni.h"


#include "uart8.h"

// 全局变量定义
static UART_HandleTypeDef huart;

// UART8中断服务函数
void UART8_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart);
}


// 发送单字节数据
void uart8_send(uint8_t msg)
{
	//// 使用阻塞模式发送单字节（可能出现死锁bug）
	// HAL_UART_Transmit(&huart, (uint8_t*)msg, 1, HAL_MAX_DELAY);
	while(__HAL_UART_GET_FLAG(&huart, UART_FLAG_TC) == RESET) {} // 等待串口
	huart.Instance->TDR = msg;
}

// 发送字符串
void uart8_sendstr(char* msg)
{
	while(*msg != '\0')
	{
		//// 使用阻塞模式发送单字节（可能出现死锁bug）
		// HAL_UART_Transmit(&huart, (uint8_t*)msg, 1, HAL_MAX_DELAY);
		while(__HAL_UART_GET_FLAG(&huart, UART_FLAG_TC) == RESET) {} // 等待串口
		huart.Instance->TDR = *msg;
		msg++;
	}
}

// db9 初始化函数
void uart8_init(uint32_t baudrate, void (*msghandler)(uint8_t))
{
	usart_uni_t info_usart_uni = { usart_select_uart8, msghandler };

	usart_uni_register(info_usart_uni);

	// 配置UART8参数
	huart.Instance                    = UART8;
	huart.Init.BaudRate               = baudrate;
	huart.Init.WordLength             = UART_WORDLENGTH_8B;
	huart.Init.StopBits               = UART_STOPBITS_1;
	huart.Init.Parity                 = UART_PARITY_NONE;
	huart.Init.Mode                   = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
	// huart.Init.OverSampling           = UART_OVERSAMPLING_16;
	// huart.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
	// huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	// 初始化USART
	if (HAL_UART_Init(&huart) != HAL_OK)
	{
		// 初始化错误处理（可根据需要添加错误处理）
		while(1);
	}

	// 使能接收中断
	HAL_UART_Receive_IT(&huart, get_rx_byte_ptr(usart_select_uart8), 1);
}
