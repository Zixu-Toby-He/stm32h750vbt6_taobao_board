
#ifndef _SYSTEM_H
#define _SYSTEM_H
#include "stm32h7xx.h"
//-----------------------------------------------------------------
// 定义一些常用的数据类型短关键字 
//-----------------------------------------------------------------
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

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern void SystemClock_Config(void);// 时钟系统配置
extern void CPU_CACHE_Enable(void);
extern void MPU_Set_Protection(u32 Number,u32 BASEADDR,u32 SIZE,u8 AP,u8 DE,u8 S,u8 C,u8 B);
extern void MPU_Memory_Protection(void);
#endif


