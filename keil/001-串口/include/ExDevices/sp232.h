#ifndef __SP232_H__
#define __SP232_H__

#include <stdint.h>

typedef enum
{
	baud_9600   =   9600,
	baud_115200 = 115200,
}
baudrate_t;

void SP232_Init(baudrate_t baudrate);

#endif
