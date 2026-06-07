#ifndef _SYS_H
#define _SYS_H
#include "stm32h7xx.h"
#include "core_cm7.h"
#include "stm32h7xx_hal.h"


//0,不支持os
//1,支持os
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持OS	
///////////////////////////////////////////////////////////////////////////////////
//定义一些常用的数据类型短关键字
#ifndef s32
typedef int32_t  s32;
#endif
#ifndef s16
typedef int16_t  s16;
#endif
#ifndef s8
typedef int8_t   s8;
#endif

#ifndef sc32
typedef const int32_t sc32;  
#endif
#ifndef sc16
typedef const int16_t sc16;
#endif
#ifndef sc8
typedef const int8_t  sc8;
#endif

#ifndef vs32
typedef __IO int32_t  vs32;
#endif
#ifndef vs16
typedef __IO int16_t  vs16;
#endif
#ifndef vs8
typedef __IO int8_t   vs8;
#endif

#ifndef vsc32
typedef __I int32_t vsc32;  
#endif
#ifndef vsc16
typedef __I int16_t vsc16; 
#endif
#ifndef vsc8
typedef __I int8_t  vsc8;   
#endif

#ifndef u32
typedef uint32_t  u32;
#endif
#ifndef u16
typedef uint16_t  u16;
#endif
#ifndef u8
typedef uint8_t   u8;
#endif

#ifndef uc32
typedef const uint32_t uc32;  
#endif
#ifndef uc16
typedef const uint16_t uc16;  
#endif
#ifndef uc8
typedef const uint8_t  uc8; 
#endif

#ifndef vu32
typedef __IO uint32_t  vu32;
#endif
#ifndef vu16
typedef __IO uint16_t  vu16;
#endif
#ifndef vu8
typedef __IO uint8_t   vu8;
#endif

#ifndef vuc32
typedef __I uint32_t vuc32;  
#endif
#ifndef vuc16
typedef __I uint16_t vuc16; 
#endif
#ifndef vuc8
typedef __I uint8_t  vuc8;  
#endif

#define ON	1
#define OFF	0
#define Write_Through() (*(__IO uint32_t*)0XE000EF9C=1UL<<2) //Cache透写模式

void Cache_Enable(void);                                    //使能STM32H7的L1-Cahce
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq); //配置系统时钟
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

