#ifndef __CACHE_H__
#define __CACHE_H__

#include "ebdtypes.h"

#define Write_Through() (*((__IO uint32_t*)0XE000EF9C) = (1UL << 2)) // Cache透写模式

//-----------------------------------------------------------------
// void CPU_CACHE_Enable(void)
//-----------------------------------------------------------------
// 
// 函数功能: 启用CPU缓存
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void CPU_CACHE_Enable(void);

//判断I_Cache是否打开
//返回值:0 关闭，1 打开
u8 Get_ICacheSta(void);
// 判断 D_Cache 是否打开
// 返回值:0 关闭，1 打开
u8 Get_DCacheSta(void);

#endif


