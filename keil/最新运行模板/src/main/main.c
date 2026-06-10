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
#include "cache.h"

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
#include "eeprom.h"

// util
#include "sysclock.h"
#include "delay.h"

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
	LED_Init();                      // LED 初始化
	eeprom_init();
}


int main(void)
{
	uint8_t i;
	uint8_t temp;

	char msg_in [128];
	char msg_out[128];
	char msg_read[128];
	eeprom_page_data_t page_data;

	machine_init();
	devices_init();
	

	while(true)
	{
		// 写入
		if (is_data_in())
		{
			temp = get_msg(msg_in);
			for(i = 0; i < temp; i += 8)
			{
				page_data = *((eeprom_page_data_t*)(&msg_in[i]));
				eeprom_write_page(i / 8, page_data);
			}
			for(; i < temp; i++)
			{
				eeprom_write_byte(i, msg_in[i]);
				eeprom_write_byte(i + 1, '\0');
			}
			clear_msg();
			db9_sendstr("Write Successfully.\r\n");
		}
		// 读取
		i = 0;
		do
		{
			temp = eeprom_read_byte(i);
			msg_read[  i] = temp;
			msg_read[++i] = '\0';
		}
		while (temp && (i < 64));
		sprintf(msg_out, "current data: \"%s\"\r\n", msg_read);
		db9_sendstr(msg_out);

		temp = i;
		for(i = 0; i < temp; i += 8)
		{
			page_data = eeprom_read_page(i / 8);
			sprintf(
				msg_out,
				"page_%i: \"%c%c%c%c%c%c%c%c\"\r\n",
				i / 8,
				page_data.data[0],
				page_data.data[1],
				page_data.data[2],
				page_data.data[3],
				page_data.data[4],
				page_data.data[5],
				page_data.data[6],
				page_data.data[7]
			);
			db9_sendstr(msg_out);
		}

		delay_ms(500);
		LED_Toggle();
    }
}





