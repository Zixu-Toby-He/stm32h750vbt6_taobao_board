#define getCRstat(GPIO_Mode,GPIO_Speed) ((GPIO_Mode & 0x0F) | (((GPIO_Mode >> 4) & 0x01) * GPIO_Speed))
#define GPIO_Speed_Input 0