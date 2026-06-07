#include <stdlib.h>

#include "system.h"
#include "delay.h"
#include "led.h"
#include "dac.h"

#include "sp232.h"
#include "ads8688.h"

char msg[256] = {
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
	'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'
};
uint8_t idx = 0;
void msghandler(uint8_t _msg_)
{
	msg[  idx] = _msg_;
	msg[++idx] = '\0';
	idx &= 0x7F;
}
float val = 0;

int main(void)
{
	double   ads_millivolt_ch0; // DA
	double   ads_millivolt_ch7; // 电阻

	Cache_Enable();
	HAL_Init();
	MPU_Memory_Protection();
	SystemClock_Config();
	delay_init(SystemCoreClock / 1000000);
	LED_Init();
	db9_init(115200, msghandler);
	ADS8688_Init();

	//DAC_Init(DAC1_CH1CH2);
	DAC_Init(DAC1_CH1);
	DAC_Set_MilliVolt_CH1(1000);
	//DAC_Set_MilliVolt_CH2(1000);

	while(1)
	{
		ads_millivolt_ch7 = Get_MAN_CH_Data_MilliVolt(MAN_CH_7);
		ads_millivolt_ch0 = Get_MAN_CH_Data_MilliVolt(MAN_CH_0);
		DAC_Set_MilliVolt_CH1((uint16_t)ads_millivolt_ch7);
		//DAC_Set_MilliVolt_CH2((uint16_t)ads_millivolt_ch7);
		switch (((ads_millivolt_ch7 > 1000) << 1) | (ads_millivolt_ch0 > 1000))
		{
			case 0:
				sprintf(msg + 128, "volt_0 = %7.3lf mV, volt_7 = %7.3lf mV\r\n", ads_millivolt_ch0,        ads_millivolt_ch7);
				break;
			case 1:
				sprintf(msg + 128, "volt_0 = %5.3lf  V, volt_7 = %7.3lf mV\r\n", ads_millivolt_ch0 / 1000, ads_millivolt_ch7);
				break;
			case 2:
				sprintf(msg + 128, "volt_0 = %5.3lf mV, volt_7 = %7.3lf  V\r\n", ads_millivolt_ch0,        ads_millivolt_ch7 / 1000);
				break;
			case 3:
				sprintf(msg + 128, "volt_0 = %5.3lf  V, volt_7 = %5.3lf  V\r\n", ads_millivolt_ch0 / 1000, ads_millivolt_ch7 / 1000);
				break;
			default:
				// 不可能
				break;
		}
		db9_sendstr(msg + 128);
		delay_ms(500);
    }
}

