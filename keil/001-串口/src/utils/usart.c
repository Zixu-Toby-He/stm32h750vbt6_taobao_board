#include "stm32h7xx_hal.h"
#include "usart.h"

// 全局变量定义
UART_HandleTypeDef huart1;
void msghandler_default(uint8_t msg);
void (*_msghandler_)(uint8_t) = msghandler_default;
static uint8_t rx_byte;  // 单字节接收缓冲区

// 默认消息处理函数（空函数）
void msghandler_default(uint8_t msg) {
    // 可在此添加默认处理逻辑
}

// USART1中断服务函数
void USART1_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart1);
}

// 接收完成回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if(huart->Instance == USART1) {
        // 调用用户定义的消息处理器
        _msghandler_(rx_byte);
        
        // 重新启用接收中断
        HAL_UART_Receive_IT(huart, &rx_byte, 1);
    }
}

// 发送单字节数据
void uart_send(uint8_t msg) {
    // 使用阻塞模式发送单字节
    HAL_UART_Transmit(&huart1, &msg, 1, HAL_MAX_DELAY);
}

// HAL库MSP初始化回调函数
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
    GPIO_InitTypeDef         GPIO_InitStruct = {0};
    //RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    
    if(uartHandle->Instance == USART1)
    {
        //// 配置USART1时钟源
        //PeriphClkInitStruct.PeriphClockSelection  = RCC_PERIPHCLK_USART1;
        //PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
        //HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
        
        // 使能USART1和GPIOA时钟
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        // 配置PA9为USART1_TX，PA10为USART1_RX
        GPIO_InitStruct.Pin       = GPIO_PIN_9 | GPIO_PIN_10;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_NOPULL;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        // 配置USART1中断
        HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

// USART初始化函数
void uart_init(uint32_t baudrate, void (*__msghandler__)(uint8_t)) {
    // 更新消息处理器
    _msghandler_ = __msghandler__;
    
    // 配置USART1参数
    huart1.Instance                    = USART1;
    huart1.Init.BaudRate               = baudrate;
    huart1.Init.WordLength             = UART_WORDLENGTH_8B;
    huart1.Init.StopBits               = UART_STOPBITS_1;
    huart1.Init.Parity                 = UART_PARITY_NONE;
    huart1.Init.Mode                   = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling           = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    
    // 初始化USART
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        // 初始化错误处理（可根据需要添加错误处理）
        while(1);
    }
    
    // 使能接收中断
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}