#include "iic.h"
#include "eeprom.h"

#define DEVICE_ADDRESS_A0 0x0
#define DEVICE_ADDRESS_A1 0x0
#define DEVICE_ADDRESS_A2 0x0


static void wait_ms(uint32_t tms)
{
	// MATCHING_NUMBER：与实际时间匹配的常数
	#define MATCHING_NUMBER 6000
	for(volatile uint32_t i = tms * (SystemCoreClock / MATCHING_NUMBER); i > 0; i--) {}
	#undef MATCHING_NUMBER
}

void eeprom_init(void)
{
	IIC_Init(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);
}

void eeprom_write_byte(eeprom_addr_t addr, uint8_t data)
{
	IIC_Emit_Start_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);

	#if (BYTE_NUM > 0x800) // AT24C16以后
		// 发送写命令
		IIC_Send_Byte( GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0);
		IIC_Wait_Ack(  GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
		// 发送高地址
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr >> 8);
	#else
		// 发送器件地址0xA0，写数据（对于 AT24C02该值始终为 0xA0）
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0 + ((addr >> 8) << 1));
	#endif

	IIC_Wait_Ack(        GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	IIC_Send_Byte(       GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr & 0xFF);   // 发送低地址
	IIC_Wait_Ack(        GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	IIC_Send_Byte(       GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, data);     // 发送字节
	IIC_Wait_Ack(        GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	IIC_Emit_Stop_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);                     // 产生一个停止条件

	wait_ms(10);
}
uint8_t eeprom_read_byte(eeprom_addr_t addr)
{
	uint8_t byte = 0;
	// 伪写：写入地址
	IIC_Emit_Start_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);
	#if (BYTE_NUM > 0x800) // AT24C16以后
		// 发送写命令
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0);
		IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 256);
		// 发送高地址
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr >> 8);
	#else
		// 发送器件地址0xA0，写数据（对于 AT24C02该值始终为 0xA0）
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0 + ((addr >> 8) << 1));
	#endif
	IIC_Wait_Ack(        GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	IIC_Send_Byte(       GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr & 0xFF);   // 发送低地址
	IIC_Wait_Ack(        GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);

	// 重新开始，读取数据
	IIC_Emit_Start_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);
	IIC_Send_Byte(       GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA1);     // 读模式
	IIC_Wait_Ack(        GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);

	byte = IIC_Get_Byte( GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, false);
	IIC_Emit_Stop_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);

	return byte;
}

void eeprom_write_page(eeprom_page_t page, eeprom_page_data_t data)
{
	uint8_t addr = page * BYTES_PER_PAGE;

	IIC_Emit_Start_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);
	#if (BYTE_NUM > 0x800) // AT24C16以后
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0);
		IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr >> 8);
	#else
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0 + ((addr >> 8) << 1));
	#endif
	IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr & 0xFF);
	IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	for (size_t i = 0; i < BYTES_PER_PAGE; i++)
	{
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, data.data[i]);
		IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	}
	IIC_Emit_Stop_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);
	wait_ms(10);
}
eeprom_page_data_t eeprom_read_page(eeprom_page_t page)
{
	eeprom_page_data_t data;
	uint8_t addr = page * BYTES_PER_PAGE;

	IIC_Emit_Start_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);
	// 伪写
	#if (BYTE_NUM > 0x800) // AT24C16以后
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0);
		IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr >> 8);
	#else
		IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA0 + ((addr >> 8) << 1));
	#endif
	IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, addr & 0xFF);
	IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);

	IIC_Emit_Start_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);
	IIC_Send_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xA1);
	IIC_Wait_Ack(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, 0xFF);
	for (size_t i = 0; i < BYTES_PER_PAGE; i++)
	{
		data.data[i] = IIC_Get_Byte(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL, i < (BYTES_PER_PAGE - 1));
	}
	IIC_Emit_Stop_Signal(GPIO_SDA, PIN_SDA, GPIO_SCL, PIN_SCL);

	return data;
}
