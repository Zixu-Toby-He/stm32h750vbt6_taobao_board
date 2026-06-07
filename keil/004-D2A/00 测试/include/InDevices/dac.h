#ifndef __DAC_H
#define __DAC_H

#include "sys.h"

extern DAC_HandleTypeDef DAC_Handler;

typedef enum
{
	DAC1_CH1    = 1,
	DAC1_CH2    = 2,
	DAC1_CH1CH2 = 3,
}dac1_chn_t;

void DAC_Init(dac1_chn_t channel);
void DAC_Set_MilliVolt_CH1(u16 mV);
void DAC_Set_MilliVolt_CH2(u16 mV);

#endif
