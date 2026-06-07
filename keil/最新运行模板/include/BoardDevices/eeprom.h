#ifndef __EEPROM_H__
#define __EEPROM_H__

#include <stdint.h>

// IIC 管脚
#define GPIO_SDA GPIOB
#define PIN_SDA  GPIO_PIN_7

#define GPIO_SCL GPIOB
#define PIN_SCL  GPIO_PIN_6

#define AT24C02


#if   defined(AT24C01 )
	#define BYTE_NUM        0x80
	#define PAGE_NUM        0x10
	#define BYTES_PER_PAGE  0x08
	typedef uint8_t eeprom_addr_t;
	typedef uint8_t eeprom_page_t;
#elif defined(AT24C02 )
	#define BYTE_NUM        0x100
	#define PAGE_NUM        0x020
	#define BYTES_PER_PAGE  0x008
	typedef uint8_t eeprom_addr_t;
	typedef uint8_t eeprom_page_t;
#elif defined(AT24C04 )
	#define BYTE_NUM        0x200
	#define PAGE_NUM        0x020
	#define BYTES_PER_PAGE  0x010
	typedef uint16_t eeprom_addr_t;
	typedef uint8_t  eeprom_page_t;
#elif defined(AT24C08 )
	#define BYTE_NUM        0x400
	#define PAGE_NUM        0x040
	#define BYTES_PER_PAGE  0x010
	typedef uint16_t eeprom_addr_t;
	typedef uint8_t  eeprom_page_t;
#elif defined(AT24C16 )
	#define BYTE_NUM        0x800
	#define PAGE_NUM        0x080
	#define BYTES_PER_PAGE  0x010
	typedef uint16_t eeprom_addr_t;
	typedef uint8_t  eeprom_page_t;
#elif defined(AT24C32 )
	#define BYTE_NUM        0x1000
	#define PAGE_NUM        0x0080
	#define BYTES_PER_PAGE  0x0020
	typedef uint16_t eeprom_addr_t;
	typedef uint8_t  eeprom_page_t;
#elif defined(AT24C64 )
	#define BYTE_NUM        0x2000
	#define PAGE_NUM        0x0100
	#define BYTES_PER_PAGE  0x0020
	typedef uint16_t eeprom_addr_t;
	typedef uint8_t  eeprom_page_t;
#elif defined(AT24C128)
	#define BYTE_NUM        0x4000
	#define PAGE_NUM        0x0100
	#define BYTES_PER_PAGE  0X0040
	typedef uint16_t eeprom_addr_t;
	typedef uint8_t  eeprom_page_t;
#elif defined(AT24C256)
	#define BYTE_NUM        0x8000
	#define PAGE_NUM        0x0200
	#define BYTES_PER_PAGE  0x0040
	typedef uint16_t eeprom_addr_t;
	typedef uint8_t  eeprom_page_t;
#else
	// 常数未定义编译不通过
#endif

typedef struct 
{
	uint8_t data[BYTES_PER_PAGE];
}
eeprom_page_data_t;


void    eeprom_init(void);

void    eeprom_write_byte(eeprom_addr_t addr, uint8_t data);
uint8_t eeprom_read_byte(eeprom_addr_t addr);

void               eeprom_write_page(eeprom_page_t addr, eeprom_page_data_t data);
eeprom_page_data_t eeprom_read_page( eeprom_page_t addr);


#endif

