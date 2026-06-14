#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();                      //开启GPIOA时钟

	GPIO_Initure.Pin   = GPIO_PIN_0;                   // PA0，1
	GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;          // 推挽输出
	GPIO_Initure.Pull  = GPIO_PULLUP;                  // 上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;    // 高速
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);               // 初始化GPIOB.0和GPIOB.1

	LED_Turn_Off();
}

