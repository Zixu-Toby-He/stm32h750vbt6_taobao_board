# STM32H750VBT6 淘宝工控板工程文档

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-STM32H7-blue)](https://www.st.com/en/microcontrollers-microprocessors/stm32h7-series.html)
[![Toolchain](https://img.shields.io/badge/Toolchain-ARM_Keil-green)](https://www.keil.com/)
[![Version](https://img.shields.io/badge/Version-2.0.0-brightgreen)](CHANGELOG.md)

## 项目概述

本项目是一个基于 **STM32H750VBT6** 微控制器的嵌入式开发工程，主要面向淘宝常见工控板。工程代码涵盖了系统初始化、外设驱动、板级设备支持以及多种通信接口的实现。同时集成了**代码执行时间测量**功能，方便开发者评估关键函数的性能，可作为快速搭建 STM32H7 系列项目的基础模板。

**核心特性：**
- ✅ **完整的底层驱动**：MPU、SDRAM、DAC、ADC、GPIO、I2C、SPI、定时器、串口等
- ✅ **代码时间测量**：利用 TIMx、SysTick 或 DWT 测量关键函数执行时间（见测试数据）
- ✅ **统一外设管理**：定时器（`tim_uni.c`）和串口（`usart_uni.c`）的统一回调接口
- ✅ **快速工程模板**：`最新运行模板` 已集成所有常用外设，可直接作为项目起点
- ✅ **丰富的测试工程**：包含闪烁、串口、RS232、ADC、DAC、EEPROM、时间测量等独立示例
- ✅ **在线调试支持**：可选用 USMART 组件，通过串口动态调用函数并统计执行时间

---

## 硬件平台

- **主控芯片**：STM32H750VBT6（Cortex-M7，480MHz）
- **板载资源**：
  - SDRAM（32MB，通过 FMC 接口）
  - DAC（通道1/2，12位分辨率）
  - 16路光耦隔离输入（带软件消抖）
  - 16路继电器输出
  - SPI接口（用于 ADS8688 等高速 ADC）
  - I2C接口（用于 AT24Cxx EEPROM）
  - 多路定时器（TIM2/3/4/5）
  - USART1（调试串口）、UART8（RS232）
  - 用户 LED（PA0）

> **注意**：本工程基于淘宝店铺 [科鑫电子技术](https://shop348054749.taobao.com/) 的 STM32H750 工控板开发，引脚定义需与原理图对应。

---

## 目录

- [硬件平台](#硬件平台)
- [主要功能](#主要功能)
- [Keil工程列表](#keil工程列表)
- [工程目录结构](#工程目录结构)
- [快速开始](#快速开始)
- [API参考](#api参考)
- [代码时间测量](#代码时间测量)
- [配置与使用说明](#配置与使用说明)
- [常见问题 (FAQ)](#常见问题-faq)
- [版本历史](#版本历史)
- [贡献指南](#贡献指南)
- [许可与致谢](#许可与致谢)

---

## 主要功能

| 模块              | 描述                                                                 | 文件（示例）                  |
| ----------------- | -------------------------------------------------------------------- | ----------------------------- |
| **MPU**           | 配置内存保护单元，保护 AXI SRAM 和 SDRAM 的访问属性（可缓存/缓冲等） | `mpu.c`                       |
| **SDRAM**         | 驱动外部 SDRAM，提供字节读写函数，自动完成初始化序列                 | `sdram.c`                     |
| **DAC**           | 初始化 DAC 通道，支持 0~3.3V 模拟电压输出                           | `dac.c`                       |
| **GPIO 输入**     | 支持最多 16 路光耦隔离输入，带软件消抖                              | `gpio_input.c/h`              |
| **GPIO 输出**     | 支持最多 16 路继电器输出，提供高低电平控制和电平翻转                | `gpio_output.c/h`             |
| **I2C**           | 软件模拟 I2C，用于 EEPROM 等设备                                    | `iic.c/h`                     |
| **SPI**           | 硬件 SPI4（映射为 SPI5），用于 ADS8688 等高速数据采集               | `spi.c/h`                     |
| **定时器**        | TIM2/3/4/5 通用定时器，提供毫秒级中断回调，支持统一管理接口         | `timX.c`, `tim_uni.c`         |
| **串口**          | USART1、UART8 非阻塞收发，支持用户自定义消息处理函数                | `usart1.c`, `uart8.c`, `usart_uni.c` |
| **ADS8688**       | 8 通道 16 位 ADC，支持单通道和自动扫描模式，可直接读取电压（mV）    | `ads8688.c/h`                 |
| **AT24Cxx**       | I2C EEPROM 读写（支持页写/连续读写）                                | `24cxx.c/h`                   |
| **系统时钟**      | 配置 PLL，使 CPU 以 480MHz 运行                                     | `sys.c`                       |
| **SysTick 延时**  | 微秒、毫秒、秒、分钟级延时（基于 SysTick 查询）                     | `delay.c`, `systick.c`        |
| **代码时间测量**  | 利用 TIMx、SysTick 或 DWT 测量代码块执行时间                        | 见“代码时间测量”章节及测试数据 |

---

## Keil 工程列表

| 文件夹名称                                      | 简要说明                                                                                       |
| ----------------------------------------------- | ---------------------------------------------------------------------------------------------- |
| `000-闪烁`                                      | LED 闪烁测试，包含多个版本（原始延时、新 delay 模块、TIM 计时器优化）                           |
| `001-串口`                                      | 基础串口通信测试工程，演示 USART1 的收发功能，并包含 GPIO 输入输出控制示例。                    |
| `002-RS232`                                     | RS232（UART8）通信测试，演示与 PC 串口调试助手交互                                              |
| `003-A2D`                                       | ADS8688 ADC 采集测试，读取 8 通道电压并打印                                                     |
| `004-D2A/00 测试`                               | D2A（数字转模拟）功能测试工程，主要测试 DAC 输出与 ADC（ADS8688）闭环控制，验证信号转换准确性。 |
| `004-D2A/01 复位输出问题`                       | 针对 DAC 输出在上电复位瞬间产生异常电平的问题进行排查和验证的工程。                             |
| `005-IIC链接EEPROM`                             | I2C EEPROM（AT24C02）读写测试，支持串口命令交互                                                 |
| `006-代码时间测量`                              | **核心工程**：完整外设驱动 + 函数执行时间测量（含测试数据）                                     |
| `最新运行模板`                                  | 整合了所有常用外设（SDRAM、MPU、DAC、ADC、定时器、串口等）的完整运行模板，可作为新项目的起点。 |
| `尚未使用的接口库/USMART`                       | 正点原子 USMART 调试组件库（非独立工程），用于通过串口动态调用函数，支持函数执行时间统计。     |

> **注**：`尚未使用的接口库/USMART` 是一个通用组件库，不是独立的 Keil 工程，但已包含完整的源码，可移植到其他工程中使用。

---

## 各工程详细说明

### 1. `000-闪烁`
- **主要功能**：LED 闪烁测试，演示 GPIO 输出和延时。
- **包含版本**：原始循环延时、`delay` 模块延时、TIM 计时器优化延时。
- **适用场景**：验证 GPIO 和基本延时功能。

### 2. `001-串口`
- **主要功能**：验证 STM32H7 的基础串口通信。
- **包含模块**：USART1 中断收发、LED 控制、简单的命令行回显。
- **适用场景**：调试串口硬件、测试波特率稳定性。

### 3. `002-RS232`
- **主要功能**：测试 UART8（RS232）与 PC 串口调试助手的通信。
- **适用场景**：需要 RS232 接口的应用。

### 4. `003-A2D`
- **主要功能**：ADS8688 ADC 采集测试，读取 8 通道电压并打印。
- **关键代码**：`ADS8688_ReadOneChannel()` 和 `Get_MAN_CH_Data_MilliVolt()`。
- **适用场景**：验证 ADC 硬件和 SPI 通信。

### 5. `004-D2A/00 测试`
- **主要功能**：测试 DAC 输出与 ADC 采集的闭环精度。
- **工作流程**：DAC 输出可调电压 → ADS8688 采集该电压 → 串口打印对比结果。
- **关键代码**：`Get_MAN_CH_Data_MilliVolt()` 读取 ADC，`DAC_Set_MilliVolt_CH1()` 设定输出电压。

### 6. `004-D2A/01 复位输出问题`
- **背景**：解决 DAC 在 MCU 复位瞬间输出非零电平的问题。
- **验证方法**：监控 DAC 输出引脚，对比不同复位方式下的电平变化，并尝试通过 GPIO 配置或外部上拉/下拉改善。
- **工程特点**：精简了其他外设，仅保留 DAC 和必要的 GPIO 控制。

### 7. `005-IIC链接EEPROM`
- **主要功能**：I2C EEPROM（AT24C02）读写测试，支持串口命令交互。
- **适用场景**：验证 I2C 硬件和 EEPROM 驱动。

### 8. `006-代码时间测量`
- **定位**：完整外设驱动 + 函数执行时间测量工程，包含详细的测试数据（见 `数据.txt`）。
- **集成外设**：与 `最新运行模板` 类似，额外加入了时间测量框架。
- **推荐使用**：需要进行性能分析和代码优化的开发。

### 9. `最新运行模板`
- **定位**：**最全面的集成模板**，适合作为新项目的基板。
- **已集成外设**：
  - MPU（SDRAM + AXI SRAM 保护）
  - SDRAM（32MB）
  - DAC（双通道）
  - ADS8688（8 通道 ADC）
  - 16 路光耦输入 + 16 路继电器输出
  - 定时器 TIM2/3/4/5（统一回调管理）
  - 串口 USART1 + UART8
  - SysTick 精确延时（us/ms/s/min）
  - I2C 模拟（AT24Cxx EEPROM）
  - SPI 硬件（用于 ADS8688）
- **推荐使用**：直接复制该工程，在此基础上添加应用代码。

### 10. `尚未使用的接口库/USMART`
- **说明**：这不是一个完整的工程，而是一个可移植的调试组件。
- **功能**：通过串口命令行调用用户函数，支持参数解析、返回值显示、函数执行时间统计。
- **使用方法**：将 `USMART` 文件夹下的源文件加入工程，并参照 `usmart_config.c` 注册需要调试的函数即可。

---

## 如何选择合适的工程？

- **新手入门**：从 `001-串口` 开始，了解最基本的串口打印和 GPIO 控制。
- **需要验证特定外设**：使用对应的单项测试工程，如 `003-A2D`（ADC）、`005-IIC链接EEPROM`（EEPROM）。
- **需要进行性能测量**：使用 `006-代码时间测量` 工程。
- **需要稳定外设驱动**：直接使用 `最新运行模板`，它已经包含了所有已验证的驱动代码。
- **调试特定问题（如 DAC 复位输出）**：使用 `004-D2A/01 复位输出问题`。
- **需要进行函数级在线调试**：参考 `尚未使用的接口库/USMART` 集成到您的工程中。

---

## 工程目录结构

```
src/
├── __CHIP__/                # 芯片级启动与系统配置
│   ├── startup_stm32h750xx.s
│   └── system_stm32h7xx.c
├── __HALLIB__/              # STM32H7 HAL 库驱动
│   ├── stm32h7xx_hal_*.c    # 各种外设 HAL 驱动
│   └── stm32h7xx_hal.c      # HAL 核心
├── ChipDevices/             # 芯片内设驱动（片上外设，独立于硬件）
│   ├── gpio_input.c / gpio_output.c
│   ├── iic.c / spi.c
│   ├── dac.c
│   ├── tim2.c / tim3.c / tim4.c / tim5.c / timer.c
│   ├── tim_uni.c            # 定时器统一管理
│   ├── uart8.c / usart1.c / usart_uni.c
│   ├── systick.c
│   └── ...
├── CentralDevicesOnBoard/   # 板级核心外设（MPU, SDRAM）
│   ├── mpu.c                # MPU 配置
│   └── sdram.c              # SDRAM 初始化
├── BoardDevices/            # 板载设备驱动（依赖具体电路）
│   ├── led.c
│   ├── 24cxx.c              # EEPROM
│   ├── ads8688.c            # ADC 芯片
│   ├── sp232.c              # RS232 串口
│   └── ...
├── utils/                   # 工具函数
│   ├── delay.c              # 基于 SysTick 的延时
│   ├── sys.c                # 系统时钟、Cache 配置
│   ├── ebdtypes.h           # 通用类型定义（u8/u16/u32/bool）
│   └── bitband.h            # Cortex-M7 位带操作模拟（硬件不支持原生位带）
├── main/                    # 主程序入口
│   ├── main.c
│   └── msg.c / msg.h        # 消息缓冲区
└── AlterLib/                # 中断服务（模板）
    └── stm32h7xx_it.c
```

---

## 快速开始

### 1. 环境准备

- **IDE**：Keil MDK 5.31 或更高版本（支持 ARM Compiler 5/6）
- **固件库**：STM32CubeH7 固件包（已包含 HAL 驱动）
- **调试器**：ST-Link / J-Link

### 2. 导入工程

打开所需工程目录（如 `001-串口` 或 `最新运行模板`）下的 `.uvprojx` 工程文件。

### 3. 配置宏定义

根据实际硬件连接，可在以下文件中调整引脚映射和时序参数：

- 输入/输出引脚映射：`gpio_input.h`、`gpio_output.h`（根据原理图修改宏定义）
- SDRAM 时序：`sdram.c` 中的 `SDRAM_Timing` 结构体
- ADC 范围：`ads8688.h` 中的 `VREF_B_125` 等宏（±5.12V 输入范围）
- I2C 延时：`iic.c` 中的 `delay_us` 参数
- 串口引脚：`usart_uni.c` 中的 `HAL_UART_MspInit`

### 4. 编译与下载

1. 选择正确的芯片型号（STM32H750VBTx）。
2. 编译工程（无错误警告）。
3. 连接调试器，下载至目标板。

### 5. 使用示例

#### 系统初始化流程

```c
// 系统初始化流程（按顺序）
MPU_Memory_Protection();      // 1. 配置 MPU（最先调用）
HAL_Init();                   // 2. HAL 库初始化
Stm32_Clock_Init(192,5,2,2);  // 3. 系统时钟 480MHz
delay_init();                 // 4. 延时函数初始化
SDRAM_Init();                 // 5. SDRAM 初始化
LED_Init();                   // 6. LED 初始化
DAC_Init(DAC1_CH1);           // 7. DAC 初始化
ADS8688_Init();               // 8. ADC 初始化
db9_init(115200, your_handler); // 9. 串口初始化
```

---

## API 参考

### 系统与延时

| 函数                      | 描述                           |
| ------------------------- | ------------------------------ |
| `Stm32_Clock_Init()`      | 配置系统时钟，默认 480MHz      |
| `delay_us()` / `delay_ms()` | 微秒/毫秒级延时（阻塞）       |
| `delay_s()` / `delay_min()` | 秒/分钟级延时（阻塞）         |
| `get_systick_frequency()` | 获取 SysTick 当前工作频率      |

### GPIO 输入/输出

| 函数                              | 描述                               |
| --------------------------------- | ---------------------------------- |
| `INPUT_GPIO_Init(init_series)`    | 初始化指定输入通道（按位掩码）     |
| `INPUT_StateRead(channel)`        | 读取输入状态，带软件消抖           |
| `OUTPUT_GPIO_Init(init_series)`   | 初始化指定输出通道                 |
| `Output_StateWrite(channel, state)` | 设置输出电平（高/低）              |
| `Output_Toggle(channel)`          | 翻转输出电平                       |

### 定时器（统一接口）

| 函数                          | 描述                                   |
| ----------------------------- | -------------------------------------- |
| `TIM3_Init(ms, ncounts, cb)`  | 初始化定时器，周期 = ms / ncounts      |
| `TIM3_Start()` / `Stop()`     | 启动/停止定时器                        |
| `TIM3_Pause()` / `Resume()`   | 暂停/恢复计数（不重置配置）             |
| `TIM3_SetPeriod(new_period)`  | 动态调整周期（会重新初始化定时器）     |

### DAC

| 函数                            | 描述                        |
| ------------------------------- | --------------------------- |
| `DAC_Init(channel)`             | 初始化 DAC（通道1/2/1+2）   |
| `DAC_Set_MilliVolt_CH1(mV)`     | 设置通道1输出电压（0~3300mV）|
| `DAC_Set_MilliVolt_CH2(mV)`     | 设置通道2输出电压（0~3300mV）|

### ADS8688 (ADC)

| 函数                              | 描述                                   |
| --------------------------------- | -------------------------------------- |
| `ADS8688_Init()`                  | 初始化 SPI 和 ADS8688，配置8通道±5.12V |
| `Get_MAN_CH_Data_MilliVolt(ch)`   | 读取指定通道电压（单位：mV，浮点数）   |
| `Get_MAN_CH_Data(ch, *data)`      | 读取原始 16 位 ADC 值                  |
| `ADS8688_Write_Command(cmd)`      | 发送命令字                             |

### 串口 (USART1 / UART8)

| 函数                          | 描述                       |
| ----------------------------- | -------------------------- |
| `usart1_init(baud, handler)`  | 初始化 USART1，注册回调    |
| `usart1_send(byte)`           | 发送单字节                 |
| `usart1_sendstr(str)`         | 发送字符串                 |
| `db9_init(baud, handler)`     | 初始化 UART8（RS232）      |
| `db9_send()` / `db9_sendstr()` | 同 usart1 系列             |

> 接收回调函数原型：`void your_handler(uint8_t data)`

---

## 代码时间测量

本项目提供了精确测量代码执行时间的框架，可用于性能分析和优化。

### 测量原理

- **SysTick 方式**：利用 SysTick 作为计数器，记录代码块前后的计数值差值，结合 CPU 频率换算为周期数或微秒。
- **硬件定时器方式**：使用 TIM2~5 任意一个定时器，配置为微秒级计数，测量精度更高。
- **DWT 方式**：直接读取数据观察点与跟踪 (DWT) 的周期计数器，精度最高，需在调试时启用。

### 实测示例（基于 480MHz 主频）

以下数据来自 `数据.txt` 中的测试结果（不同优化等级可能略有差异）：

| 代码片段                           | 执行周期数 |
| ---------------------------------- | ---------- |
| `uint32_t a = 0; a++;`             | 5          |
| `uint64_t a++;`                    | 15         |
| `float f = (int)a + (int)b;`       | 11         |
| `int = float * int`                | 13         |
| `uint8++`                          | 10         |
| `float++`                          | 15         |
| `double++`                         | 15         |
| `DAC_Set_MilliVolt_CH1(250);`      | 130        |
| `ADS8688_ReadOneChannel(0);`       | 约 800     |

### 使用方法

```c
// 方法1：使用 SysTick
uint32_t start = get_systick_count();
// ... 待测代码 ...
uint32_t cycles = get_systick_count() - start;

// 方法2：使用 DWT（需先使能）
DWT->CYCCNT = 0;
uint32_t start = DWT->CYCCNT;
// ... 待测代码 ...
uint32_t cycles = DWT->CYCCNT - start;
float us = cycles / 480.0f;
```

详细代码示例请参考 `006-代码时间测量` 工程。

---

## 配置与使用说明

### 1. 系统时钟配置
在 `sys.c` 的 `Stm32_Clock_Init()` 中修改 PLL 参数：
```c
void Stm32_Clock_Init(u32 plln, u32 pllm, u32 pllp, u32 pllq)
```
- 推荐配置：plln=192, pllm=5, pllp=2, pllq=2 → 480MHz
- HCLK = 240MHz，PCLK1/PCLK2/PCLK3 = 100MHz

### 2. MPU 保护区域
可根据实际外设地址修改 `mpu.c` 中的保护区域：
- `MPU_REGION_NUMBER1`：D1 SRAM (0x24000000, 512KB)
- `MPU_REGION_NUMBER2`：SDRAM (0xC0000000, 32MB)

### 3. 外设引脚映射
所有引脚映射通过宏定义在对应的头文件中，需要根据实际硬件原理图调整：
- **输入引脚**：`gpio_input.h` 中的 `INPUT1_GPIO_PIN` 等
- **输出引脚**：`gpio_output.h` 中的 `OUTPUT1_GPIO_PIN` 等
- **I2C 引脚**：`iic.h` 中的 `GPIO_PIN_6`/`GPIO_PIN_7`（PB6/PB7）
- **SPI 引脚**：`spi.c` 中的 `HAL_SPI_MspInit`（PE2/PE5/PE6）
- **串口引脚**：`usart_uni.c` 中的 `HAL_UART_MspInit`（USART1: PA9/PA10；UART8: PE0/PE1）

### 4. 调试方式
- 使用串口 USART1（PA9/PA10）或 UART8（PE0/PE1）输出调试信息
- 支持中断方式接收，回调函数 `msghandler` 可自定义（参考 `msg.c`）

---

## 常见问题 (FAQ)

### 1. 程序无法运行，进入 HardFault？
- 确保 **MPU 配置最先执行**，尤其是在访问 SDRAM 或外部存储器之前。
- 检查缓存一致性：如果使用 DMA 访问 D-Cache 区域，需调用 `SCB_CleanInvalidateDCache()`。

### 2. SDRAM 读写失败或数据错误？
- 检查 SDRAM 时序参数（`sdram.c` 中的 `SDRAM_Timing`）是否与芯片手册匹配。
- 确保 FMC 引脚配置正确，且 SDRAM 供电正常。

### 3. I2C 通信不稳定？
- 调整 `iic.c` 中的 `delay_us()` 参数（增大延时值）。
- 检查上拉电阻是否已添加（通常需要 4.7kΩ）。

### 4. ADC (ADS8688) 读数始终为 0？
- 检查 SPI 引脚连接和片选信号逻辑。
- 确认 `ADS8688_Init()` 中的范围配置与硬件输入电平匹配（如 ±5.12V 对应 `VREF_B_125`）。

### 5. 定时器中断不触发？
- 确保调用了 `HAL_TIM_Base_Start_IT()`。
- 检查中断优先级是否被其他中断屏蔽。
- 确认 `tim_uni.c` 中对应定时器的 `HAL_TIM_PeriodElapsedCallback` 未被重复定义。

### 6. 如何测量代码执行时间？
- 参考上文 [代码时间测量](#代码时间测量) 章节，推荐使用 DWT 周期计数器，精度最高。

### 7. 工程编译报错“找不到头文件”？
- 检查 Keil 工程中的 Include Paths 是否包含所有必要目录（如 `src/`, `include/`, `Drivers/` 等）。
- 确认 STM32CubeH7 固件包已正确安装并添加到工程。

---

## 版本历史

### v2.0.0 (2025-03)
- 重构 README 文档，增加 API 参考、FAQ、贡献指南
- 添加 `最新运行模板` 工程，集成所有常用外设
- 统一定时器和串口回调接口 (`tim_uni`, `usart_uni`)
- 修复 DAC 复位输出异常问题（验证工程 `004-D2A/01`）

### v1.0.0 (2024-10)
- 初始版本，包含基础外设驱动和测试工程

> 详细更新日志请查看 [CHANGELOG.md](CHANGELOG.md)。

---

## 贡献指南

欢迎通过 Issue 或 Pull Request 贡献代码、文档或示例。

1. Fork 本仓库
2. 创建您的特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交您的更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开一个 Pull Request

**代码规范**：请遵循 STM32 HAL 库的命名风格，注释清晰，关键函数需提供使用示例。

---

## 许可与致谢

- **STM32CubeH7**：STMicroelectronics 提供（Apache 2.0 许可）
- **USMART**：正点原子开源串口调试组件（可选用）
- **本仓库代码**：采用 [MIT 许可证](LICENSE)，仅供学习参考，使用前请自行测试验证。

**致谢**：感谢 [科鑫电子技术](https://shop348054749.taobao.com/) 提供的硬件平台及原理图参考。

---

## 联系与支持

本工程为淘宝 STM32H750VBT6 开发板配套代码，可根据实际硬件原理图调整引脚映射和时序参数。如有问题，请参考 ST 官方 HAL 库文档或联系板卡供应商。

**店铺链接**：[科鑫电子技术](https://shop348054749.taobao.com/)  
**商品链接**：[STM32H750工控板串口屏人机界面16位ADC采集隔离485CAN232通讯TTL](https://item.taobao.com/item.htm?id=767885976386)

> 注：程序作者除购买该店铺该产品外与该店铺无直接关联，此处贴出商品信息仅作为程序复现提示，若商家允许相应电路图原理图上传将及时撤回该店铺信息。

欢迎提交 Issue 或 Pull Request 改进文档与代码，同时欢迎 Star ⭐ 和 Fork，让更多人受益！
