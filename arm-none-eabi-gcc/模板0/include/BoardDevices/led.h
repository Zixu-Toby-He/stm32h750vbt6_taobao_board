#ifndef _LED_H
#define _LED_H

#include "bitband.h"

#include "stm32h7xx_hal.h"


// LED端口定义

#define LED_ON     GPIO_PIN_RESET    // 0
#define LED_OFF    GPIO_PIN_SET      // 1

#define LED_Turn(OnOff)   ((OnOff)?PCout_Set_1(3): PCout_Set_0(3))
#define LED_Turn_On()     (PCout_Set_0(3))
#define LED_Turn_Off()    (PCout_Set_1(3))
#define LED_Toggle()      (HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3)) //LED1输出电平翻转


void LED_Init(void); //LED初始化函数
#endif
