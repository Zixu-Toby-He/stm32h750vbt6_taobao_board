#ifndef __BITBAND_H__
#define __BITBAND_H__

// 头文件自解释
#include <stm32f10x.h>

// 位带操作,实现51类似的GPIO控制功能
// 具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
// IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE + 0x14) // 0x58020014
#define GPIOB_ODR_Addr    (GPIOB_BASE + 0x14) // 0x58020414
#define GPIOC_ODR_Addr    (GPIOC_BASE + 0x14) // 0x58020814
#define GPIOD_ODR_Addr    (GPIOD_BASE + 0x14) // 0x58020C14
#define GPIOE_ODR_Addr    (GPIOE_BASE + 0x14) // 0x58021014
#define GPIOF_ODR_Addr    (GPIOF_BASE + 0x14) // 0x58021414
#define GPIOG_ODR_Addr    (GPIOG_BASE + 0x14) // 0x58021814
#define GPIOH_ODR_Addr    (GPIOH_BASE + 0x14) // 0x58021C14
#define GPIOI_ODR_Addr    (GPIOI_BASE + 0x14) // 0x58022014
#define GPIOJ_ODR_Addr    (GPIOJ_BASE + 0x14) // 0x58022414
#define GPIOK_ODR_Addr    (GPIOK_BASE + 0x14) // 0x58022814


#define GPIOA_IDR_Addr    (GPIOA_BASE + 0x10) // 0x58020010
#define GPIOB_IDR_Addr    (GPIOB_BASE + 0x10) // 0x58020410
#define GPIOC_IDR_Addr    (GPIOC_BASE + 0x10) // 0x58020810
#define GPIOD_IDR_Addr    (GPIOD_BASE + 0x10) // 0x58020C10
#define GPIOE_IDR_Addr    (GPIOE_BASE + 0x10) // 0x58021010
#define GPIOF_IDR_Addr    (GPIOF_BASE + 0x10) // 0x58021410
#define GPIOG_IDR_Addr    (GPIOG_BASE + 0x10) // 0x58021810
#define GPIOH_IDR_Addr    (GPIOH_BASE + 0x10) // 0x58021C10
#define GPIOI_IDR_Addr    (GPIOI_BASE + 0x10) // 0x58022010
#define GPIOJ_IDR_Addr    (GPIOJ_BASE + 0x10) // 0x58022410
#define GPIOK_IDR_Addr    (GPIOK_BASE + 0x10) // 0x58022810
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr, n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr, n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr, n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr, n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr, n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr, n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr, n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr, n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr, n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr, n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr, n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr, n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr, n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr, n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr, n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr, n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr, n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr, n)  //输入

#define PJout(n)   BIT_ADDR(GPIOJ_ODR_Addr, n)  //输出 
#define PJin(n)    BIT_ADDR(GPIOJ_IDR_Addr, n)  //输入

#define PKout(n)   BIT_ADDR(GPIOK_ODR_Addr, n)  //输出 
#define PKin(n)    BIT_ADDR(GPIOK_IDR_Addr, n)  //输入

#endif
