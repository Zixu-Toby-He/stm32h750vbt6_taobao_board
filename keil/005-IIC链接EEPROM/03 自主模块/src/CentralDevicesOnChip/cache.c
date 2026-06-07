#include "stm32h750xx.h"
#include "core_cm7.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

#include "cache.h"
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
void CPU_CACHE_Enable(void)
{
	SCB_EnableICache();    // 使能指令缓存
	SCB_EnableDCache();    // 使能数据缓存
	SCB->CACR |= 1<<2;       // 设置 D-Cache 为 Write Through，保证数据的一致性
}


//判断I_Cache是否打开
//返回值:0 关闭，1 打开
u8 Get_ICacheSta(void)
{
	u8 sta;
	sta = ((SCB->CCR) >> 17) & 0X01;
	return sta;
}

// 判断 D_Cache 是否打开
// 返回值:0 关闭，1 打开
u8 Get_DCacheSta(void)
{
	u8 sta;
	sta = ((SCB->CCR) >> 16) & 0X01;
	return sta;
}



