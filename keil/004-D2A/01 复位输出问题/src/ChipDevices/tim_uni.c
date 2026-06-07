#include "ebdtypes.h"

#include "tim_uni.h"

bool tim_used[18] = {
	false, false, false, false,
	false, false, false, false,
	false, false, false, false,
	false, false, false, false,
	false, false
};
bool lptim_used[5] = {false, false, false, false, false};

float T_ms_tim[18] = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0
};
bool T_ms_lptim[5] = {0, 0, 0, 0, 0};


void (*timeouthandlers_tim[18])(void) = {
	timeupevent_default, timeupevent_default, timeupevent_default, timeupevent_default,
	timeupevent_default, timeupevent_default, timeupevent_default, timeupevent_default,
	timeupevent_default, timeupevent_default, timeupevent_default, timeupevent_default,
	timeupevent_default, timeupevent_default, timeupevent_default, timeupevent_default,
	timeupevent_default, timeupevent_default
};
void (*timeouthandlers_lptim[5])(void) = { timeupevent_default, timeupevent_default, timeupevent_default, timeupevent_default, timeupevent_default };


void tim_uni_init(tim_uni_t* tim_uni)
{
	// 当前与 tim_uni_register_many 没有区别
	uint8_t i = 0;
	for(i = 0; tim_uni[i].tim_select != tim_select_none; i++)
	{
		if (tim_uni[i].tim_select & 0x100)
		{
			timeouthandlers_lptim[(tim_uni[i].tim_select & 0x0FF) - 1] = tim_uni[i].timeouthandler;
			tim_used[(tim_uni[i].tim_select & 0x0FF) - 1] = true;
		}
		else
		{
			timeouthandlers_tim  [(tim_uni[i].tim_select & 0x0FF) - 1] = tim_uni[i].timeouthandler;
			lptim_used[(tim_uni[i].tim_select & 0x0FF) - 1] = true;
		}
	}
}

void tim_uni_register_many(tim_uni_t* tim_uni)
{
	uint8_t i = 0;
	for(i = 0; tim_uni[i].tim_select != tim_select_none; i++)
	{
		if (tim_uni[i].tim_select & 0x100)
		{
			timeouthandlers_lptim[(tim_uni[i].tim_select & 0x0FF) - 1] = tim_uni[i].timeouthandler;
			tim_used[(tim_uni[i].tim_select & 0x0FF) - 1] = true;
		}
		else
		{
			timeouthandlers_tim  [(tim_uni[i].tim_select & 0x0FF) - 1] = tim_uni[i].timeouthandler;
			tim_used[(tim_uni[i].tim_select & 0x0FF) - 1] = true;
		}
	}
}

void tim_uni_register(tim_uni_t tim_uni)
{
	if (tim_uni.tim_select & 0x100)
	{
		timeouthandlers_lptim[(tim_uni.tim_select & 0x0FF) - 1] = tim_uni.timeouthandler;
		tim_used[(tim_uni.tim_select & 0x0FF) - 1] = true;
	}
	else
	{
		timeouthandlers_tim  [(tim_uni.tim_select & 0x0FF) - 1] = tim_uni.timeouthandler;
		tim_used[(tim_uni.tim_select & 0x0FF) - 1] = true;
	}
}


