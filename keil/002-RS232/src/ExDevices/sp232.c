#include "stm32h7xx_hal.h"
#include "sp232.h"

// 全局变量定义
UART_HandleTypeDef huart8;
void msghandler_default(uint8_t msg);
void (*_msghandler_sp232_)(uint8_t) = msghandler_default;
static uint8_t rx_byte;  // 单字节接收缓冲区
static HAL_StatusTypeDef status = HAL_OK;

// 默认消息处理函数（空函数）
void msghandler_default(uint8_t msg)
{
	// 可在此添加默认处理逻辑
}

// UART8中断服务函数
void UART8_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart8);
}

// 接收完成回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART8)
	{
		// 调用用户定义的消息处理器
		_msghandler_sp232_(rx_byte);
		// 重新启用接收中断
		status = HAL_UART_Receive_IT(huart, &rx_byte, 1);
	}
}

HAL_StatusTypeDef db9_get_status(void)
{
	return status;
}
// 发送单字节数据
void db9_send(uint8_t msg)
{
	//// 使用阻塞模式发送单字节（有风险出现死锁bug）
	// HAL_UART_Transmit(&huart8, &msg, 1, HAL_MAX_DELAY);
	// 使用寄存器发送
	while(__HAL_UART_GET_FLAG(&huart8, UART_FLAG_TC) == RESET) {} // 等待串口
	huart8.Instance->TDR = msg;
}

// HAL库MSP初始化回调函数
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
	GPIO_InitTypeDef         init_info_gpio = {0};
	
	if(uartHandle->Instance == UART8)
	{
		// 使能 UART8 和 GPIOE 时钟
		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_UART8_CLK_ENABLE();

		// 配置 PE1 为 UART8_TX，PE0 为 UART8_RX
		init_info_gpio.Pin       = GPIO_PIN_1;
		init_info_gpio.Mode      = GPIO_MODE_AF_PP;
		init_info_gpio.Pull      = GPIO_NOPULL;
		init_info_gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
		init_info_gpio.Alternate = GPIO_AF8_UART8;
		HAL_GPIO_Init(GPIOE, &init_info_gpio);

		init_info_gpio.Pin       = GPIO_PIN_0;
		HAL_GPIO_Init(GPIOE, &init_info_gpio);

		// 配置 UART8 中断
		HAL_NVIC_EnableIRQ(UART8_IRQn);
		HAL_NVIC_SetPriority(UART8_IRQn, 1, 1);
    }
}

// db9 初始化函数
void db9_init(uint32_t baudrate, void (*__msghandler__)(uint8_t))
{
	// 更新消息处理器
	_msghandler_sp232_ = __msghandler__;
	// 配置UART8参数
	huart8.Instance                    = UART8;
	huart8.Init.BaudRate               = baudrate;
	huart8.Init.WordLength             = UART_WORDLENGTH_8B;
	huart8.Init.StopBits               = UART_STOPBITS_1;
	huart8.Init.Parity                 = UART_PARITY_NONE;
	huart8.Init.Mode                   = UART_MODE_TX_RX;
	huart8.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
	//huart8.Init.OverSampling           = UART_OVERSAMPLING_16;
	//huart8.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
	//huart8.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	// 初始化USART
	if (HAL_UART_Init(&huart8) != HAL_OK)
	{
		// 初始化错误处理（可根据需要添加错误处理）
		while(1);
	}
	// 使能接收中断
	HAL_UART_Receive_IT(&huart8, &rx_byte, 1);
}
