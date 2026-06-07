#ifndef __GPIO_INPUT_H__
#define __GPIO_INPUT_H__
#include "stm32h7xx_hal.h"


typedef enum
{
	GPIO_INACTIVE   = 0,
	GPIO_ACTIVE     = 1,
}
GPIOState_TypeDef;

#define INPUT1_RCC_CLK_ENABLE           __HAL_RCC_GPIOE_CLK_ENABLE
#define INPUT1_GPIO_PIN                 GPIO_PIN_15
#define INPUT1_GPIO                     GPIOE
#define INPUT1_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT2_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT2_GPIO_PIN                 GPIO_PIN_10
#define INPUT2_GPIO                     GPIOD
#define INPUT2_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT3_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT3_GPIO_PIN                 GPIO_PIN_11
#define INPUT3_GPIO                     GPIOD
#define INPUT3_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT4_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT4_GPIO_PIN                 GPIO_PIN_8
#define INPUT4_GPIO                     GPIOC
#define INPUT4_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT5_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT5_GPIO_PIN                 GPIO_PIN_9
#define INPUT5_GPIO                     GPIOC
#define INPUT5_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT6_RCC_CLK_ENABLE           __HAL_RCC_GPIOA_CLK_ENABLE
#define INPUT6_GPIO_PIN                 GPIO_PIN_8
#define INPUT6_GPIO                     GPIOA
#define INPUT6_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT7_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT7_GPIO_PIN                 GPIO_PIN_3
#define INPUT7_GPIO                     GPIOD
#define INPUT7_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT8_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT8_GPIO_PIN                 GPIO_PIN_4
#define INPUT8_GPIO                     GPIOD
#define INPUT8_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */
																													

#define INPUT9_RCC_CLK_ENABLE           __HAL_RCC_GPIOD_CLK_ENABLE
#define INPUT9_GPIO_PIN                 GPIO_PIN_7
#define INPUT9_GPIO                     GPIOD
#define INPUT9_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT10_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT10_GPIO_PIN                 GPIO_PIN_4
#define INPUT10_GPIO                     GPIOB
#define INPUT10_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT11_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT11_GPIO_PIN                 GPIO_PIN_8
#define INPUT11_GPIO                     GPIOB
#define INPUT11_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT12_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT12_GPIO_PIN                 GPIO_PIN_2
#define INPUT12_GPIO                     GPIOB
#define INPUT12_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */																													

#define INPUT13_RCC_CLK_ENABLE           __HAL_RCC_GPIOA_CLK_ENABLE
#define INPUT13_GPIO_PIN                 GPIO_PIN_15
#define INPUT13_GPIO                     GPIOA
#define INPUT13_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT14_RCC_CLK_ENABLE           __HAL_RCC_GPIOB_CLK_ENABLE
#define INPUT14_GPIO_PIN                 GPIO_PIN_3
#define INPUT14_GPIO                     GPIOB
#define INPUT14_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT15_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT15_GPIO_PIN                 GPIO_PIN_6
#define INPUT15_GPIO                     GPIOC
#define INPUT15_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */

#define INPUT16_RCC_CLK_ENABLE           __HAL_RCC_GPIOC_CLK_ENABLE
#define INPUT16_GPIO_PIN                 GPIO_PIN_7
#define INPUT16_GPIO                     GPIOC
#define INPUT16_ACTIVE_LEVEL             GPIO_PIN_RESET /* 根据原理图设计，INPUT引脚上拉电阻，\
                                                          光耦导通时STM32引脚为低电平，即为：0 */
	

void input(void);
void INPUT_GPIO_Init(void);
GPIOState_TypeDef INPUT1_StateRead(void);
GPIOState_TypeDef INPUT2_StateRead(void);
GPIOState_TypeDef INPUT3_StateRead(void);
GPIOState_TypeDef INPUT4_StateRead(void);
GPIOState_TypeDef INPUT5_StateRead(void);
GPIOState_TypeDef INPUT6_StateRead(void);
GPIOState_TypeDef INPUT7_StateRead(void);
GPIOState_TypeDef INPUT8_StateRead(void);
GPIOState_TypeDef INPUT9_StateRead(void);
GPIOState_TypeDef INPUT10_StateRead(void);
GPIOState_TypeDef INPUT11_StateRead(void);
GPIOState_TypeDef INPUT12_StateRead(void);
GPIOState_TypeDef INPUT13_StateRead(void);
GPIOState_TypeDef INPUT14_StateRead(void);
GPIOState_TypeDef INPUT15_StateRead(void);
GPIOState_TypeDef INPUT16_StateRead(void);

#endif  


