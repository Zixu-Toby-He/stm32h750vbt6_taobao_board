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
	ADS8688_Init();
	DAC_Init(DAC1_CH1);

}


int main(void)
{
	double   ads_millivolt_ch0; // DA
	double   ads_millivolt_ch7; // 电阻

	machine_init();
	devices_init();

	DAC_Set_MilliVolt_CH1(1000);

	while(true)
	{
		ads_millivolt_ch7 = Get_MAN_CH_Data_MilliVolt(MAN_CH_7);
		ads_millivolt_ch0 = Get_MAN_CH_Data_MilliVolt(MAN_CH_0);
		DAC_Set_MilliVolt_CH1((uint16_t)ads_millivolt_ch7);
		switch (((ads_millivolt_ch7 > 1000) << 1) | (ads_millivolt_ch0 > 1000))
		{
			case 0:
				sprintf(msg + 128, "volt_0 = %7.3lf mV, volt_7 = %7.3lf mV\r\n", ads_millivolt_ch0,        ads_millivolt_ch7);
				break;
			case 1:
				sprintf(msg + 128, "volt_0 = %5.3lf  V, volt_7 = %7.3lf mV\r\n", ads_millivolt_ch0 / 1000, ads_millivolt_ch7);
				break;
			case 2:
				sprintf(msg + 128, "volt_0 = %5.3lf mV, volt_7 = %7.3lf  V\r\n", ads_millivolt_ch0,        ads_millivolt_ch7 / 1000);
				break;
			case 3:
				sprintf(msg + 128, "volt_0 = %5.3lf  V, volt_7 = %5.3lf  V\r\n", ads_millivolt_ch0 / 1000, ads_millivolt_ch7 / 1000);
				break;
			default:
				// 不可能
				break;
		}
		db9_sendstr(msg + 128);
		delay_ms(500);
    }
}





