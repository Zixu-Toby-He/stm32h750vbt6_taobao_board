#ifndef _TIMER_H
#define _TIMER_H

#include "stm32h750xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_tim.h"

#include "ebdtypes.h"

extern TIM_HandleTypeDef TIM3_Handler;      // 定时器 3 PWM 句柄
extern TIM_OC_InitTypeDef TIM3_CH4Handler; 	// 定时器 3 通道 4 句柄

void TIM3_Init(u16 arr,u16 psc);    		// 定时器初始化
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM3Compare4(u32 compare);
#endif

