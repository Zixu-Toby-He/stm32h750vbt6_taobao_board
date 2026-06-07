#include "ebdtypes.h"

#include "sys.h"



//-----------------------------------------------------------------
// void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
//-----------------------------------------------------------------
// 
// 函数功能: 系统时钟初始化
// 入口参数: 无
// 返 回 值: 无
// 注意事项:
//            System Clock source  = PLL (HSE) 25MHz晶振
//	          SYSCLK(Hz)           = 480 000 000 (CPU Clock)
//	          HCLK(Hz)             = 240 000 000 (AXI and AHBs Clock)
//	          AHB Prescaler        = 2
//	          D1 APB3 Prescaler    = 2 (APB3 Clock  100MHz)
//	          D2 APB1 Prescaler    = 2 (APB1 Clock  100MHz)
//	          D2 APB2 Prescaler    = 2 (APB2 Clock  100MHz)
//	          D3 APB4 Prescaler    = 2 (APB4 Clock  100MHz)
//	          HSE Frequency(Hz)    = 2 5000 000
//	          PLL_N                = 192（可修改）
//	          PLL_M                = 5（可修改）
//	          PLL_P                = 2（可修改）
//	          PLL_Q                = 2（可修改）
//	          PLL_R                = 2
//	          VDD(V)               = 3.3
//	          Flash Latency(WS)    = 2
//
//-----------------------------------------------------------------
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



//-----------------------------------------------------------------
// void CPU_CACHE_Enable(void)
//-----------------------------------------------------------------
// 
// 函数功能: 启用CPU缓存
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void CPU_CACHE_Enable(void)
{
	SCB_EnableICache();    // 使能指令缓存
	SCB_EnableDCache();    // 使能数据缓存
	SCB->CACR|=1<<2;       // 设置 D-Cache 为 Write Through，保证数据的一致性
}


//判断I_Cache是否打开
//返回值:0 关闭，1 打开
u8 Get_ICahceSta(void)
{
	u8 sta;
	sta=((SCB->CCR)>>17)&0X01;
	return sta;
}

//判断I_Dache是否打开
//返回值:0 关闭，1 打开
u8 Get_DCahceSta(void)
{
	u8 sta;
	sta=((SCB->CCR)>>16)&0X01;
	return sta;
}


#ifdef  USE_FULL_ASSERT
//当编译提示出错的时候此函数用来报告错误的文件和所在行
//file：指向源文件
//line：指向在文件中的行数
void assert_failed(uint8_t* file, uint32_t line)
{
	while(1)
	{
	}
}
#endif

#if defined(__clang__) //使用V6编译器(clang)
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI
void __attribute__((noinline)) WFI_SET(void)
{
	__asm__("wfi");
}

//关闭所有中断(但是不包括fault和NMI中断)
void __attribute__((noinline)) INTX_DISABLE(void)
{
	__asm__(
		"cpsid i \t\n"
		"bx lr"
	);
}

//开启所有中断
void __attribute__((noinline)) INTX_ENABLE(void)
{
	__asm__("cpsie i \t\n"
		"bx lr"
	);
}

//设置栈顶地址
//addr:栈顶地址
void __attribute__((noinline)) MSR_MSP(u32 addr)
{
	__asm__("msr msp, r0 \t\n"
		"bx r14"
	);
}
#elif defined (__CC_ARM)    //使用V5编译器(ARMCC)

// THUMB指令不支持汇编内联
// 采用如下方法实现执行汇编指令WFI
__asm void WFI_SET(void)
{
	WFI;
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr)
{
	MSR MSP, r0 //set Main Stack value
	BX r14
}
#endif
