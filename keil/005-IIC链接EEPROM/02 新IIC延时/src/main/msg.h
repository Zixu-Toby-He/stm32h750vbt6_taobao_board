#ifndef MSG_H
#define MSG_H

#include <stdint.h>
#include "ebdtypes.h"

void msghandler(uint8_t _msg_);

bool is_data_in(void);
void clear_msg(void);
uint8_t get_msg(char* buf);

#endif
