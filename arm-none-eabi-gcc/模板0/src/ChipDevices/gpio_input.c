#include "delay.h"
#include "gpio_input.h"

/**
  * 函数功能: 板载按键IO引脚初始化.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：使用宏定义方法代替具体引脚号，方便程序移植，只要简单修改bsp_gpio.h
  *           文件相关宏定义就可以方便修改引脚。
  */
void INPUT_GPIO_Init(input_init_t init_series)
{
	/* 定义IO硬件初始化结构体变量 */
	GPIO_InitTypeDef init_info_gpio = {0};

	/* 配置INPUT GPIO:输入上拉模式 */
	#define INIT_INPUT(n)                                   \
		INPUT##n##_RCC_CLK_ENABLE();                        \
		init_info_gpio.Pin  = INPUT##n##_GPIO_PIN;          \
		HAL_GPIO_Init(INPUT##n##_GPIO, &init_info_gpio);

	init_info_gpio.Mode = GPIO_MODE_INPUT;
	init_info_gpio.Pull = GPIO_PULLUP;
	
	if (init_series & 0x1) { INIT_INPUT( 1); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 2); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 3); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 4); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 5); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 6); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 7); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 8); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT( 9); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT(10); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT(11); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT(12); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT(13); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT(14); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT(15); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_INPUT(16); }        init_series >>= 1;
}

/**
  * 函数功能: 读取输入INPUT1的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
input_state_t INPUT_StateRead(input_select_t channel)
{
	#define READ_INPUT_STATE(n)                                                                          \
	{                                                                                                    \
		/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */                                 \
		if(HAL_GPIO_ReadPin(INPUT##n##_GPIO, INPUT##n##_GPIO_PIN) == INPUT##n##_ACTIVE_LEVEL)            \
		{                                                                                                \
			/* 延时一小段时间，消除抖动 */                                                               \
			delay_ms(20);                                                                               \
			/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */                           \
			if(HAL_GPIO_ReadPin(INPUT##n##_GPIO, INPUT##n##_GPIO_PIN) == INPUT##n##_ACTIVE_LEVEL)        \
			{                                                                                            \
				/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */                                       \
				return GPIO_ACTIVE;                                                                      \
			}                                                                                            \
		}                                                                                                \
		/* 输入处于无效电平，返回无效状态 */                                                             \
		return GPIO_INACTIVE;                                                                            \
	}

	switch (channel)
	{
		case SELECT_INPUT1 :    READ_INPUT_STATE( 1);
		case SELECT_INPUT2 :    READ_INPUT_STATE( 2);
		case SELECT_INPUT3 :    READ_INPUT_STATE( 3);
		case SELECT_INPUT4 :    READ_INPUT_STATE( 4);
		case SELECT_INPUT5 :    READ_INPUT_STATE( 5);
		case SELECT_INPUT6 :    READ_INPUT_STATE( 6);
		case SELECT_INPUT7 :    READ_INPUT_STATE( 7);
		case SELECT_INPUT8 :    READ_INPUT_STATE( 8);
		case SELECT_INPUT9 :    READ_INPUT_STATE( 9);
		case SELECT_INPUT10:    READ_INPUT_STATE(10);
		case SELECT_INPUT11:    READ_INPUT_STATE(11);
		case SELECT_INPUT12:    READ_INPUT_STATE(12);
		case SELECT_INPUT13:    READ_INPUT_STATE(13);
		case SELECT_INPUT14:    READ_INPUT_STATE(14);
		case SELECT_INPUT15:    READ_INPUT_STATE(15);
		case SELECT_INPUT16:    READ_INPUT_STATE(16);
		default:
			// 不可能
			return GPIO_INACTIVE;
	}
}
