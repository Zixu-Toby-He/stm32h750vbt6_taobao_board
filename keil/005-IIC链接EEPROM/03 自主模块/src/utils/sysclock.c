#include "sysclock.h"

void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{
	HAL_StatusTypeDef  ret = HAL_OK;
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};

	// 供应配置更新启用
	MODIFY_REG(PWR->CR3,PWR_CR3_SCUEN, 0);
	// 设置调压器输出电压级别，让器件以最大频率工作
	__HAL_PWR_VOLTAGESCALING_CONFIG(
		PWR_REGULATOR_VOLTAGE_SCALE1
	);// 设置调压器输出电压级别 1

	while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) {}

	// 初始化CPU，AHB和APB总线时钟
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;   // 选择时钟源为 HSE
	RCC_OscInitStruct.HSEState       = RCC_HSE_ON;               // 打开 HSE
	RCC_OscInitStruct.HSIState       = RCC_HSI_OFF;              // 关闭 HSI
	RCC_OscInitStruct.CSIState       = RCC_CSI_OFF;              // 关闭 CSI
	RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;               // 打开 PLL
	RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;        // PLL时钟源选择HSE

	RCC_OscInitStruct.PLL.PLLN = plln;
	RCC_OscInitStruct.PLL.PLLM = pllm;
	RCC_OscInitStruct.PLL.PLLP = pllp;
	RCC_OscInitStruct.PLL.PLLQ = pllq;
	RCC_OscInitStruct.PLL.PLLR = 2;                              // 外设时钟的分频系数 R

	RCC_OscInitStruct.PLL.PLLRGE    = RCC_PLL1VCIRANGE_2;      // PLL 时钟输入范围
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;         // PLL 时钟输出范围
	RCC_OscInitStruct.PLL.PLLFRACN  = 0;                       // 指定 PLL1 VCO 的乘数的小数部分。它应该是0到8191之间的值

	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);               // 初始化
	if(ret != HAL_OK) while(1) {}

	// 选中 PLLCLK 作为系统时钟源并且配置 HCLK，PCLK1 和 PCLK2
	RCC_ClkInitStruct.ClockType =
		RCC_CLOCKTYPE_HCLK    |
		RCC_CLOCKTYPE_SYSCLK  |
		RCC_CLOCKTYPE_PCLK1   |
		RCC_CLOCKTYPE_PCLK2   |
		RCC_CLOCKTYPE_D3PCLK1 |
		RCC_CLOCKTYPE_D1PCLK1
	;
	RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;    // 选择 PLLCLK 作为系统时钟的时钟源
	RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;            // 系统时钟分频器
	RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV2;              // AHB  时钟（HCLK）分频器，该时钟来自系统时钟（SYSCLK）
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;              // APB1 时钟（PCLK1）分频器，该时钟源自AHB时钟（HCLK）
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;              // APB2 时钟（PCLK2）分频器，该时钟源自AHB时钟（HCLK）
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;              // APB3 时钟（D1PCLK1）分频器，该时钟源自AHB时钟（HCLK）
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV4;              // APB4 时钟（D3PCLK1）分频器，该时钟源自AHB时钟（HCLK）
	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
	if(ret!=HAL_OK) while(1) {}

	__HAL_RCC_CSI_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	HAL_EnableCompensationCell();
}




