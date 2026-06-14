#ifndef _SYS_H
#define _SYS_H

#include <stdint.h>

#include "stm32h750xx.h"
#include "core_cm7.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

#include "ebdtypes.h"


//-----------------------------------------------------------------
// void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
//-----------------------------------------------------------------
// 
// 函数功能: 系统时钟初始化
// 入口参数: 无
// 返 回 值: 无
// 注意事项:
//            System Clock source  = PLL (HSE) 25MHz晶振
//            SYSCLK(Hz)           = 480 000 000 (CPU Clock)
//            HCLK(Hz)             = 240 000 000 (AXI and AHBs Clock)
//            AHB Prescaler        = 2
//            D1 APB3 Prescaler    = 2 (APB3 Clock  100MHz)
//            D2 APB1 Prescaler    = 2 (APB1 Clock  100MHz)
//            D2 APB2 Prescaler    = 2 (APB2 Clock  100MHz)
//            D3 APB4 Prescaler    = 2 (APB4 Clock  100MHz)
//            HSE Frequency(Hz)    = 2 5000 000
//            PLL_N                = plln（推荐值：192）
//            PLL_M                = pllm（推荐值：5）
//            PLL_P                = pllp（推荐值：2）
//            PLL_Q                = pllq（推荐值：2）
//            PLL_R                = 2
//            VDD(V)               = 3.3
//            Flash Latency(WS)    = 2
//
//-----------------------------------------------------------------
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq);


#endif

