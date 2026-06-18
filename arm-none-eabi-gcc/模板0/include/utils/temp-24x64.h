#ifndef __TEMP_24X64_H__ 
#define __TEMP_24X64_H__ 

#include <stdint.h>
#include "ebdtypes.h"

void    AT24CXX_Init(void);

void    AT24CXX_WriteOneByte(u16 addr, u8 data);
uint8_t AT24CXX_ReadOneByte(u16 addr);

#endif
