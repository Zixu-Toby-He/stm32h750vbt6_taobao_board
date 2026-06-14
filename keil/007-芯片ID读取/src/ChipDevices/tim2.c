#include "ebdtypes.h"

#include "tim_uni.h"

#include "tim2.h"

// #define DEBUG
#ifdef DEBUG
#include <stdlib.h>
#include "sp232.h"
#endif

static TIM_HandleTypeDef  htim;      //定时器句柄
//static TIM_OC_InitTypeDef hch4;      // 定时器3通道4句柄

// 定时器 3 在 APB1 上，该表达式可以计算其时钟周期
static uint32_t get_tim2_clock(void)
{
	uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();  // 获取PCLK1频率
	uint32_t hclk = HAL_RCC_GetHCLKFreq();    // 获取HCLK频率

	// 检查APB1预分频系数是否为1
	return (pclk1 < hclk) ? (pclk1 * 2) : pclk1;
}


// 定时器溢出时间计算方法:Tout = ((arr + 1) * ( psc + 1)) / Ft us.
// Ft = 定时器工作频率，单位:Mhz
// 参数含义：ncount，一次中断多少次计数（整数毫秒通常设为毫秒ms数）
// 符号约定：period —— 1个时钟周期；count —— 分频计数 +1；time —— 一次中断
// 设定时间不宜超过 5 s（5000）
void TIM2_Init(float time_ms, uint16_t ncounts, void (*time_out_handler)(void))
{
	tim_uni_t info_tim_uni;
	
	uint32_t total_period;
	uint16_t periods_per_count = 0;  // 一次循环
	uint16_t counts_per_inter = 0;


	// 总周期数
	total_period = (uint32_t) (time_ms * get_tim2_clock() * 1e-3f);
	counts_per_inter = ncounts;
	periods_per_count = total_period / counts_per_inter;


	htim.Instance           = TIM2;
	htim.Init.Prescaler     = periods_per_count - 1;   // 分频
	htim.Init.CounterMode   = TIM_COUNTERMODE_UP;      // 向上计数
	htim.Init.Period        = counts_per_inter  - 1;   // 自动装填值
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;  // 时钟分频因子

	
	info_tim_uni.T_ms           = time_ms;
	info_tim_uni.tim_select     = tim_select_tim2_g;
	info_tim_uni.timeouthandler = time_out_handler;
	tim_uni_register(info_tim_uni);

	HAL_TIM_Base_Init(&htim);
}

void TIM2_ReInit(float time_ms, uint16_t ncounts, void (*time_out_handler)(void))
{
	tim_uni_t info_tim_uni;
	
	uint32_t total_period;
	uint16_t periods_per_count = 0;  // 一次循环
	uint16_t counts_per_inter = 0;

	// 总周期数
	total_period = (uint32_t) (time_ms * get_tim2_clock() * 1e-3f);
	counts_per_inter = ncounts;
	periods_per_count = total_period / counts_per_inter;


	htim.Instance           = TIM2;
	htim.Init.Prescaler     = periods_per_count - 1;   // 分频
	htim.Init.CounterMode   = TIM_COUNTERMODE_UP;      // 向上计数
	htim.Init.Period        = counts_per_inter  - 1;   // 自动装填值
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;  // 时钟分频因子

	
	info_tim_uni.T_ms           = time_ms;
	info_tim_uni.tim_select     = tim_select_tim2_g;
	info_tim_uni.timeouthandler = time_out_handler;
	tim_uni_register(info_tim_uni);

	HAL_TIM_Base_Init(&htim);
}



// 停止定时器
void TIM2_Stop(void)
{
	// 停止定时器计数并禁用中断
	HAL_TIM_Base_Stop_IT(&htim);
	// 计数清零
	__HAL_TIM_SET_COUNTER(&htim, 0);
	// 可选：清除任何挂起的中断标志
	__HAL_TIM_CLEAR_IT(&htim, TIM_IT_UPDATE);
}

// 启动定时器
void TIM2_Start(void)
{
	// 启动定时器并启用中断
	HAL_TIM_Base_Start_IT(&htim);
}

// 暂停定时器（停止计数但保持配置）
void TIM2_Pause(void)
{
	// 停止定时器计数但保持中断设置
	HAL_TIM_Base_Stop(&htim);
}

// 继续定时器（从当前值继续计数）
void TIM2_Resume(void)
{
	// 从当前计数值继续计数
	HAL_TIM_Base_Start(&htim);
}

// 重置定时器3计数器
void TIM2_Reset(void)
{
	// 将计数器重置为0
	__HAL_TIM_SET_COUNTER(&htim, 0);
}

// 获取当前计数值
uint32_t TIM2_GetCounter(void)
{
	return __HAL_TIM_GET_COUNTER(&htim);
}

//定时器3中断服务函数
void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim);
}



////// TIM3 的 PWM 部分初始化
////// PWM：输出初始化
////// arr：自动重装值
////// psc：时钟预分频数
////void TIM3_PWM_Init(uint16_t arr, uint16_t psc, void (*_time_out_handler_)(void))
////{
////	time_out_handler_tim3           = _time_out_handler_;
////	TIM3_Handler.Instance           = TIM3;                      //定时器3
////	TIM3_Handler.Init.Prescaler     = psc;                       //定时器分频
////	TIM3_Handler.Init.CounterMode   = TIM_COUNTERMODE_UP;        //向上计数模式
////	TIM3_Handler.Init.Period        = arr;                       //自动重装载值
////	TIM3_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;    // 时钟分频因子
////	HAL_TIM_PWM_Init(&TIM3_Handler);                             //初始化PWM
////
////	// 模式选择PWM1
////	TIM3_CH4Handler.OCMode = TIM_OCMODE_PWM1;
////	// 设置比较值,此值用来确定占空比，
////	// 当前比较值为自动重装载值的一半，即占空比为50%
////	TIM3_CH4Handler.Pulse = arr/2;
////	// 输出比较极性为低
////	TIM3_CH4Handler.OCPolarity = TIM_OCPOLARITY_LOW;
////	// 配置TIM3通道4
////	HAL_TIM_PWM_ConfigChannel(&TIM3_Handler, &TIM3_CH4Handler, TIM_CHANNEL_4);
////	// 开启PWM通道4
////	HAL_TIM_PWM_Start(&TIM3_Handler, TIM_CHANNEL_4);
////}

////// 设置 TIM 通道 4 的占空比
////// compare:比较值
////void TIM_SetTIM3Compare4(uint32_t compare)
////{
////	TIM3->CCR4 = compare; 
////}


