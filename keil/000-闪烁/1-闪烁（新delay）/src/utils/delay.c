#include "stm32h7xx.h"
#include "delay.h"

// 最大计数值（24位计数器）
#define MAX_TICKS 0xFFFFFF

static uint32_t periods_per_us;
static uint32_t periods_per_ms;
static uint32_t periods_per_25ms; // 480MHz ~ max < 35 ms

// 内部函数声明
static void delay_25ms();            // 延时 25 ms
static void delay_n25ms(uint16_t n); // 延时 n * 25 ms，上限1638.4 s （约27.367 min）
#define     delay_ns(n)   delay_n25ms(40   * n)
#define     delay_nmin(n) delay_n25ms(2400 * n)



void delay_init(delay_mode_t mode)
{
	switch (mode)
	{
		case DELAY_MODE_HLCK:
			SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
			periods_per_us    = SystemCoreClock / 1000000;
			periods_per_ms    = SystemCoreClock / 1000;
			periods_per_25ms  = SystemCoreClock / 40;
			break;
		case DELAY_MODE_HLCK_DIV_8:
			SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
			periods_per_us    = SystemCoreClock / 8000000;
			periods_per_ms    = SystemCoreClock / 8000;
			periods_per_25ms  = SystemCoreClock / 320;
			break;
		default:
			break;
	}
}

void delay(float num, delay_unit_t unit)
{
	switch (unit)
	{
		case DELAY_UNIT_us:
			delay_us(num);
			break;
		case DELAY_UNIT_ms:
			delay_ms(num);
			break;
		case DELAY_UNIT_s:
			delay_s(num);
			break;
		case DELAY_UNIT_min:
			delay_min(num);
			break;
		default:
			// 无效单位处理
			break;
	}
}

void delay_min(float nmin)
{
	volatile uint32_t ctrl = 0; 
	uint16_t cnt;

	SysTick->LOAD = periods_per_25ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	// 20 min 量级
	while(nmin > 20)
	{
		for(cnt = 48000; cnt; cnt--)
		{
			do
			{
				ctrl = SysTick->CTRL;
			}
			while(
				(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
				(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
			);
		}
		nmin -= 20;
	}
	// 1 min 等级
	while(nmin > 1)
	{
		for(cnt = 2400; cnt; cnt--)
		{
			do
			{
				ctrl = SysTick->CTRL;
			}
			while(
				(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
				(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
			);
		}
		nmin--;
	}
	#define ns nmin
	ns = nmin * 60;
	while(ns > 1)
	{
		for(cnt = 40; cnt; cnt--)
		{
			do
			{
				ctrl = SysTick->CTRL;
			}
			while(
				(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
				(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
			);
		}
		ns--;
	}
	// 百毫秒级（(0 ~ 10) * 100 ms）
	#define n100ms nmin
	n100ms = ns * 10; // 转化为 n100ms，此时
	#undef  ns
	while(n100ms > 0.25)
	{
		do
		{
			ctrl = SysTick->CTRL;
		}
		while(
			(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
			(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
		);
		n100ms -= 0.25;
	}
	// 毫秒级（0 ~ 25 ms）
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
	SysTick->LOAD = n100ms * 100 * periods_per_ms;
	SysTick->VAL  = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		ctrl = SysTick->CTRL;
	}
	while(
		(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
		(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
	);
	#undef  n100ms
	// 完成
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);	//关闭计数器
}

void delay_s(float ns)
{
	volatile uint32_t ctrl = 0; 
	uint8_t cnt;
	// 开始计时
	SysTick->LOAD = periods_per_25ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	// 秒量级
	while(ns > 3)
	{
		for(cnt = 120; cnt; cnt--)
		{
			do
			{
				ctrl = SysTick->CTRL;
			}
			while(
				(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
				(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
			);
		}
		ns -= 3;
	}
	while(ns > 1)
	{
		for(cnt = 40; cnt; cnt--)
		{
			do
			{
				ctrl = SysTick->CTRL;
			}
			while(
				(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
				(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
			);
		}
		ns--;
	}
	// 百毫秒级（(0 ~ 10) * 100 ms）
	#define n100ms ns
	n100ms = ns * 10; // 转化为 n100ms，此时
	while(n100ms > 0.25)
	{
		do
		{
			ctrl = SysTick->CTRL;
		}
		while(
			(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
			(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
		);
		n100ms -= 0.25;
	}
	// 毫秒级（0 ~ 25 ms）
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
	SysTick->LOAD = n100ms * 100 * periods_per_ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		ctrl = SysTick->CTRL;
	}
	while(
		(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
		(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
	);
	#undef  n100ms
	// 完成
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);	//关闭计数器
}

void delay_ms(float nms)
{
	volatile uint32_t ctrl = 0; 
	
	// 开始计时
	SysTick->LOAD = periods_per_25ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(nms > 25)
	{
		do
		{
			ctrl = SysTick->CTRL;
		}
		while(
			(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
			(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
		);
		nms -= 25;
	}
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
	SysTick->LOAD = nms * periods_per_ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		ctrl = SysTick->CTRL;
	}
	while(
		(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
		(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
	);
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
}

void delay_us(float nus)
{
	volatile uint32_t ctrl = 0; 
	// 开始计时
	SysTick->LOAD = periods_per_25ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(nus > 25000)
	{
		do
		{
			ctrl = SysTick->CTRL;
		}
		while(
			(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
			(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
		);
		nus -= 25000;
	}
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
	SysTick->LOAD = nus * periods_per_us;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		ctrl = SysTick->CTRL;
	}
	while(
		(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
		(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
	);
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
}

//////////////////////////////////
// 内部静态函数
/////////////////////////////////
static void delay_25ms()
{
	uint32_t temp;
	SysTick->LOAD = periods_per_25ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		temp = SysTick->CTRL;
	}
	while(
		(temp & 0x01) &&         // 激活
		(!(temp & 1 << 16))      // 计时到 0
	);
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);	//关闭计数器
	SysTick->VAL   = 0;                             //清空计数器
}

static void delay_n25ms(uint16_t n)
{
	volatile uint32_t ctrl = 0;
	SysTick->LOAD = periods_per_25ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	for(__nop(); n; n--)
	{
		do
		{
			ctrl = SysTick->CTRL;
		}
		while(
			(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
			(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
		);
	}
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);	//关闭计数器

}
