#ifndef _LED_H
#define _LED_H

#include "bitband.h"

#include "stm32h7xx_hal.h"


//LED端口定义

#define LED_ON     GPIO_PIN_RESET    // 0
#define LED_OFF    GPIO_PIN_SET      // 1

#define LED_Turn(OnOff)   ((OnOff)?PAout_Set_1(0): PAout_Set_0(0))
#define LED_Turn_On()     (PAout_Set_0(0))
#define LED_Turn_Off()    (PAout_Set_1(0))
#define LED_Toggle()      (HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0)) //LED1输出电平翻转


void LED_Init(void); //LED初始化函数
#endif
