// C标准库
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 核心设备
#include "mpu.h"
#include "cache.h"


// 板上外设
#include "led.h"
#include "sp232.h"

// util
#include "sysclock.h"
#include "delay.h"
#include "chip_info.h"

#include "msg.h"

void machine_init(void)
{
	CPU_CACHE_Enable();                 // 缓存
	HAL_Init();                         // HAL 库初始化
	MPU_Memory_Protection();            // 内存保护？
	Stm32_Clock_Init(192, 5, 2, 2);     // 时钟初始化
	delay_init();                       // 延迟初始化
}

void devices_init(void)
{
	db9_init(115200, msghandler);    // 串口初始化
	LED_Init();
}


int main(void)
{
	char info[128] = {
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
		'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
	};
	cpu_id_t    cpu_id     = {{0,0,0}};
	uint16_t    flash_size = 0;
	chip_type_t chip_type  = 0;

	machine_init();
	devices_init();
	
	cpu_id     = chip_info_get_cpu_id();
	flash_size = chip_info_get_flash_size();
	chip_type  = chip_info_get_chip_type();

	while (true)
	{
		sprintf(
			info,
			"CPU ID:     %X - %X - %X\r\n"
			"Flash size: %u\r\n"
			"Chip type:  0x%X\r\n"
			"\r\n",
			cpu_id.id[0], cpu_id.id[1], cpu_id.id[2],
			flash_size,
			chip_type
		);
		db9_sendstr(info);
		delay_ms(500);
		LED_Toggle();
	}
}





