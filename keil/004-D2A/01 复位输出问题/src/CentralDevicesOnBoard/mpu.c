#include "stm32h7xx_hal.h"

#include "stm32h7xx_hal_cortex.h"

#include "mpu.h"

//-----------------------------------------------------------------
// void MPU_Set_Protection(u32 Number,u32 BASEADDR,u32 SIZE,u8 AP,u8 DE,u8 S,u8 C,u8 B)
//-----------------------------------------------------------------
// 
// 函数功能: 配置MPU
// 入口参数:
//     u32 rnum      配置保护区域
//     u32 baseaddr  设置基地址
//     u32 size      设置保护区域的大小
//     u8 ap         设置访问权限
//     u8 de         是否允许指令访问
//     u8 sen        是否共享
//     u8 cen        是否缓存
//     u8 ben        是否缓冲
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void MPU_Set_Protection( u32 rnum, u32 baseaddr, u32 size, u8 ap, u8 de, u8 sen, u8 cen, u8 ben)
{
	MPU_Region_InitTypeDef MPU_Initure;
	
	HAL_MPU_Disable();                                 //配置MPU之前先关闭MPU,配置完成以后在使能MPU

	MPU_Initure.Enable           = MPU_REGION_ENABLE;                   // 激活该保护区域 
	MPU_Initure.Number           = rnum;                                // 设置保护区域
	MPU_Initure.BaseAddress      = baseaddr;                            // 设置基址
	MPU_Initure.Size             = size;                                // 设置保护区域大小
	MPU_Initure.SubRegionDisable = 0X00;                                // 禁止子区域
	MPU_Initure.TypeExtField     = MPU_TEX_LEVEL0;                      // 设置类型扩展域为level0
	MPU_Initure.AccessPermission = (u8)ap;                              // 设置访问权限
	MPU_Initure.DisableExec      = de;                                  // 是否允许指令访问（de_default：允许读取指令）
	MPU_Initure.IsShareable      = sen;                                 // 是否共用？
	MPU_Initure.IsCacheable      = cen;                                 // 是否缓存？   
	MPU_Initure.IsBufferable     = ben;                                 // 是否缓冲?
	HAL_MPU_ConfigRegion(&MPU_Initure);           // 配置 MPU
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);	      // 开启 MPU
}



//-----------------------------------------------------------------
// void MPU_Memory_Protection(void)
//-----------------------------------------------------------------
// 
// 函数功能: 设置需要保护的存储块
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 
//     必须对部分存储区域进行 MPU 保护,否则可能导致程序运行异常
//     比如 MCU 屏不显示，摄像头采集数据出错等等问题...
//
//-----------------------------------------------------------------
void MPU_Memory_Protection(void)
{
	//保护整个D1 SRAM 512KB
	MPU_Set_Protection(
		MPU_REGION_NUMBER1,         // NUMER1
		0x24000000,                 // 基地址
		MPU_REGION_SIZE_512KB,      // 长度
		MPU_REGION_FULL_ACCESS,     // 全访问
		de_default,
		MPU_ACCESS_SHAREABLE,       // 允许共享
		MPU_ACCESS_CACHEABLE,       // 允许cache
		MPU_ACCESS_NOT_BUFFERABLE   // 禁止缓冲
	);

	//保护SDRAM区域,共32M字节  
	MPU_Set_Protection(
		MPU_REGION_NUMBER2,         // NUMER2
		0XC0000000,                 // 基地址
		MPU_REGION_SIZE_32MB,       // 长度
		MPU_REGION_FULL_ACCESS,     // 全访问
		de_default,
		MPU_ACCESS_NOT_SHAREABLE,   // 禁止共享
		MPU_ACCESS_CACHEABLE,       // 允许cache
		MPU_ACCESS_BUFFERABLE       // 允许缓冲
	);
}


////// 从 System.c 复制，暂不清楚其具体影响
//////-----------------------------------------------------------------
////// void MPU_Memory_Protection(void)
//////-----------------------------------------------------------------
////// 
////// 函数功能: 设置需要的保护区域，AXI SRAM和FMC
////// 入口参数: 无
////// 返 回 值: 无
////// 注意事项: 无
//////
//////-----------------------------------------------------------------
////void MPU_Memory_Protection(void)
////{
////	// 配置AXI SRAM，共512KB字节，全访问，允许指令访问，禁止共享，允许缓存，允许缓冲
////	MPU_Set_Protection(
////		MPU_REGION_NUMBER0,
////		0x24000000,
////		MPU_REGION_SIZE_512KB,
////		MPU_REGION_FULL_ACCESS,
////		MPU_INSTRUCTION_ACCESS_ENABLE,
////		MPU_ACCESS_NOT_SHAREABLE,
////		MPU_ACCESS_CACHEABLE,
////		MPU_ACCESS_BUFFERABLE
////	);
////
////	// 配置FMC，共64MB字节，全访问，允许指令访问，禁止共享，禁止缓存，允许缓冲
////	MPU_Set_Protection(
////		MPU_REGION_NUMBER1,
////		0x60000000,
////		MPU_REGION_SIZE_64MB,
////		MPU_REGION_FULL_ACCESS,
////		MPU_INSTRUCTION_ACCESS_ENABLE,
////		MPU_ACCESS_NOT_SHAREABLE,
////		MPU_ACCESS_NOT_CACHEABLE,
////		MPU_ACCESS_BUFFERABLE
////	);
////}
