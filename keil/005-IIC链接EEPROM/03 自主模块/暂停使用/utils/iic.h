#ifndef _MYIIC_H
#define _MYIIC_H

#include "stm32h750xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

#include "ebdtypes.h"

// 目前接口未设置页读页写，参考 https://zhuanlan.zhihu.com/p/379683287


// IO 方向设置
#define SDA_IN()  {GPIOB->MODER &= ~(3 << (7 * 2)); GPIOB->MODER |= 0 << (7 * 2);} // PH5 输入模式
#define SDA_OUT() {GPIOB->MODER &= ~(3 << (5 * 2)); GPIOB->MODER |= 1 << (7 * 2);} // PH5 输出模式

// IO 操作
#define IIC_SCL(n)  ((n)? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)) // SCL
#define IIC_SDA(n)  ((n)? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)) // SDA
#define READ_SDA    HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)  //输入SDA

// IIC 所有操作函数
void IIC_Init(void);                      // 初始化 IIC 的 IO 口
void IIC_Start(void);                     // 发送 IIC 开始信号
void IIC_Stop(void);                      // 发送 IIC 停止信号
void IIC_Send_Byte(u8 txd);               // IIC 发送一个字节
u8   IIC_Read_Byte(unsigned char ack);    // IIC 读取一个字节
u8   IIC_Wait_Ack(void);                  // IIC 等待 ACK 信号
void IIC_Ack(void);                       // IIC 发送 ACK 信号
void IIC_NAck(void);                      // IIC 不发送 ACK 信号

// void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
// u8   IIC_Read_One_Byte(u8 daddr,u8 addr);

#endif

