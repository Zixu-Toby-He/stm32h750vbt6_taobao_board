#include <stdlib.h>

#include "sys.h"
#include "sp232.h"
#include "systick.h"

#include "msg.h"

#include "ads8688.h"
#include "dac.h"

// 当前程序不接收信息
void msghandler(uint8_t _msg_) {}


void init()
{
	HAL_Init();                           // 初始化 HAL 库
	CPU_CACHE_Enable();                   // 打开 L1-Cache
	Stm32_Clock_Init(192, 5, 2, 2);       // 设置时钟，480MHz
	systick_init(SYSTICK_INIT_MODE_HLCK);
	db9_init(115200, msghandler);
}

static volatile uint64_t a = 0;
void f(void)
{
	a++;
}


uint32_t measure_time(void)
{
	volatile uint32_t t_start = 0;
	volatile uint32_t t_end   = 0;

	volatile uint64_t a = 1;

	t_start = systick_get_val();
	db9_send('0');
	db9_send('1');
	db9_send('2');
	db9_send('3');
	db9_send('4');
	db9_send('5');
	db9_send('6');
	db9_send('7');
	db9_send('8');
	db9_send('9');
	db9_send('\r');
	db9_send('\n');
	t_end = systick_get_val();
	return t_start - t_end;
}

int main(void)
{
	volatile uint64_t a = 0;
	volatile uint64_t b = 0;
	volatile uint64_t c = 0;

	volatile uint32_t t[16] = {
		SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS,
		SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS,
		SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS,
		SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS, SYSTICK_MAX_TICKS
	};
	
	init();
	DAC_Init(DAC1_CH1);


	systick_turn_off();
	systick_assign_counting_ticks(SYSTICK_MAX_TICKS);
	systick_turn_on();
	for (size_t i = 0; i < 16; i++)
	{
		t[i] = measure_time();
	}
	
	systick_turn_off();

	sprintf(
		str,
		"%u, %u, %u, %u, %u, %u, %u, %u,\r\n"
		"%u, %u, %u, %u, %u, %u, %u, %u,\r\n",
		t[ 0], t[ 1], t[ 2], t[ 3],
		t[ 4], t[ 5], t[ 6], t[ 7],
		t[ 8], t[ 9], t[10], t[11],
		t[12], t[13], t[14], t[15]
	);
	db9_sendstr(str);

	return 0;
}

