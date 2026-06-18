#include "iic.h"

#define GPIO_MODE             ((uint32_t)0x00000003)
#define H GPIO_PIN_SET      // 高电平
#define L GPIO_PIN_RESET    // 低电平

// IO 方向设置（pin_sda只有一个引脚，不进行检查）
// 设为输入模式（设定项为 0）
#define set_sda_input(gpio, pin)                                           \
{                                                                          \
	(gpio)->MODER &= ~(3 *                           ((pin) * (pin)));     \
/*	(gpio)->MODER |= (GPIO_MODE_INPUT & GPIO_MODE) * ((pin) * (pin)) */    \
}
// 设为输出模式（设定项为 0）
#define set_sda_output(gpio, pin)                                              \
{                                                                              \
	(gpio)->MODER &= ~((                      GPIO_MODE) * ((pin) * (pin)));   \
	(gpio)->MODER |=  ((GPIO_MODE_OUTPUT_PP & GPIO_MODE) * ((pin) * (pin)));   \
}

// IO 操作
#define set_SCL(gpio, pin, HL) HAL_GPIO_WritePin(gpio, pin, HL)   // SCL 控制
#define set_SDA(gpio, pin, HL) HAL_GPIO_WritePin(gpio, pin, HL)   // 输出 SDA
#define get_SDA(gpio, pin    ) HAL_GPIO_ReadPin( gpio, pin)       // 输入 SDA


#define set_scl_relax(    gpio_scl, pin_scl)           set_SCL(gpio_scl, pin_scl, H)
#define set_scl_ready(    gpio_scl, pin_scl)           set_SCL(gpio_scl, pin_scl, L)
#define set_scl_sending(  gpio_scl, pin_scl)           set_SCL(gpio_scl, pin_scl, H)
#define set_scl_receiving(gpio_scl, pin_scl)           set_SCL(gpio_scl, pin_scl, H)

#define set_sda_relax(   gpio_sda, pin_sda)            set_SDA(gpio_sda, pin_sda, H)
#define toggle_sda(      gpio_sda, pin_sda)            HAL_GPIO_TogglePin(gpio_sda, pin_sda)

#define shift_sda(gpio_sda, pin_sda, gpio_scl, pin_scl, HL)    set_scl_ready(gpio_scl, pin_scl);set_SDA(gpio_sda, pin_sda, HL)

static void wait_us(uint32_t tus)
{
	// MATCHING_NUMBER：与实际时间匹配的常数
	#define MATCHING_NUMBER 6000000
	for(volatile uint32_t i = tus * (SystemCoreClock / MATCHING_NUMBER); i > 0; i--) {}
	#undef MATCHING_NUMBER
}

void IIC_Init(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
)
{
	GPIO_InitTypeDef GPIO_Initure;

	switch ((uint32_t)gpio_sda)
	{
		case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
		case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
		case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
		case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
		case GPIOE_BASE: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
		case GPIOF_BASE: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
		case GPIOG_BASE: __HAL_RCC_GPIOG_CLK_ENABLE(); break;
		case GPIOH_BASE: __HAL_RCC_GPIOH_CLK_ENABLE(); break;
		case GPIOI_BASE: __HAL_RCC_GPIOI_CLK_ENABLE(); break;
		case GPIOJ_BASE: __HAL_RCC_GPIOJ_CLK_ENABLE(); break;
		case GPIOK_BASE: __HAL_RCC_GPIOK_CLK_ENABLE(); break;
		default: return; // gpio 不存在
	}
	switch ((uint32_t)gpio_scl)
	{
		case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
		case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
		case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
		case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
		case GPIOE_BASE: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
		case GPIOF_BASE: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
		case GPIOG_BASE: __HAL_RCC_GPIOG_CLK_ENABLE(); break;
		case GPIOH_BASE: __HAL_RCC_GPIOH_CLK_ENABLE(); break;
		case GPIOI_BASE: __HAL_RCC_GPIOI_CLK_ENABLE(); break;
		case GPIOJ_BASE: __HAL_RCC_GPIOJ_CLK_ENABLE(); break;
		case GPIOK_BASE: __HAL_RCC_GPIOK_CLK_ENABLE(); break;
		default: return; // gpio 不存在
	}

	// 初始化设置
	GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;          //推挽输出
	GPIO_Initure.Pull  = GPIO_PULLUP;                  //上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;    //快速

	// sda管脚初始化
	GPIO_Initure.Pin   = pin_sda;
	HAL_GPIO_Init(gpio_sda, &GPIO_Initure);
	// scl管脚初始化
	GPIO_Initure.Pin   = pin_scl;
	HAL_GPIO_Init(gpio_scl, &GPIO_Initure);

	set_sda_relax(gpio_sda, pin_sda);
	set_scl_relax(gpio_scl, pin_scl);
}



