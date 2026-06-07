// hal库
#include "stm32h750xx.h"
#include "stm32h7xx_hal.h"

// 核心设备
#include "mpu.h"

// 片上外设
#include "systick.h"
#include "tim2.h"
#include "tim3.h"
#include "tim4.h"
#include "tim5.h"

// 板上外设
#include "led.h"

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

uint8_t protect_init(void)
{
	FLASH_OBProgramInitTypeDef ob;
	HAL_StatusTypeDef status;

	// 读取当前选项字节状态
	HAL_FLASHEx_OBGetConfig(&ob);

	// 如果已经是Level 1保护，直接返回
	if (ob.RDPLevel == OB_RDP_LEVEL_1)
	{
		return 0; // 已保护
	}

	// 解锁Flash和选项字节
	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();

	// 配置 RDP Level 1
	ob.OptionType = OPTIONBYTE_RDP;
	ob.RDPLevel = OB_RDP_LEVEL_1;
	status = HAL_FLASHEx_OBProgram(&ob);

	// 保护失败
	if (status != HAL_OK)
	{
		// 编程失败，重新锁定并返回错误
		HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
		return 1;
	}
	else
	{
		// 启动选项字节加载（会触发系统复位）
		HAL_FLASH_OB_Launch();
		return 0;
	}
}


int main(void)
{
	uint8_t status = 0;
	machine_init();
	status = protect_init();
	delay_init();
	LED_Init();
	LED_Turn_Off();


	if (status == 0)
	{
		while(true)
		{
			delay_ms(500);
			LED_Toggle();
		}
	}
	else
	{
		LED_Turn_On();
		while (true)
		{
			delay_ms(500);
		}
	}
	return 0;
}

