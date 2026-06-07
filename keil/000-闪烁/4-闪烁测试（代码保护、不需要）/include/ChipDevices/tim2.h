#ifndef __TIM2_H__
#define __TIM2_H__

#include "stm32h7xx.h"
#include "core_cm7.h"
#include "stm32h7xx_hal.h"

// 参数含义：ncount，一次中断多少次计数（整数毫秒通常设为毫秒ms数 * 10）
// 设定时间不宜超过 5 s（5000）
void TIM2_Init(float time_ms, uint16_t ncounts, void (*time_out_handler)(void));

#endif
