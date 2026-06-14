#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stdint.h>

#include "ebdtypes.h"
#include "time_unit.h"

// 最大计数值（24位计数器）
#define SYSTICK_MAX_TICKS 0xFFFFFF

typedef enum
{
	SYSTICK_INIT_MODE_HLCK       = 0,
	SYSTICK_INIT_MODE_HLCK_DIV_8 = 1
}
systick_init_mode_t;

void systick_init(systick_init_mode_t);

// 布置计数任务
// 以下接口不会检查范围，超过范围则产生未定义行为
void systick_assign_counting_ticks(uint32_t nticks);

// 开启关闭（根据提升效率准则采用宏函数实现）
#define systick_turn_on()   SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk
#define systick_turn_off()  SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk)

// 获取状态与判断
// 注意：systick_get_ctrl() 与 systick_get_val() 禁止与其他表达式嵌套，若需要则单独使用一个变量承接！！！
#define systick_get_val()        (SysTick->VAL)
#define systick_get_ctrl()       (SysTick->CTRL)
#define systick_is_active(ctrl)  ((ctrl) & SysTick_CTRL_ENABLE_Msk)
#define systick_is_timeout(ctrl) ((ctrl) & SysTick_CTRL_COUNTFLAG_Msk)



uint32_t get_systick_frequency(void);
uint32_t get_systick_counts_per_s(void);
uint32_t get_systick_counts_per_ms(void);
uint32_t get_systick_counts_per_us(void);

#endif




//__inline void systick_assign_counting_ms(uint8_t nms);
//__inline void systick_assign_counting_us(uint16_t nus);
//void systick_turn_on(void);
//void systick_turn_off(void);
