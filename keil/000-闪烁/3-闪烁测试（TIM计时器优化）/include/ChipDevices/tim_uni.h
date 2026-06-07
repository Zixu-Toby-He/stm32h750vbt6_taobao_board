#ifndef __TIM_UNI_H__
#define __TIM_UNI_H__

#include "stm32h7xx.h"
#include "core_cm7.h"
#include "stm32h7xx_hal.h"

// 定时器计数完成默认函数
void timeupevent_default(void);

typedef enum
{
	tim_select_none     = 0x000,
	tim_select_tim1_h   = 0x001,  // 高级控制定时器
	
	tim_select_tim2_g   = 0x002,  // 通用定时器
	tim_select_tim3_g   = 0x003,  // 通用定时器
	tim_select_tim4_g   = 0x004,  // 通用定时器
	tim_select_tim5_g   = 0x005,  // 通用定时器

	tim_select_tim6_b   = 0x006,  // 基本定时器
	tim_select_tim7_b   = 0x007,  // 基本定时器

	tim_select_tim8_h   = 0x008,  // 高级控制定时器

	tim_select_tim12_g  = 0x00C,  // 通用定时器
	tim_select_tim13_g  = 0x00D,  // 通用定时器
	tim_select_tim14_g  = 0x00E,  // 通用定时器
	tim_select_tim15_g  = 0x00F,  // 通用定时器
	tim_select_tim16_g  = 0x010,  // 通用定时器
	tim_select_tim17_g  = 0x011,  // 通用定时器

	tim_select_lptim1_l = 0x101,  // 低功耗定时器
	tim_select_lptim2_l = 0x102,  // 低功耗定时器
	tim_select_lptim3_l = 0x103,  // 低功耗定时器
	tim_select_lptim4_l = 0x104,  // 低功耗定时器
	tim_select_lptim5_l = 0x105,  // 低功耗定时器
}
tim_select_t;
typedef struct 
{
	tim_select_t tim_select;
	float T_ms;
	void (*timeouthandler)(void);
}
tim_uni_t;

// 参数格式：{ status_tim, status_tim, ... , {0, NULL} }
// 最多初始化 19 个，不会对参数格式进行检查，请务必按格式赋值
void tim_uni_init(tim_uni_t*);
void tim_uni_register_many(tim_uni_t*);
void tim_uni_register(tim_uni_t);

// 系统调用，导入头文件方便链接
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *tim_handle);

#endif

