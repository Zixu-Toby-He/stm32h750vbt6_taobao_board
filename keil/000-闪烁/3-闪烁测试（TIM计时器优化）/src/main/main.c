// C标准库
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// hal库
#include "stm32h750xx.h"
#include "stm32h7xx_hal.h"

// 核心设备
#include "mpu.h"

// 片上外设
#include "dac.h"
#include "systick.h"
#include "tim2.h"
#include "tim3.h"
#include "tim4.h"
#include "tim5.h"

// 板上外设
#include "led.h"
#include "sp232.h"
#include "ads8688.h"
#include "24cxx.h"

// util
#include "sys.h"
#include "delay.h"

#include "msg.h"


void machine_init(void)
{
	CPU_CACHE_Enable();              // 缓存
	HAL_Init();                      // HAL 库初始化
	MPU_Memory_Protection();         // 内存保护？
	Stm32_Clock_Init(192, 5, 2, 2);  // 时钟初始化
}

void timfunc(void)
{
	LED_Toggle();
}

int main(void)
{
	machine_init();
	delay_init();
	LED_Init();


	TIM3_Init(500, 5000, timfunc);
	TIM3_Start();
	delay_s(5);
	TIM3_Pause();
	delay_s(1);
	TIM3_ReInit(100, 1000, timfunc);
	TIM3_Resume();
	delay_s(5);
	TIM3_Stop();


	// while(true) {}

	return 0;
}

