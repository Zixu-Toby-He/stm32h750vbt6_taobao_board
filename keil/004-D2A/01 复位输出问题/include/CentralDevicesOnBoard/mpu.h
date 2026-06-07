#ifndef __MPU_H
#define __MPU_H

#include "ebdtypes.h"

#define de_default MPU_INSTRUCTION_ACCESS_ENABLE
void MPU_Set_Protection(u32 rnum, u32 baseaddr, u32 size, u8 ap, u8 de, u8 sen, u8 cen, u8 ben);
void MPU_Memory_Protection(void);

#endif
