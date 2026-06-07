#include "gpio_input.h"
#include "gpio_output.h"
#include "led.h"
/**
  * 函数功能: 板载按键IO引脚初始化.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：使用宏定义方法代替具体引脚号，方便程序移植，只要简单修改bsp_gpio.h
  *           文件相关宏定义就可以方便修改引脚。
  */
void INPUT_GPIO_Init(void)
{
	/* 定义IO硬件初始化结构体变量 */
	GPIO_InitTypeDef GPIO_InitStruct={0};

	/* 使能(开启)INPUT引脚对应IO端口时钟 */  
	INPUT1_RCC_CLK_ENABLE();
	INPUT2_RCC_CLK_ENABLE();
	INPUT3_RCC_CLK_ENABLE();
	INPUT4_RCC_CLK_ENABLE();
	INPUT5_RCC_CLK_ENABLE();
	INPUT6_RCC_CLK_ENABLE();
	INPUT7_RCC_CLK_ENABLE();
	INPUT8_RCC_CLK_ENABLE();
	INPUT9_RCC_CLK_ENABLE();
	INPUT10_RCC_CLK_ENABLE();
	INPUT11_RCC_CLK_ENABLE();
	INPUT12_RCC_CLK_ENABLE();
	INPUT13_RCC_CLK_ENABLE();
	INPUT14_RCC_CLK_ENABLE();
	INPUT15_RCC_CLK_ENABLE();
	INPUT16_RCC_CLK_ENABLE();

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT1_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT1_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT2_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT2_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT3_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT3_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT4_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT4_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT5_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT5_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT6_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT6_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT7_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT7_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT8_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT8_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT9_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT9_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT10_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT10_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT11_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT11_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT12_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT12_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT13_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT13_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT14_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT14_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT15_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT15_GPIO, &GPIO_InitStruct);

	/* 配置INPUT GPIO:输入上拉模式 */
	GPIO_InitStruct.Pin = INPUT16_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(INPUT16_GPIO, &GPIO_InitStruct);
}

/**
  * 函数功能: 读取输入INPUT1的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT1_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT1_GPIO,INPUT1_GPIO_PIN)==INPUT1_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT1_GPIO,INPUT1_GPIO_PIN)==INPUT1_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT2的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT2_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT2_GPIO,INPUT2_GPIO_PIN)==INPUT2_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT2_GPIO,INPUT2_GPIO_PIN)==INPUT2_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT3的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT3_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT3_GPIO,INPUT3_GPIO_PIN)==INPUT3_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT3_GPIO,INPUT3_GPIO_PIN)==INPUT3_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT4的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT4_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT4_GPIO,INPUT4_GPIO_PIN)==INPUT4_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT4_GPIO,INPUT4_GPIO_PIN)==INPUT4_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT5的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT5_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT5_GPIO,INPUT5_GPIO_PIN)==INPUT5_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT5_GPIO,INPUT5_GPIO_PIN)==INPUT5_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT6的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT6_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT6_GPIO,INPUT6_GPIO_PIN)==INPUT6_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT6_GPIO,INPUT6_GPIO_PIN)==INPUT6_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT7的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT7_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT7_GPIO,INPUT7_GPIO_PIN)==INPUT7_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT7_GPIO,INPUT7_GPIO_PIN)==INPUT7_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT8的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT8_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT8_GPIO,INPUT8_GPIO_PIN)==INPUT8_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT8_GPIO,INPUT8_GPIO_PIN)==INPUT8_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}
/**
  * 函数功能: 读取输入INPUT5的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT9_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT9_GPIO,INPUT9_GPIO_PIN)==INPUT9_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT9_GPIO,INPUT9_GPIO_PIN)==INPUT9_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT6的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT10_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT10_GPIO,INPUT10_GPIO_PIN)==INPUT10_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT10_GPIO,INPUT10_GPIO_PIN)==INPUT10_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT7的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT11_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT11_GPIO,INPUT11_GPIO_PIN)==INPUT11_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT11_GPIO,INPUT11_GPIO_PIN)==INPUT11_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT8的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT12_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT12_GPIO,INPUT12_GPIO_PIN)==INPUT12_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT12_GPIO,INPUT12_GPIO_PIN)==INPUT12_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

GPIOState_TypeDef INPUT13_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT13_GPIO,INPUT13_GPIO_PIN)==INPUT13_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT13_GPIO,INPUT13_GPIO_PIN)==INPUT13_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT4的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT14_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT14_GPIO,INPUT14_GPIO_PIN)==INPUT14_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT14_GPIO,INPUT14_GPIO_PIN)==INPUT14_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT5的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT15_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT15_GPIO,INPUT15_GPIO_PIN)==INPUT15_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT15_GPIO,INPUT15_GPIO_PIN)==INPUT15_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

/**
  * 函数功能: 读取输入INPUT6的状态
  * 输入参数：无
  * 返 回 值: GPIO_INACTIVE：无效电平；
  *           GPIO_ACTIVE  ：有效电平
  * 说    明：无。
  */
GPIOState_TypeDef INPUT16_StateRead(void)
{
	/* 读取此时电平并判断是否为有效，如果为有效电平状态进入函数内 */
	if(HAL_GPIO_ReadPin(INPUT16_GPIO,INPUT16_GPIO_PIN)==INPUT16_ACTIVE_LEVEL)
	{
		/* 延时一小段时间，消除抖动 */
		HAL_Delay(20);
		/* 延时时间后再判断电平状态，如果还是有效电平说明确实为有限电平 */
		if(HAL_GPIO_ReadPin(INPUT16_GPIO,INPUT16_GPIO_PIN)==INPUT16_ACTIVE_LEVEL)
		{
			/* 输入INPUT扫描完毕，确定输入INPUT出现有效电平 */
			return GPIO_ACTIVE;
		}
	}
	/* 输入处于无效电平，返回无效状态 */
	return GPIO_INACTIVE;
}

void input(void)
{
	if(INPUT1_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT1_HIGH();
	}
	if(INPUT2_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT2_HIGH();
	}
	if(INPUT3_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT3_HIGH();
	}
	if(INPUT4_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT4_HIGH();
	}
	if(INPUT5_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT5_HIGH();
	}
	if(INPUT6_StateRead()==GPIO_ACTIVE)
	{
 		LED0_Toggle;        //LED0反转
		OUTPUT6_HIGH();
	}
	if(INPUT7_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT7_HIGH();
	}
	if(INPUT8_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT8_HIGH();
	}	
	if(INPUT9_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT9_HIGH();
	}
	if(INPUT10_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT10_HIGH();
	}
	if(INPUT11_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT11_HIGH();
	}
	if(INPUT12_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT12_HIGH();
	}
	if(INPUT13_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT13_HIGH();
	}
	if(INPUT14_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT14_HIGH();
	}
	if(INPUT15_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT15_HIGH();
	}
	if(INPUT16_StateRead()==GPIO_ACTIVE)
	{
		LED0_Toggle;        //LED0反转
		OUTPUT16_HIGH();
	}	
}

