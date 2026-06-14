#ifndef __CHIP_INFO_H__
#define __CHIP_INFO_H__

#include <stdint.h>

#define STM32H7

typedef struct
{
	uint32_t id[3];
}
cpu_id_t;

typedef uint32_t chip_type_t;

cpu_id_t    chip_info_get_cpu_id(void);
uint16_t    chip_info_get_flash_size(void);
chip_type_t chip_info_get_chip_type(void);


#endif
