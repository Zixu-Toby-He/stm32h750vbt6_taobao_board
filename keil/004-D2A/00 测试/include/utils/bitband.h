#ifndef __BITBAND_H__
#define __BITBAND_H__

// 头文件自解释
#include <stm32h743xx.h>

// Cortex M7不支持位带操作，在此模拟位带操作
#define PAout_Set_1(n)   (GPIOA->ODR  |= (1 << (n)))  //输出
#define PBout_Set_1(n)   (GPIOB->ODR  |= (1 << (n)))  //输出
#define PCout_Set_1(n)   (GPIOC->ODR  |= (1 << (n)))  //输出
#define PDout_Set_1(n)   (GPIOD->ODR  |= (1 << (n)))  //输出
#define PEout_Set_1(n)   (GPIOE->ODR  |= (1 << (n)))  //输出
#define PFout_Set_1(n)   (GPIOF->ODR  |= (1 << (n)))  //输出
#define PGout_Set_1(n)   (GPIOG->ODR  |= (1 << (n)))  //输出
#define PHout_Set_1(n)   (GPIOH->ODR  |= (1 << (n)))  //输出
#define PIout_Set_1(n)   (GPIOI->ODR  |= (1 << (n)))  //输出
#define PJout_Set_1(n)   (GPIOJ->ODR  |= (1 << (n)))  //输出
#define PKout_Set_1(n)   (GPIOK->ODR  |= (1 << (n)))  //输出

#define PAout_Set_0(n)   (GPIOA->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PBout_Set_0(n)   (GPIOB->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PCout_Set_0(n)   (GPIOC->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PDout_Set_0(n)   (GPIOD->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PEout_Set_0(n)   (GPIOE->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PFout_Set_0(n)   (GPIOF->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PGout_Set_0(n)   (GPIOG->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PHout_Set_0(n)   (GPIOH->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PIout_Set_0(n)   (GPIOI->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PJout_Set_0(n)   (GPIOJ->ODR  &= (0xFFFF ^ (1 << (n))))  //输出
#define PKout_Set_0(n)   (GPIOK->ODR  &= (0xFFFF ^ (1 << (n))))  //输出

#define PAin_Get(n)      ((GPIOA->IDR >> n) & 1)  //输入 
#define PBin_Get(n)      ((GPIOB->IDR >> n) & 1)  //输入 
#define PCin_Get(n)      ((GPIOC->IDR >> n) & 1)  //输入 
#define PDin_Get(n)      ((GPIOD->IDR >> n) & 1)  //输入 
#define PEin_Get(n)      ((GPIOE->IDR >> n) & 1)  //输入 
#define PFin_Get(n)      ((GPIOF->IDR >> n) & 1)  //输入 
#define PGin_Get(n)      ((GPIOG->IDR >> n) & 1)  //输入 
#define PHin_Get(n)      ((GPIOH->IDR >> n) & 1)  //输入 
#define PIin_Get(n)      ((GPIOI->IDR >> n) & 1)  //输入 
#define PJin_Get(n)      ((GPIOJ->IDR >> n) & 1)  //输入 
#define PKin_Get(n)      ((GPIOK->IDR >> n) & 1)  //输入 



#endif
