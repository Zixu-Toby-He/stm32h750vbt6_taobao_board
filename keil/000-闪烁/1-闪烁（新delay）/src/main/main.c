#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "timer.h"
#include "gpio_output.h"
#include "gpio_input.h"

#include "bitband.h"


int main(void)
{
	HAL_Init();                     // 初始化 HAL 库
	Cache_Enable();                 // 打开 L1-Cache
	Stm32_Clock_Init(192, 5, 2, 2); // 设置时钟,480MHz
	delay_init(DELAY_MODE_HLCK_DIV_8);    // 延时初始化
	LED_Init();                     // 初始化LED

	LED0(0);

	while(1)
	{
		LED0_Toggle;
		delay_ms(800);
		LED0_Toggle;
		delay_ms(200);
	}
}

