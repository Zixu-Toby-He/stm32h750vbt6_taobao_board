#ifndef __SPI_H
#define __SPI_H

#include "stm32h750xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_spi.h"
#include "ebdtypes.h"

extern SPI_HandleTypeDef SPI_Handler;  // SPI句柄

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
void SPI5_Init(void);                       // 初始化SPI口
uint8_t SPI5_ReadWriteByte(uint8_t TxData); // SPI读写
 
#endif
