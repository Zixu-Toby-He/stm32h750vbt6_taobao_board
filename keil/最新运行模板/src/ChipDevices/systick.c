#include "stm32h7xx.h"

#include "systick.h"

static uint32_t systick_freq;
#define periods_per_s systick_freq
static uint32_t periods_per_us;
static uint32_t periods_per_ms;

void systick_init(systick_init_mode_t mode)
{
	switch (mode)
	{
		case SYSTICK_INIT_MODE_HLCK:
			SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
			systick_freq      = SystemCoreClock;
			periods_per_us    = SystemCoreClock / 1000000;
			periods_per_ms    = SystemCoreClock / 1000;
			break;
		case SYSTICK_INIT_MODE_HLCK_DIV_8:
			SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
			systick_freq      = SystemCoreClock / 8;
			periods_per_us    = SystemCoreClock / 8000000;
			periods_per_ms    = SystemCoreClock / 8000;
			break;
		default:
			break;
	}
}


// 以下接口不会检查范围，超过范围则产生未定义行为
void systick_assign_counting_ticks(uint32_t nticks)
{
	SysTick->LOAD = nticks;
	SysTick->VAL = 0;
}
uint32_t get_systick_frequency(void)
{
	return systick_freq;
}
uint32_t get_systick_counts_per_s(void)
{
	return systick_freq;
}
uint32_t get_systick_counts_per_ms(void)
{
	return periods_per_ms;
}
uint32_t get_systick_counts_per_us(void)
{
	return periods_per_us;
}

//// 考虑到SysTick执行与时间高度相关，此处实现采用宏函数
////void systick_turn_on()
////{
////	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
////}
////void systick_turn_off(void)
////{
////	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
////}
////bool systick_is_active(void)
////{
////	volatile uint32_t ctrl = SysTick->CTRL;
////	return (
////		(ctrl   & SysTick_CTRL_ENABLE_Msk) &&       // 当前是激活状态
////		(!(ctrl & SysTick_CTRL_COUNTFLAG_Msk))      // 计时已经到 0
////	);
////}

