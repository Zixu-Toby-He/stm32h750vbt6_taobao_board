#ifndef _LED_H
#define _LED_H
#include "sys.h"


//LED端口定义
#define LED0(n)		(n?HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET))
#define LED0_Toggle (HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0)) //LED1输出电平翻转


void LED_Init(void); //LED初始化函数
#endif