// 发送 IIC 开始信号
void IIC_Emit_Start_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
)
{
	set_sda_output(gpio_sda, pin_sda);     // sda 线输出
	set_SDA(gpio_sda, pin_sda, H);
	set_SCL(gpio_scl, pin_scl, H);
	wait_us(4);
	set_SDA(gpio_sda, pin_sda, L);
	wait_us(4);
	set_SCL(gpio_scl, pin_scl, L);    // 钳住I2C总线，准备发送或接收数据
}
// 发送 IIC 停止信号
void IIC_Emit_Stop_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
)
{
	set_sda_output(gpio_sda, pin_sda);

	// 设定为发送就绪状态
	set_SCL(gpio_scl, pin_scl, L);
	set_SDA(gpio_sda, pin_sda, L);    // STOP: when CLK is high DATA change form low to high
	wait_us(4);
	set_SCL(gpio_scl, pin_scl, H);
	// wait_us(4);
	set_SDA(gpio_sda, pin_sda, H);
	wait_us(4);


}
// IIC 发送一个字节
void IIC_Send_Byte(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl,
	uint8_t byte_to_be_send
)
{
	int8_t t = 7;
	set_sda_output(gpio_sda, pin_sda);
	set_SCL(gpio_scl, pin_scl, L);
	for(t = 7; t >= 0; t--)
	{
		set_SDA(gpio_sda, pin_sda, (GPIO_PinState)((byte_to_be_send >> t) & 0x1));
		wait_us(2);
		set_SCL(gpio_scl, pin_scl, H);
		wait_us(2);
		set_SCL(gpio_scl, pin_scl, L);
		wait_us(2);
	}
}
// IIC 读取一个字节
uint8_t IIC_Get_Byte(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl,
	bool ack
)
{
	int8_t t = 7;
	int8_t val = 0;

	set_sda_input(gpio_sda, pin_sda); // SDA设置为输入
	for(t = 0; t < 8; t++)
	{
		set_SCL(gpio_scl, pin_scl, L);
		wait_us(2);
		set_SCL(gpio_scl, pin_scl, H);
		wait_us(1);
		val <<= 1;
		val += get_SDA(gpio_sda, pin_sda);
		wait_us(1);
	}
	if (ack)
	{
		IIC_Emit_Ack_Signal(gpio_sda, pin_sda, gpio_scl, pin_scl);
	}
	else
	{
		IIC_Emit_NAck_Signal(gpio_sda, pin_sda, gpio_scl, pin_scl);
	}
	return val;
}
// IIC 等待 ACK 信号
uint8_t IIC_Wait_Ack(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl,
	uint8_t timeout
)
{
	uint8_t t_count = 0;

	set_sda_input(gpio_sda, pin_sda);    // SDA设置为输入
	set_SDA(gpio_sda, pin_sda, H);
	wait_us(1);

	set_SCL(gpio_scl, pin_scl, H);
	wait_us(1);

	for(t_count = 0; t_count < timeout; t_count++)
	{
		// 获取到 ACK
		if (!get_SDA(gpio_sda, pin_sda))
		{
			set_SCL(gpio_scl, pin_scl, L);
			return 0;
		}
	}
	// 获取到 NACK
	IIC_Emit_Stop_Signal(gpio_sda, pin_sda, gpio_scl, pin_scl);
	return 1;
}
// IIC 发送 ACK 信号
void IIC_Emit_Ack_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
)
{
	set_SCL(gpio_scl, pin_scl, L);
	set_sda_output(gpio_sda, pin_sda);
	set_SDA(gpio_sda, pin_sda, L);
	wait_us(2);
	set_SCL(gpio_scl, pin_scl, H);
	wait_us(2);
	set_SCL(gpio_scl, pin_scl, L);
}
// IIC 不发送 ACK 信号
void IIC_Emit_NAck_Signal(
	GPIO_TypeDef* gpio_sda,
	uint16_t pin_sda,
	GPIO_TypeDef* gpio_scl,
	uint16_t pin_scl
)
{
	set_SCL(gpio_scl, pin_scl, L);
	set_sda_output(gpio_sda, pin_sda);
	set_SDA(gpio_sda, pin_sda, H);
	wait_us(2);
	set_SCL(gpio_scl, pin_scl, H);
	wait_us(2);
	set_SCL(gpio_scl, pin_scl, L);
}







