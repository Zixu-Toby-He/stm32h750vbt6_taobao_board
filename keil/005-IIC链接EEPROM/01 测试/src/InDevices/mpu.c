#include "mpu.h"
#include "led.h"
#include "delay.h"
u8 MPU_Set_Protection(u32 baseaddr,u32 size,u32 rnum,u8 ap,u8 sen,u8 cen,u8 ben)
{
	MPU_Region_InitTypeDef MPU_Initure;
	
	HAL_MPU_Disable();								        //配置MPU之前先关闭MPU,配置完成以后在使能MPU

	MPU_Initure.Enable=MPU_REGION_ENABLE;			        //使能该保护区域 
	MPU_Initure.Number=rnum;			                    //设置保护区域
	MPU_Initure.BaseAddress=baseaddr;	                    //设置基址
	MPU_Initure.Size=size;				                    //设置保护区域大小
	MPU_Initure.SubRegionDisable=0X00;                      //禁止子区域
	MPU_Initure.TypeExtField=MPU_TEX_LEVEL0;                //设置类型扩展域为level0
	MPU_Initure.AccessPermission=(u8)ap;		            //设置访问权限,
	MPU_Initure.DisableExec=MPU_INSTRUCTION_ACCESS_ENABLE;	//允许指令访问(允许读取指令)
	MPU_Initure.IsShareable=sen;                            //是否共用?
    MPU_Initure.IsCacheable=cen;                            //是否cache?     
	MPU_Initure.IsBufferable=ben;                           //是否缓冲?
	HAL_MPU_ConfigRegion(&MPU_Initure);                     //配置MPU
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);			        //开启MPU
    return 0;
}

//设置需要保护的存储块
//必须对部分存储区域进行MPU保护,否则可能导致程序运行异常
//比如MCU屏不显示,摄像头采集数据出错等等问题...
void MPU_Memory_Protection(void)
{
    //保护整个D1 SRAM 512KB
    MPU_Set_Protection( 0x24000000,                 //基地址
                        MPU_REGION_SIZE_512KB,      //长度
                        MPU_REGION_NUMBER1,         //NUMER1
                        MPU_REGION_FULL_ACCESS,     //全访问
                        MPU_ACCESS_SHAREABLE,       //允许共享
                        MPU_ACCESS_CACHEABLE,       //允许cache
                        MPU_ACCESS_NOT_BUFFERABLE); //禁止缓冲
    
    //保护SDRAM区域,共32M字节  
    MPU_Set_Protection( 0XC0000000,                 //基地址
                        MPU_REGION_SIZE_32MB,       //长度
                        MPU_REGION_NUMBER2,         //NUMER2
                        MPU_REGION_FULL_ACCESS,     //全访问
                        MPU_ACCESS_NOT_SHAREABLE,   //禁止共享
                        MPU_ACCESS_CACHEABLE,       //允许cache
                        MPU_ACCESS_BUFFERABLE);     //允许缓冲
}


