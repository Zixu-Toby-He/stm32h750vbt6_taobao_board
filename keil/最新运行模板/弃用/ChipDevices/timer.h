#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

// 定时器初始化
void TIM3_Init(    u16 arr, u16 psc, void (*time_out_handler)(void));
void TIM3_PWM_Init(u16 arr, u16 psc, void (*time_out_handler)(void));
void TIM_SetTIM3Compare4(u32 compare);
#endif

