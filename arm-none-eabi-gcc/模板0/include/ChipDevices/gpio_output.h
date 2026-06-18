
#ifndef __GPIO_OUTPUT_H__
#define __GPIO_OUTPUT_H__


#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_rcc.h"

#include "ebdtypes.h"

typedef enum
{
	GPIO_LOW  = false,
	GPIO_HIGH = true,
}
output_state_t;

typedef enum
{
	SELECT_OUTPUT1  = 0x0001,   SELECT_OUTPUT9  = 0x0100,
	SELECT_OUTPUT2  = 0x0002,   SELECT_OUTPUT10 = 0x0200,
	SELECT_OUTPUT3  = 0x0004,   SELECT_OUTPUT11 = 0x0400,
	SELECT_OUTPUT4  = 0x0008,   SELECT_OUTPUT12 = 0x0800,
	SELECT_OUTPUT5  = 0x0010,   SELECT_OUTPUT13 = 0x1000,
	SELECT_OUTPUT6  = 0x0020,   SELECT_OUTPUT14 = 0x2000,
	SELECT_OUTPUT7  = 0x0040,   SELECT_OUTPUT15 = 0x4000,
	SELECT_OUTPUT8  = 0x0080,   SELECT_OUTPUT16 = 0x8000
}
output_select_t;
typedef uint16_t output_init_t;

void OUTPUT_GPIO_Init(output_init_t init_series);
void Output_StateWrite(output_select_t channel, output_state_t state);
void Output_Toggle(output_select_t channel);

#define OUTPUT1_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define OUTPUT1_GPIO_PIN                 GPIO_PIN_15
#define OUTPUT1_GPIO                     GPIOD

#define OUTPUT2_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define OUTPUT2_GPIO_PIN                 GPIO_PIN_14
#define OUTPUT2_GPIO                     GPIOD

#define OUTPUT3_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define OUTPUT3_GPIO_PIN                 GPIO_PIN_13
#define OUTPUT3_GPIO                     GPIOD

#define OUTPUT4_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define OUTPUT4_GPIO_PIN                 GPIO_PIN_12
#define OUTPUT4_GPIO                      GPIOD

#define OUTPUT5_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define OUTPUT5_GPIO_PIN                 GPIO_PIN_14
#define OUTPUT5_GPIO                     GPIOE

#define OUTPUT6_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define OUTPUT6_GPIO_PIN                 GPIO_PIN_13
#define OUTPUT6_GPIO                     GPIOE

#define OUTPUT7_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define OUTPUT7_GPIO_PIN                 GPIO_PIN_11
#define OUTPUT7_GPIO                     GPIOE

#define OUTPUT8_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define OUTPUT8_GPIO_PIN                 GPIO_PIN_9
#define OUTPUT8_GPIO                     GPIOE

#define OUTPUT9_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define OUTPUT9_GPIO_PIN                 GPIO_PIN_0
#define OUTPUT9_GPIO                     GPIOB

#define OUTPUT10_RCC_CLK_ENABLE           __HAL_RCC_GPIOA_CLK_ENABLE
#define OUTPUT10_GPIO_PIN                 GPIO_PIN_6
#define OUTPUT10_GPIO                     GPIOA

#define OUTPUT11_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define OUTPUT11_GPIO_PIN                 GPIO_PIN_10
#define OUTPUT11_GPIO                     GPIOE

#define OUTPUT12_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define OUTPUT12_GPIO_PIN                 GPIO_PIN_12
#define OUTPUT12_GPIO                     GPIOE

#define OUTPUT13_RCC_CLK_ENABLE           __HAL_RCC_GPIOA_CLK_ENABLE
#define OUTPUT13_GPIO_PIN                 GPIO_PIN_3
#define OUTPUT13_GPIO                     GPIOA

#define OUTPUT14_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define OUTPUT14_GPIO_PIN                 GPIO_PIN_0
#define OUTPUT14_GPIO                     GPIOC


#define OUTPUT15_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define OUTPUT15_GPIO_PIN                 GPIO_PIN_2
#define OUTPUT15_GPIO                     GPIOC

#define OUTPUT16_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define OUTPUT16_GPIO_PIN                 GPIO_PIN_3
#define OUTPUT16_GPIO                     GPIOC

#endif  

