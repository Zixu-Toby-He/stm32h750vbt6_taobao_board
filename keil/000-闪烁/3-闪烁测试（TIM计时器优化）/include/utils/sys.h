#ifndef _SYS_H
#define _SYS_H

#include <stdint.h>

#include "stm32h750xx.h"
#include "core_cm7.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

#include "ebdtypes.h"

//0,不支持os
//1,支持os
#define SYSTEM_SUPPORT_OS		0		// 定义系统文件夹是否支持OS	

#define ON	1
#define OFF	0
#define Write_Through() (*(__IO uint32_t*)0XE000EF9C=1UL<<2) // Cache透写模式

void CPU_CACHE_Enable(void);                                    // 使能 STM32H7 的 L1-Cahce
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq);     // 配置系统时钟
u8 Get_ICahceSta(void); //判断I_Cache是否打开
u8 Get_DCahceSta(void); //判断I_Dache是否打开

#if defined(__clang__)                                      // 使用V6编译器(clang)
void __attribute__((noinline)) WFI_SET(void);
void __attribute__((noinline)) INTX_DISABLE(void);
void __attribute__((noinline)) INTX_ENABLE(void);
void __attribute__((noinline)) MSR_MSP(u32 addr);
#elif defined (__CC_ARM)                                    // 使用V5编译器(ARMCC)
//以下为汇编函数
void WFI_SET(void);		                                    //执行WFI指令
void INTX_DISABLE(void);                                    //关闭所有中断
void INTX_ENABLE(void);	                                    //开启所有中断
void MSR_MSP(u32 addr);	                                    //设置堆栈地址 
#endif


#endif