// 定时器底册驱动，开启时钟，设置中断优先级
// 此函数会被 HAL_TIM_Base_Init() 函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	switch ((uint32_t)(htim->Instance))
	{
		case TIM1_BASE  : 
			// TIM1 有四种中断
			__HAL_RCC_TIM1_CLK_ENABLE();
			break;
		case TIM2_BASE  :
			__HAL_RCC_TIM2_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM2_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM2_IRQn);            // 开启中断
			break;
		case TIM3_BASE  : 
			__HAL_RCC_TIM3_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM3_IRQn);            // 开启中断
			break;
		case TIM4_BASE  :
			__HAL_RCC_TIM4_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM4_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM4_IRQn);            // 开启中断
			break;
		case TIM5_BASE  :
			__HAL_RCC_TIM5_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM5_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM5_IRQn);            // 开启中断
			break;
		case TIM6_BASE  :
			__HAL_RCC_TIM6_CLK_ENABLE();                  // 使能时钟
			HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);            // 开启中断
			break;
		case TIM7_BASE  :
			__HAL_RCC_TIM7_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM7_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM7_IRQn);            // 开启中断
			break;
		case TIM8_BASE  :
			// TIM8 有四种中断
			__HAL_RCC_TIM8_CLK_ENABLE();              // 使能时钟
			break;

		case TIM12_BASE :
			__HAL_RCC_TIM12_CLK_ENABLE();              // 使能时钟
			// TIM12 需要与 TIM8 配合使用，其中断为 TIM8_BRK_TIM12_IRQn
			break;
		case TIM13_BASE :
			__HAL_RCC_TIM13_CLK_ENABLE();              // 使能时钟
			// TIM13 需要与 TIM8 配合使用，其中断为 TIM8_UP_TIM13_IRQn
			break;
		case TIM14_BASE :
			__HAL_RCC_TIM14_CLK_ENABLE();              // 使能时钟
			// TIM14 需要与 TIM8 配合使用，其中断为 TIM8_TRG_COM_TIM14_IRQn
			break;
		case TIM15_BASE :
			__HAL_RCC_TIM15_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM15_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM15_IRQn);            // 开启中断
			break;
		case TIM16_BASE :
			__HAL_RCC_TIM16_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM16_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM16_IRQn);            // 开启中断
			break;
		case TIM17_BASE :
			__HAL_RCC_TIM17_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(TIM17_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(TIM17_IRQn);            // 开启中断
			break;

		case LPTIM1_BASE:
			__HAL_RCC_LPTIM1_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(LPTIM1_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(LPTIM1_IRQn);            // 开启中断
			break;
		case LPTIM2_BASE:
			__HAL_RCC_LPTIM2_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(LPTIM2_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(LPTIM2_IRQn);            // 开启中断
			break;
		case LPTIM3_BASE:
			__HAL_RCC_LPTIM3_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(LPTIM3_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(LPTIM3_IRQn);            // 开启中断
			break;
		case LPTIM4_BASE:
			__HAL_RCC_LPTIM2_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(LPTIM4_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(LPTIM4_IRQn);            // 开启中断
			break;
		case LPTIM5_BASE:
			__HAL_RCC_LPTIM5_CLK_ENABLE();              // 使能时钟
			HAL_NVIC_SetPriority(LPTIM5_IRQn, 1, 3);    // 设置中断优先级，抢占优先级1，子优先级3
			HAL_NVIC_EnableIRQ(LPTIM5_IRQn);            // 开启中断
			break;
		default:
			break;
	}
}



// 定时器底层驱动，时钟使能，引脚配置
// 此函数会被 HAL_TIM_PWM_Init() 调用
// htim：定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;

	switch ((uint32_t)(htim->Instance))
	{
		case TIM1_BASE  :
			break;
		case TIM2_BASE  :
			break;
		case TIM3_BASE  :
			__HAL_RCC_TIM3_CLK_ENABLE();     //使能定时器3
			__HAL_RCC_GPIOB_CLK_ENABLE();    //开启GPIOB时钟

			GPIO_Initure.Pin       = GPIO_PIN_1;                    // PB1
			GPIO_Initure.Mode      = GPIO_MODE_AF_PP;               // 复用推完输出
			GPIO_Initure.Pull      = GPIO_PULLUP;                   // 上拉
			GPIO_Initure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;     // 高速
			GPIO_Initure.Alternate = GPIO_AF2_TIM3;                 // PB1复用为TIM3_CH4
			HAL_GPIO_Init(GPIOB, &GPIO_Initure);
			break;
		case TIM4_BASE  :
			break;
		case TIM5_BASE  :
			break;
		case TIM6_BASE  :
			break;
		case TIM7_BASE  :
			break;
		case TIM8_BASE  :
			break;

		case TIM12_BASE :
			break;
		case TIM13_BASE :
			break;
		case TIM14_BASE :
			break;
		case TIM15_BASE :
			break;
		case TIM16_BASE :
			break;
		case TIM17_BASE :
			break;

		case LPTIM1_BASE:
			;break;
		case LPTIM2_BASE:
			;break;
		case LPTIM3_BASE:
			;break;
		case LPTIM4_BASE:
			;break;
		case LPTIM5_BASE:
			;break;
		default:
			break;
	}
}



// 定时完成回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	void (*timeout_handler)(void);

	switch ((uint32_t)(htim->Instance))
	{
		case TIM1_BASE  : timeout_handler = timeouthandlers_tim[ 0];break;
		case TIM2_BASE  : timeout_handler = timeouthandlers_tim[ 1];break;
		case TIM3_BASE  : timeout_handler = timeouthandlers_tim[ 2];break;
		case TIM4_BASE  : timeout_handler = timeouthandlers_tim[ 3];break;
		case TIM5_BASE  : timeout_handler = timeouthandlers_tim[ 4];break;
		case TIM6_BASE  : timeout_handler = timeouthandlers_tim[ 5];break;
		case TIM7_BASE  : timeout_handler = timeouthandlers_tim[ 6];break;
		case TIM8_BASE  : timeout_handler = timeouthandlers_tim[ 7];break;

		case TIM12_BASE : timeout_handler = timeouthandlers_tim[11];break;
		case TIM13_BASE : timeout_handler = timeouthandlers_tim[12];break;
		case TIM14_BASE : timeout_handler = timeouthandlers_tim[13];break;
		case TIM15_BASE : timeout_handler = timeouthandlers_tim[14];break;
		case TIM16_BASE : timeout_handler = timeouthandlers_tim[15];break;
		case TIM17_BASE : timeout_handler = timeouthandlers_tim[16];break;

		case LPTIM1_BASE: timeout_handler = timeouthandlers_lptim[0];break;
		case LPTIM2_BASE: timeout_handler = timeouthandlers_lptim[1];break;
		case LPTIM3_BASE: timeout_handler = timeouthandlers_lptim[2];break;
		case LPTIM4_BASE: timeout_handler = timeouthandlers_lptim[3];break;
		case LPTIM5_BASE: timeout_handler = timeouthandlers_lptim[4];break;
		default:
			break;
	}
	timeout_handler();
}

void timeupevent_default(void){}

