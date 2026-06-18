#ifndef __GPIO_INPUT_H__
#define __GPIO_INPUT_H__

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_rcc.h"

#include "ebdtypes.h"

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
typedef enum
{
	GPIO_INACTIVE   = false,
	GPIO_ACTIVE     = true,
}
input_state_t;

typedef enum
{
	SELECT_INPUT1  = 0x0001,   SELECT_INPUT9  = 0x0100,
	SELECT_INPUT2  = 0x0002,   SELECT_INPUT10 = 0x0200,
	SELECT_INPUT3  = 0x0004,   SELECT_INPUT11 = 0x0400,
	SELECT_INPUT4  = 0x0008,   SELECT_INPUT12 = 0x0800,
	SELECT_INPUT5  = 0x0010,   SELECT_INPUT13 = 0x1000,
	SELECT_INPUT6  = 0x0020,   SELECT_INPUT14 = 0x2000,
	SELECT_INPUT7  = 0x0040,   SELECT_INPUT15 = 0x4000,
	SELECT_INPUT8  = 0x0080,   SELECT_INPUT16 = 0x8000
}
input_select_t;
typedef uint16_t input_init_t;

void INPUT_GPIO_Init(input_init_t init_series);
input_state_t INPUT_StateRead(input_select_t channel);

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT1_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define INPUT1_GPIO_PIN                 GPIO_PIN_15
#define INPUT1_GPIO                     GPIOE
#define INPUT1_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT2_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT2_GPIO_PIN                 GPIO_PIN_10
#define INPUT2_GPIO                     GPIOD
#define INPUT2_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT3_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT3_GPIO_PIN                 GPIO_PIN_11
#define INPUT3_GPIO                     GPIOD
#define INPUT3_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT4_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT4_GPIO_PIN                 GPIO_PIN_8
#define INPUT4_GPIO                     GPIOC
#define INPUT4_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT5_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT5_GPIO_PIN                 GPIO_PIN_9
#define INPUT5_GPIO                     GPIOC
#define INPUT5_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT6_RCC_CLK_ENABLE           __HAL_RCC_GPIOA_CLK_ENABLE
#define INPUT6_GPIO_PIN                 GPIO_PIN_8
#define INPUT6_GPIO                     GPIOA
#define INPUT6_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT7_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT7_GPIO_PIN                 GPIO_PIN_3
#define INPUT7_GPIO                     GPIOD
#define INPUT7_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT8_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT8_GPIO_PIN                 GPIO_PIN_4
#define INPUT8_GPIO                     GPIOD
#define INPUT8_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT9_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT9_GPIO_PIN                 GPIO_PIN_7
#define INPUT9_GPIO                     GPIOD
#define INPUT9_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT10_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT10_GPIO_PIN                 GPIO_PIN_4
#define INPUT10_GPIO                     GPIOB
#define INPUT10_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT11_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT11_GPIO_PIN                 GPIO_PIN_8
#define INPUT11_GPIO                     GPIOB
#define INPUT11_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT12_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT12_GPIO_PIN                 GPIO_PIN_2
#define INPUT12_GPIO                     GPIOB
#define INPUT12_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT13_RCC_CLK_ENABLE           __HAL_RCC_GPIOA_CLK_ENABLE
#define INPUT13_GPIO_PIN                 GPIO_PIN_15
#define INPUT13_GPIO                     GPIOA
#define INPUT13_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT14_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT14_GPIO_PIN                 GPIO_PIN_3
#define INPUT14_GPIO                     GPIOB
#define INPUT14_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT15_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT15_GPIO_PIN                 GPIO_PIN_6
#define INPUT15_GPIO                     GPIOC
#define INPUT15_ACTIVE_LEVEL             GPIO_PIN_RESET

// 根据原理图设计，INPUT引脚上拉电阻，光耦导通时STM32引脚为低电平，即为：0
#define INPUT16_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT16_GPIO_PIN                 GPIO_PIN_7
#define INPUT16_GPIO                     GPIOC
#define INPUT16_ACTIVE_LEVEL             GPIO_PIN_RESET

#endif

