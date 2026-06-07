#include "stm32h7xx_hal_gpio.h"

#include "stm32h7xx_hal_rcc.h"

#include "bitband.h"

#include "sp232.h"

UART_HandleTypeDef uart8_handler;



void SP232_Init(baudrate_t baudrate)
{
	GPIO_InitTypeDef   init_info_gpio;
	
	// 使用第二套端口组（Tx = PE0、Rx = PE1、UART8）
	RCC->AHB4ENR  |= RCC_AHB4ENR_GPIOEEN;
	RCC->APB1LENR |= RCC_APB1LENR_UART8EN;

	// PE0：上拉开漏输出
	init_info_gpio.Pin       = GPIO_PIN_0;
	init_info_gpio.Mode      = GPIO_MODE_AF_PP;
	init_info_gpio.Pull      = GPIO_NOPULL;
	init_info_gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
	init_info_gpio.Alternate = GPIO_AF8_UART8;
	HAL_GPIO_Init(GPIOE, &init_info_gpio);
	
	init_info_gpio.Pin       = GPIO_PIN_1;
	init_info_gpio.Mode      = GPIO_MODE_INPUT;
	init_info_gpio.Pull      = GPIO_PULLUP;
	init_info_gpio.Speed     = GPIO_SPEED_FREQ_HIGH;
	init_info_gpio.Alternate = GPIO_AF8_UART8;
	HAL_GPIO_Init(GPIOE, &init_info_gpio);

	uart8_handler.Instance        = UART8;
	uart8_handler.Init.BaudRate   = baudrate;
	uart8_handler.Init.WordLength = UART_WORDLENGTH_8B;
	uart8_handler.Init.StopBits   = UART_STOPBITS_1;
	uart8_handler.Init.Parity     = UART_PARITY_NONE;
	uart8_handler.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	uart8_handler.Init.Mode       = UART_MODE_TX_RX;
	HAL_UART_Init(&uart8_handler);

}
