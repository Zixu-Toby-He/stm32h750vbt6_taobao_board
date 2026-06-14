#include "stm32h7xx_hal.h"

#include "chip_info.h"

#if   defined(STM32F0)
	#define CPU_ID_P     0x1FFFF7AC
	#define FLASH_SIZE_P 0x1FFFF7CC
#elif defined(STM32F1)
	#define CPU_ID_P     0x1FFFF7E8
	#define FLASH_SIZE_P 0x1FFFF7E0
	// #define CHIP_TYPE_P  0xE0042000
#elif defined(STM32F2)
	#define CPU_ID_P     0x1FFF7A10
	#define FLASH_SIZE_P 0x1FFF7A22
#elif defined(STM32F3)
	#define CPU_ID_P     0x1FFFF7AC
	#define FLASH_SIZE_P 0x1FFFF7CC
#elif defined(STM32F4)
	#define CPU_ID_P     0x1FFF7A10
	#define FLASH_SIZE_P 0x1FFF7A22
#elif defined(STM32F7)
	#define CPU_ID_P     0x1FF0F420
	#define FLASH_SIZE_P 0x1FF0F442
#elif defined(STM32L0)
	#define CPU_ID_P     0x1FF80050
	#define FLASH_SIZE_P 0x1FF8007C
#elif defined(STM32L1)
	#define CPU_ID_P     0x1FF80050
	#define FLASH_SIZE_P 0x1FF8004C
	// 或 #define FLASH_SIZE_P 0x1FF800CC
#elif defined(STM32L4)
	#define CPU_ID_P     0x1FFF7590
	#define FLASH_SIZE_P 0x1FFF75E0
#elif defined(STM32H7)
	#define CPU_ID_P     0x1FF0F420
	#define FLASH_SIZE_P 0x1FF0F442
#endif

#define CPU_ID_HP (CPU_ID_P)
#define CPU_ID_MP (CPU_ID_P + 4)
#define CPU_ID_LP (CPU_ID_P + 8)


cpu_id_t    chip_info_get_cpu_id(void)
{
	cpu_id_t cpu_id;
	cpu_id.id[0] = *((volatile uint32_t*)(CPU_ID_HP));
	cpu_id.id[1] = *((volatile uint32_t*)(CPU_ID_MP));
	cpu_id.id[2] = *((volatile uint32_t*)(CPU_ID_LP));

	return cpu_id;
}

uint16_t    chip_info_get_flash_size(void)
{
	uint16_t ret = 0;
	ret = *((volatile uint16_t*)(FLASH_SIZE_P));
	return ret;
}
chip_type_t chip_info_get_chip_type(void)
{
//	施工中，数值暂不可参考
//	chip_type_t ret = 0;
//	ret = *((volatile chip_type_t*)(CHIP_TYPE_P));
//	return ret;
	return 0;
}