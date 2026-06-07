#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "stm32h750xx.h"
#include "stm32h7xx_hal.h"

#include "mpu.h"

#include "led.h"
#include "dac.h"
#include "tim5.h"
#include "systick.h"

#include "sp232.h"
#include "ads8688.h"
#include "24cxx.h"

#include "sys.h"
#include "delay.h"


void msghandler(uint8_t _msg_) {}

void tim_timeout_func(void)
{
	LED_Toggle();
}

int main(void)
{

	CPU_CACHE_Enable();           // 缓存
	HAL_Init();                   // HAL 库初始化
	MPU_Memory_Protection();      // 内存保护？

	Stm32_Clock_Init(192, 5, 2, 2); // 时钟初始化
	delay_init();                   // 延迟初始化
	LED_Init();                     // LED 初始化

	db9_init(115200, msghandler);

	DAC_Init(DAC1_CH1);          // 数转模初始化
	ADS8688_Init();              // 模转数初始化

	TIM5_Init((float)100, 1000, tim_timeout_func);

	while(true) {}

	return 0;
}

