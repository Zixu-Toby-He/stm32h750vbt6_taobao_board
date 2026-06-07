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
	AT24CXX_Init();
}


int main(void)
{
	uint8_t i;
	uint8_t temp;

	char msg_in [128];
	char msg_out[128];
	char msg_read[128];

	machine_init();
	devices_init();

	while(AT24CXX_Check())// 检测不到24c02
	{
		delay_ms(500);
		LED_Toggle();      // DS0闪烁
	}
	db9_sendstr("AT24C02 detected\r\n");
	
	while(true)
	{
		// 写入
		if (is_data_in())
		{
			temp = get_msg(msg_in);
			for(i = 0; i < temp; i++)
			{
				AT24CXX_WriteOneByte(i, msg_in[i]);
				AT24CXX_WriteOneByte(i + 1, '\0');
			}
			clear_msg();
			db9_sendstr("Write Successfully.\r\n");
		}
		// 读取
		i = 0;
		do
		{
			temp = AT24CXX_ReadOneByte(i);
			msg_read[  i] = temp;
			msg_read[++i] = '\0';
		}
		while (temp);
		sprintf(msg_out, "current data: \"%s\"\r\n", msg_read);
		db9_sendstr(msg_out);

		delay_ms(500);
		LED_Toggle();
    }
}





