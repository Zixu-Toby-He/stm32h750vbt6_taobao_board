#ifndef _MYIIC_H
#define _MYIIC_H

#include <stdint.h>

#include "stm32h750xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"

#include "ebdtypes.h"

// 目前接口未设置页读页写，参考 https://zhuanlan.zhihu.com/p/379683287


// IIC 所有操作函数
// 初始化 IIC 的 IO 口
void IIC_Init(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
);
// 发送 IIC 开始信号
void IIC_Emit_Start_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
);
// 发送 IIC 停止信号
void IIC_Emit_Stop_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
);
// IIC 发送一个字节
void IIC_Send_Byte(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl,
	uint8_t byte_to_be_send
);
// IIC 读取一个字节
uint8_t IIC_Get_Byte(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl,
	bool ack
);
// IIC 等待 ACK 信号
uint8_t IIC_Wait_Ack(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl,
	uint8_t timeout
);
// IIC 发送 ACK 信号
void IIC_Emit_Ack_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
);
// IIC 不发送 ACK 信号
void IIC_Emit_NAck_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
);

#endif

