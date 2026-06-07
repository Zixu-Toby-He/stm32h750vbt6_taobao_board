#ifndef __MSG_H__
#define __MSG_H__

#include <stdint.h>
#include "ebdtypes.h"

typedef void     (*setfunc)(uint32_t);
typedef uint32_t (*getfunc)(void);
void     setfunc_empty(uint32_t);
uint32_t getfunc_empty(void);

#endif
