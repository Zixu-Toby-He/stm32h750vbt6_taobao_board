#ifndef __TIM4_H__
#define __TIM4_H__

#include "stm32h7xx.h"
#include "core_cm7.h"
#include "stm32h7xx_hal.h"

// 参数含义：ncount，一次中断多少次计数（整数毫秒通常设为毫秒ms数 * 10）
// 设定时间不宜超过 5 s（5000）
void TIM4_Init(float time_ms, uint16_t ncounts, void (*time_out_handler)(void));
// 重新初始化，实验证明使用init是一样的
void TIM4_ReInit(float time_ms, uint16_t ncounts, void (*time_out_handler)(void));

// 启动
void TIM4_Start(void);
// 停止
void TIM4_Stop(void);
// 暂停（暂停不能修改配置）
void TIM4_Pause(void);
// 继续计数
void TIM4_Resume(void);

// 重置定时器计数器
void TIM4_Reset(void);
// 获取当前计数值
uint32_t TIM4_GetCounter(void);


#endif




