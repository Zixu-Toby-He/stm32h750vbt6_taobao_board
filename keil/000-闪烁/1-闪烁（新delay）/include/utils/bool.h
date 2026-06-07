#ifndef __BOOL_H__
#define __BOOL_H__

#include <stdint.h>

#ifndef bool
typedef uint8_t bool;
#endif

#ifndef True
#define True (char)1
#endif

#ifndef False
#define False (char)0
#endif

//inline bool f2b(float f) {return (f==0);}

#endif
