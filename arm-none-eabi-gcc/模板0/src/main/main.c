#include "stm32h7xx.h"
#include "cache.h"
#include "sysclock.h"
#include "mpu.h"

#include "gpio_output.h"
#include "delay.h"
#include "led.h"

int main(void)
{
	output_select_t select[8] = {
		SELECT_OUTPUT9,
		SELECT_OUTPUT10,
		SELECT_OUTPUT11,
		SELECT_OUTPUT12,
		SELECT_OUTPUT13,
		SELECT_OUTPUT14,
		SELECT_OUTPUT15,
		SELECT_OUTPUT16
	};
	uint8_t i = 0;
	CPU_CACHE_Enable();                 // 缓存
	HAL_Init();                         // HAL 库初始化
	MPU_Memory_Protection();            // 内存保护？
	Stm32_Clock_Init(192, 5, 2, 2);     // 时钟初始化

	// LED_Init();
	OUTPUT_GPIO_Init(
		SELECT_OUTPUT9  |
		SELECT_OUTPUT10 |
		SELECT_OUTPUT11 |
		SELECT_OUTPUT12 |
		SELECT_OUTPUT13 |
		SELECT_OUTPUT14 |
		SELECT_OUTPUT15 |
		SELECT_OUTPUT16
	);
	delay_init();

	while(1)
	{
		Output_Toggle(select[i]);
		i++;
		i &= 7;
		delay_ms(100);
	}
	return 0;
}