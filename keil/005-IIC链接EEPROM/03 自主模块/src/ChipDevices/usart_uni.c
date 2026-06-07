#include "stm32h750xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

#include "ebdtypes.h"

#include "usart_uni.h"



void msghandler_default(uint8_t msg);

// 8个缓冲，防止竞争
uint8_t rx_bytes[8];
uint8_t rx_err;

void (*msghandlers[8])(uint8_t) = { msghandler_default, msghandler_default, msghandler_default, msghandler_default, msghandler_default, msghandler_default, msghandler_default, msghandler_default };

void usart_uni_init(usart_uni_t* usart_uni)
{
	// 当前与 usart_uni_register_many 没有区别
	uint8_t i = 0;
	for(i = 0; usart_uni[i].usart_select != usart_select_none; i++)
	{
		msghandlers[usart_uni[i].usart_select - 1] = usart_uni[i].msghandler;
	}
}

void usart_uni_register_many(usart_uni_t* usart_uni)
{
	uint8_t i = 0;
	for(i = 0; usart_uni[i].usart_select != usart_select_none; i++)
	{
		msghandlers[usart_uni[i].usart_select - 1] = usart_uni[i].msghandler;
	}
}

void usart_uni_register(usart_uni_t usart_uni)
{
	msghandlers[usart_uni.usart_select - 1] = usart_uni.msghandler;
}

__attribute__((always_inline)) uint8_t* get_rx_byte_ptr(usart_select_t n)
{
	return (n)? ((uint8_t*)rx_bytes + (n - 1)) : &rx_err;
}

__attribute__((always_inline)) uint8_t get_rx_byte(usart_select_t n)
{
	return (n)? rx_bytes[n - 1] : rx_err;
}

// 默认消息处理函数（空函数）
void msghandler_default(uint8_t msg) {}

// 接收完成回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t idx = 0;
	switch((uint32_t)(huart->Instance))
	{
		case USART1_BASE:
			idx = 0;
			break;
		case USART2_BASE:
			idx = 1;
			break;
		case USART3_BASE:
			idx = 2;
			break;
		case UART4_BASE:
			idx = 3;
			break;
		case UART5_BASE:
			idx = 4;
			break;
		case USART6_BASE:
			idx = 5;
			break;
		case UART7_BASE:
			idx = 6;
			break;
		case UART8_BASE:
			idx = 7;
			break;
		default:
			// 其他情况出错错误，利用err进行重启
			HAL_UART_Receive_IT(huart, &rx_err, 1);
			return;
	}
	msghandlers[idx](rx_bytes[idx]);
	HAL_UART_Receive_IT(huart, &rx_bytes[idx], 1);
}

// HAL库MSP初始化回调函数
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef init_info_gpio = {0};
	GPIO_TypeDef* gpio_rx = 0;
	GPIO_TypeDef* gpio_tx = 0;
	uint16_t      pin_rx  = 0;
	uint16_t      pin_tx  = 0;
	// 复用
	uint32_t      alternate;
	// 中断
	IRQn_Type     irq;

	static uint8_t priority = 0x11;

	switch((uint32_t)(huart->Instance))
	{
		case USART1_BASE:
			gpio_rx   = GPIOA;
			gpio_tx   = GPIOA;
			pin_rx    = GPIO_PIN_10;
			pin_tx    = GPIO_PIN_9;
			alternate = GPIO_AF7_USART1;
			irq = USART1_IRQn;
			__HAL_RCC_USART1_CLK_ENABLE();
	        __HAL_RCC_GPIOA_CLK_ENABLE();
			break;
		case USART2_BASE:
			return;
			// break;
		case USART3_BASE:
			return;
			// break;
		case UART4_BASE:
			return;
			// break;
		case UART5_BASE:
			return;
			// break;
		case USART6_BASE:
			return;
			// break;
		case UART7_BASE:
			return;
			// break;
		case UART8_BASE:
			gpio_rx   = GPIOE;
			gpio_tx   = GPIOE;
			pin_rx    = GPIO_PIN_0;
			pin_tx    = GPIO_PIN_1;
			alternate = GPIO_AF8_UART8;
			irq = UART8_IRQn;
			__HAL_RCC_GPIOE_CLK_ENABLE();
			__HAL_RCC_UART8_CLK_ENABLE();
			break;
		default:
			// 其他情况出错错误，直接返回
			return;
	}
	// 引脚初始化
	init_info_gpio.Pin       = pin_rx;
	init_info_gpio.Mode      = GPIO_MODE_AF_PP;
	init_info_gpio.Pull      = GPIO_NOPULL;
	init_info_gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	init_info_gpio.Alternate = alternate;
	HAL_GPIO_Init(gpio_rx, &init_info_gpio);
	init_info_gpio.Pin       = pin_tx;
	HAL_GPIO_Init(gpio_tx, &init_info_gpio);

	// 配置中断
	HAL_NVIC_SetPriority(irq, priority >> 4, priority & 0x0F);
	HAL_NVIC_EnableIRQ(irq);
	priority++;
}
