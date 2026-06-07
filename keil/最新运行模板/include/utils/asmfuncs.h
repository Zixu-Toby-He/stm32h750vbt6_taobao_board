#ifndef __ASMFUNCS_H__
#define __ASMFUNCS_H__

#include "ebdtypes.h"

// 以下为汇编函数
#if defined(__clang__)                                      // 使用V6编译器(clang)
	void __attribute__((noinline)) WFI_SET(void);         // 执行 WFI 指令
	void __attribute__((noinline)) INTX_DISABLE(void);    // 关闭所有中断
	void __attribute__((noinline)) INTX_ENABLE(void);     // 开启所有中断
	void __attribute__((noinline)) MSR_MSP(u32 addr);     // 设置堆栈地址
#elif defined (__CC_ARM)                                    // 使用V5编译器(ARMCC)
	void WFI_SET(void);         // 执行 WFI 指令
	void INTX_DISABLE(void);    // 关闭所有中断
	void INTX_ENABLE(void);     // 开启所有中断
	void MSR_MSP(u32 addr);     // 设置堆栈地址
#endif

#endif
