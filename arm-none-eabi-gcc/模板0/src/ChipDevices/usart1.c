#include "stm32h750xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

#include "usart_uni.h"
#include "usart1.h"

// 全局变量定义
static UART_HandleTypeDef huart;

// USART1中断服务函数
void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart);
}

// 发送单字节数据
void usart1_send(uint8_t msg)
{
	//// 使用阻塞模式发送单字节（可能出现死锁bug）
	//HAL_UART_Transmit(&huart, &msg, 1, HAL_MAX_DELAY);
	while(__HAL_UART_GET_FLAG(&huart, UART_FLAG_TC) == RESET) {} // 等待串口
	huart.Instance->TDR = msg;
}

// 发送字符串
void usart1_sendstr(char* msg)
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

// USART初始化函数
void usart1_init(uint32_t baudrate, void (*msghandler)(uint8_t))
{
	usart_uni_t info_usart_uni = { usart_select_usart1, msghandler };

	// 配置USART1参数
	huart.Instance                    = USART1;
	huart.Init.BaudRate               = baudrate;
	huart.Init.WordLength             = UART_WORDLENGTH_8B;
	huart.Init.StopBits               = UART_STOPBITS_1;
	huart.Init.Parity                 = UART_PARITY_NONE;
	huart.Init.Mode                   = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
	huart.Init.OverSampling           = UART_OVERSAMPLING_16;
	huart.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
	huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	// 初始化USART
	if (HAL_UART_Init(&huart) != HAL_OK)
	{
		// 初始化错误处理（可根据需要添加错误处理）
		while(1);
	}
	usart_uni_register(info_usart_uni);
    
    // 使能接收中断
    HAL_UART_Receive_IT(&huart, get_rx_byte_ptr(usart_select_usart1), 1);
}
