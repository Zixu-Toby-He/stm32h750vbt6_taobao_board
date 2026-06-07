#ifndef __DELAY_H__
#define __DELAY_H__

////////////////////////////////////////////////////////////
// 当前 delay 模块完全基于 SysTick 实现，其功能实现并非最佳
// 故长时间 delay 请考虑其他方法
// 1 h 以上的延时不建议使用本库，同时将不会对如此长时间以外的数值进行范围检查
////////////////////////////////////////////////////////////

#include "bool.h"

typedef enum
{
	DELAY_MODE_HLCK       = 0,
	DELAY_MODE_HLCK_DIV_8 = 1
}
delay_mode_t;
typedef enum
{
	DELAY_UNIT_us = 1,
	DELAY_UNIT_ms,
	DELAY_UNIT_s,
	DELAY_UNIT_min,
}
delay_unit_t;

// 使用查询实现
void delay_init(delay_mode_t);

void delay(float num, delay_unit_t unit);

void delay_min( float nmin);
void delay_s(   float ns);
void delay_ms(  float nms);
void delay_us(  float nus);

#endif
