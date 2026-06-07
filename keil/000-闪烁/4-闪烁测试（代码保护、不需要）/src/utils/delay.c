#include "systick.h"

#include "delay.h"

static void wait(void);

// 用于后续优化自动切换选择功能
typedef enum
{
	DELAY_SYSTICK,
}
delay_tool_t;
// static delay_tool_t current_tool;

static uint32_t periods_per_us;
static uint32_t periods_per_ms;
static uint32_t periods_per_25ms; // 480MHz ~ max < 35 ms

void delay_init()
{
	systick_init(SYSTICK_INIT_MODE_HLCK);
	periods_per_us    = get_systick_frequency() / 1000000;
	periods_per_ms    = get_systick_frequency() / 1000;
	periods_per_25ms  = get_systick_frequency() / 40;
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
	volatile uint16_t cnt;

	// 开始计时
	systick_turn_off();
	systick_assign_counting_ticks(periods_per_25ms);
	systick_turn_on();

	// 20 min 量级
	while(nmin > 20)
	{
		for(cnt = 48000; cnt; cnt--)
		{
			wait();
		}
		nmin -= 20;
	}
	// 1 min 等级
	while(nmin > 1)
	{
		for(cnt = 2400; cnt; cnt--)
		{
			wait();
		}
		nmin--;
	}
	#define ns nmin
	ns = nmin * 60;
	while(ns > 1)
	{
		for(cnt = 40; cnt; cnt--)
		{
			wait();
		}
		ns--;
	}
	// 百毫秒级（(0 ~ 10) * 100 ms）
	#define n100ms nmin
	n100ms = ns * 10; // 转化为 n100ms，此时
	#undef  ns
	while(n100ms > 0.25)
	{
		wait();
		n100ms -= 0.25;
	}
	// 毫秒级（0 ~ 25 ms）
	systick_turn_off();
	systick_assign_counting_ticks(n100ms * 100 * periods_per_ms);
	systick_turn_on();
	wait();

	#undef  n100ms
	// 完成
	systick_turn_off();
}

void delay_s(float ns)
{
	volatile uint8_t cnt;

	// 开始计时
	systick_turn_off();
	systick_assign_counting_ticks(periods_per_25ms);
	systick_turn_on();
	// 秒量级
	while(ns > 3)
	{
		for(cnt = 120; cnt; cnt--)
		{
			wait();
		}
		ns -= 3;
	}
	while(ns > 1)
	{
		for(cnt = 40; cnt; cnt--)
		{
			wait();
		}
		ns--;
	}
	// 百毫秒级（(0 ~ 10) * 100 ms）
	#define n100ms ns
	n100ms = ns * 10; // 转化为 n100ms，此时
	while(n100ms > 0.25)
	{
		wait();
		n100ms -= 0.25;
	}
	// 毫秒级（0 ~ 25 ms）
	systick_turn_off();
	systick_assign_counting_ticks(n100ms * 100 * periods_per_ms);
	systick_turn_on();
	wait();
	#undef  n100ms
	// 完成
	systick_turn_off();
}

void delay_ms(float nms)
{
	// 开始计时
	systick_turn_off();
	systick_assign_counting_ticks(periods_per_25ms);
	systick_turn_on();
	while(nms > 25)
	{
		wait();
		nms -= 25;
	}

	systick_turn_off();
	systick_assign_counting_ticks(nms * periods_per_ms);
	systick_turn_on();
	wait();

	// 完成
	systick_turn_off();
}

void delay_us(float nus)
{
	// 开始计时
	systick_assign_counting_ticks(periods_per_25ms);
	systick_turn_on();
	while(nus > 25000)
	{
		wait();
		nus -= 25000;
	}

	systick_turn_off();
	systick_assign_counting_ticks(nus * periods_per_us);
	systick_turn_on();
	wait();
	// 完成
	systick_turn_off();
}

static void wait(void)
{
	volatile uint32_t ctrl;
	do
	{
		ctrl = systick_get_ctrl();
	}
	while(
		systick_is_active(ctrl) &&
		(!(systick_is_timeout(ctrl)))
	);
}