////// 发送 IIC 开始信号
////void IIC_Emit_Start_Signal(
////	GPIO_TypeDef* gpio_sda,
////	uint16_t pin_sda,
////	GPIO_TypeDef* gpio_scl,
////	uint16_t pin_scl
////)
////{
////	set_sda_output(gpio_sda, pin_sda);
////
////	// 当前理论上是 relax 状态，写入 relax
////	set_sda_relax(gpio_sda, pin_sda);
////	set_scl_relax(gpio_scl, pin_scl);
////
////	// 写入翻转
////	set_SDA(gpio_sda, pin_sda, H);
////	wait_us(4);
////	toggle_sda(gpio_sda, pin_sda);
////	wait_us(4);
////
////	// 信号完成，设定为发送就绪状态
////	set_scl_ready(gpio_scl, pin_scl);    // 钳住I2C总线，准备发送或接收数据
////
////}
////// 发送 IIC 停止信号
////void IIC_Emit_Stop_Signal(
////	GPIO_TypeDef* gpio_sda,
////	uint16_t pin_sda,
////	GPIO_TypeDef* gpio_scl,
////	uint16_t pin_scl
////)
////{
////	set_sda_output(gpio_sda, pin_sda);
////
////	// 设定为发送就绪状态
////	set_scl_ready(gpio_scl, pin_scl);
////	shift_sda(gpio_sda, pin_sda, gpio_scl, pin_scl, L);
////	wait_us(4);
////
////	// 写入翻转
////	set_scl_sending(gpio_scl, pin_scl);
////	wait_us(4);
////	toggle_sda(gpio_sda, pin_sda);
////	wait_us(4);
////
////	// 结束后应当是relax状态
////	set_sda_relax(gpio_sda, pin_sda);
////	set_scl_relax(gpio_scl, pin_scl);
////}
////// IIC 发送一个字节
////void IIC_Send_Byte(
////	GPIO_TypeDef* gpio_sda,
////	uint16_t pin_sda,
////	GPIO_TypeDef* gpio_scl,
////	uint16_t pin_scl,
////	uint8_t byte_to_be_send
////)
////{
////	int8_t t = 7;
////	set_scl_ready(gpio_scl, pin_scl);
////	set_sda_output(gpio_sda, pin_sda);
////	for(t = 7; t >= 7; t--)
////	{
////		shift_sda(gpio_sda, pin_sda, gpio_scl, pin_scl, (byte_to_be_send >> t) & 0x1);
////		wait_us(2);
////		set_scl_sending(gpio_scl, pin_scl);
////		wait_us(2);
////		set_scl_ready(gpio_scl, pin_scl);
////		wait_us(2);
////	}
////}
////// IIC 读取一个字节
////uint8_t IIC_Get_Byte(
////	GPIO_TypeDef* gpio_sda,
////	uint16_t pin_sda,
////	GPIO_TypeDef* gpio_scl,
////	uint16_t pin_scl,
////	bool ack
////)
////{
////	int8_t t = 7;
////	int8_t val = 0;
////	set_scl_ready(gpio_scl, pin_scl);
////	set_sda_input(gpio_sda, pin_sda);
////	for(t = 7; t >= 7; t--)
////	{
////		set_scl_ready(gpio_scl, pin_scl);
////		wait_us(2);
////		set_scl_receiving(gpio_scl, pin_scl);
////		wait_us(1);
////		val <<= 1;
////		val += get_SDA(gpio_sda, pin_sda);
////	}
////	if (ack)
////	{
////		IIC_Emit_Ack_Signal(gpio_sda, pin_sda, gpio_scl, pin_scl);
////	}
////	else
////	{
////		IIC_Emit_NAck_Signal(gpio_sda, pin_sda, gpio_scl, pin_scl);
////	}
////	return val;
////}
////// IIC 等待 ACK 信号
////uint8_t IIC_Wait_Ack(
////	GPIO_TypeDef* gpio_sda,
////	uint16_t pin_sda,
////	GPIO_TypeDef* gpio_scl,
////	uint16_t pin_scl,
////	uint8_t timeout
////)
////{
////	uint8_t t_count = 0;
////
////	set_sda_input(gpio_sda, pin_sda);
////	set_sda_relax(gpio_sda, pin_sda);
////	wait_us(1);
////	set_scl_receiving(gpio_scl, pin_scl);
////	wait_us(1);
////	for(t_count = 0; t_count < timeout; t_count++)
////	{
////		// 获取到 ACK
////		if (!get_SDA(gpio_sda, pin_sda))
////		{
////			set_scl_ready(gpio_scl, pin_scl);
////			return 0;
////		}
////	}
////	// 获取到 NACK
////	IIC_Emit_Stop_Signal(gpio_sda, pin_sda, gpio_scl, pin_scl);
////	return 1;
////}
////// IIC 发送 ACK 信号
////void IIC_Emit_Ack_Signal(
////	GPIO_TypeDef* gpio_sda,
////	uint16_t pin_sda,
////	GPIO_TypeDef* gpio_scl,
////	uint16_t pin_scl
////)
////{
////	set_scl_ready(gpio_scl, pin_scl);
////	set_sda_output(gpio_sda, pin_sda);
////	shift_sda(gpio_sda, pin_sda, gpio_scl, pin_scl, L);
////	wait_us(2);
////	set_scl_sending(gpio_scl, pin_scl);
////	wait_us(2);
////	set_scl_ready(gpio_scl, pin_scl);
////}
////// IIC 不发送 ACK 信号
////void IIC_Emit_NAck_Signal(
////	GPIO_TypeDef* gpio_sda,
////	uint16_t pin_sda,
////	GPIO_TypeDef* gpio_scl,
////	uint16_t pin_scl
////)
////{
////	set_scl_ready(gpio_scl, pin_scl);
////	set_sda_output(gpio_sda, pin_sda);
////	shift_sda(gpio_sda, pin_sda, gpio_scl, pin_scl, H);
////	wait_us(2);
////	set_scl_sending(gpio_scl, pin_scl);
////	wait_us(2);
////	set_scl_ready(gpio_scl, pin_scl);
////}


