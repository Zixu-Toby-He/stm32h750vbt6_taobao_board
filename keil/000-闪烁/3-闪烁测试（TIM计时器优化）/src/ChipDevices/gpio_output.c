#include "gpio_output.h"

/**
  * 函数功能: 板载按键IO引脚初始化.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：使用宏定义方法代替具体引脚号，方便程序移植，只要简单修改bsp_gpio.h
  *           文件相关宏定义就可以方便修改引脚。
  */
void OUTPUT_GPIO_Init(output_init_t init_series)
{
	/* 定义IO硬件初始化结构体变量 */
	GPIO_InitTypeDef init_info_gpio = {0};

	/* 配置OUTPUT GPIO:推挽输出模式 */
	#define INIT_OUTPUT(n)                                  \
		OUTPUT##n##_RCC_CLK_ENABLE();                       \
		init_info_gpio.Pin  = OUTPUT##n##_GPIO_PIN;         \
		HAL_GPIO_Init(OUTPUT##n##_GPIO, &init_info_gpio);
	
	init_info_gpio.Mode = GPIO_MODE_OUTPUT_PP;
	init_info_gpio.Pull = GPIO_SPEED_FREQ_LOW;

	if (init_series & 0x1) { INIT_OUTPUT( 1); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 2); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 3); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 4); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 5); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 6); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 7); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 8); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT( 9); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT(10); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT(11); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT(12); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT(13); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT(14); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT(15); }        init_series >>= 1;
	if (init_series & 0x1) { INIT_OUTPUT(16); }        init_series >>= 1;
}

void Output_StateWrite(output_select_t channel, output_state_t state)
{
	#define OUTPUT_WRITE(n, hl)  HAL_GPIO_WritePin( OUTPUT##n##_GPIO, OUTPUT##n##_GPIO_PIN, (GPIO_PinState)hl)

	switch (channel)
	{
		case SELECT_OUTPUT1 :    OUTPUT_WRITE( 1, state);    break;
		case SELECT_OUTPUT2 :    OUTPUT_WRITE( 2, state);    break;
		case SELECT_OUTPUT3 :    OUTPUT_WRITE( 3, state);    break;
		case SELECT_OUTPUT4 :    OUTPUT_WRITE( 4, state);    break;
		case SELECT_OUTPUT5 :    OUTPUT_WRITE( 5, state);    break;
		case SELECT_OUTPUT6 :    OUTPUT_WRITE( 6, state);    break;
		case SELECT_OUTPUT7 :    OUTPUT_WRITE( 7, state);    break;
		case SELECT_OUTPUT8 :    OUTPUT_WRITE( 8, state);    break;
		case SELECT_OUTPUT9 :    OUTPUT_WRITE( 9, state);    break;
		case SELECT_OUTPUT10:    OUTPUT_WRITE(10, state);    break;
		case SELECT_OUTPUT11:    OUTPUT_WRITE(11, state);    break;
		case SELECT_OUTPUT12:    OUTPUT_WRITE(12, state);    break;
		case SELECT_OUTPUT13:    OUTPUT_WRITE(13, state);    break;
		case SELECT_OUTPUT14:    OUTPUT_WRITE(14, state);    break;
		case SELECT_OUTPUT15:    OUTPUT_WRITE(15, state);    break;
		case SELECT_OUTPUT16:    OUTPUT_WRITE(16, state);    break;
		default:
			return;
	}

}

void Output_Toggle(output_select_t channel)
{
	#define OUTPUT_TOGGLE(n)      HAL_GPIO_TogglePin(OUTPUT##n##_GPIO, OUTPUT##n##_GPIO_PIN)

	switch (channel)
	{
		case SELECT_OUTPUT1 :    OUTPUT_TOGGLE( 1);    break;
		case SELECT_OUTPUT2 :    OUTPUT_TOGGLE( 2);    break;
		case SELECT_OUTPUT3 :    OUTPUT_TOGGLE( 3);    break;
		case SELECT_OUTPUT4 :    OUTPUT_TOGGLE( 4);    break;
		case SELECT_OUTPUT5 :    OUTPUT_TOGGLE( 5);    break;
		case SELECT_OUTPUT6 :    OUTPUT_TOGGLE( 6);    break;
		case SELECT_OUTPUT7 :    OUTPUT_TOGGLE( 7);    break;
		case SELECT_OUTPUT8 :    OUTPUT_TOGGLE( 8);    break;
		case SELECT_OUTPUT9 :    OUTPUT_TOGGLE( 9);    break;
		case SELECT_OUTPUT10:    OUTPUT_TOGGLE(10);    break;
		case SELECT_OUTPUT11:    OUTPUT_TOGGLE(11);    break;
		case SELECT_OUTPUT12:    OUTPUT_TOGGLE(12);    break;
		case SELECT_OUTPUT13:    OUTPUT_TOGGLE(13);    break;
		case SELECT_OUTPUT14:    OUTPUT_TOGGLE(14);    break;
		case SELECT_OUTPUT15:    OUTPUT_TOGGLE(15);    break;
		case SELECT_OUTPUT16:    OUTPUT_TOGGLE(16);    break;
		default:
			return;
	}
}
