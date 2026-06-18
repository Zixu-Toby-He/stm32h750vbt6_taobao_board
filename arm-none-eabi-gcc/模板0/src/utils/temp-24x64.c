#include "stm32h7xx_hal.h"
#include "temp-24x64.h"
#include "delay.h"

// 宏定义
#define local_IIC_local_SDA_GPIO_PORT    GPIOB
#define local_IIC_local_SDA_GPIO_PIN     GPIO_PIN_7
#define local_IIC_SCL_GPIO_PORT          GPIOB  
#define local_IIC_SCL_GPIO_PIN           GPIO_PIN_6


// IO操作 - 添加参数括号保护
#define local_IIC_SCL(n)  ((n) ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET))
#define local_IIC_SDA(n)  ((n) ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET))
#define READ_SDA    HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)



static void local_IIC_Init(void);
static void local_IIC_Start(void);
static void local_IIC_Stop(void);
static u8   local_IIC_Wait_Ack(void);
static void local_IIC_Ack(void);
static void local_IIC_NAck(void);
static void local_IIC_Send_Byte(u8 txd);
static u8   local_IIC_Read_Byte(unsigned char ack);
static void local_SDA_IN(void);
static void local_SDA_OUT(void);


#define AT24C64  8191  // 0x0000-0x1FFF 共8192字节
#define EE_TYPE  AT24C64

//初始化IIC接口
void AT24CXX_Init(void)
{
	local_IIC_Init();
}


// 在AT24CXX指定地址读出一个数据 
u8 AT24CXX_ReadOneByte(u16 ReadAddr) 
{	   
    u8 temp=0;	  	    	  
    local_IIC_Start();   
    
    // 24C64需要2字节地址
    local_IIC_Send_Byte(0xA0);          // 发送器件地址 + 写命令
    local_IIC_Wait_Ack(); 
    local_IIC_Send_Byte(ReadAddr >> 8); // 发送地址高字节
    local_IIC_Wait_Ack();
    local_IIC_Send_Byte(ReadAddr & 0xFF); // 发送地址低字节  
    local_IIC_Wait_Ack();	     
    
    local_IIC_Start();  	 	          // 重新发送起始条件
    local_IIC_Send_Byte(0xA1);          // 发送器件地址 + 读命令
    local_IIC_Wait_Ack();	  
    temp = local_IIC_Read_Byte(0);	    // 读取数据，不发送ACK
    local_IIC_Stop();                   // 停止条件
    return temp; 
}

// 在AT24CXX指定地址写入一个数据
void AT24CXX_WriteOneByte(u16 WriteAddr, u8 DataToWrite) 
{	
    local_IIC_Start();   
    local_IIC_Send_Byte(0xA0);          // 发送器件地址 + 写命令
    local_IIC_Wait_Ack(); 
    local_IIC_Send_Byte(WriteAddr >> 8); // 发送地址高字节
    local_IIC_Wait_Ack();
    local_IIC_Send_Byte(WriteAddr & 0xFF); // 发送地址低字节
    local_IIC_Wait_Ack(); 	 	  	    
    local_IIC_Send_Byte(DataToWrite);   // 发送数据
    local_IIC_Wait_Ack();  	    	    
    local_IIC_Stop();                   // 停止条件
    delay_ms(10);                 // 等待写入完成
}







// IIC
// IIC初始化 - 完整版本
static void local_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //使能GPIOB时钟
    
    // 先配置为默认状态（输入模式）
    GPIO_Initure.Pin   = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;        // 初始为输入
    GPIO_Initure.Pull  = GPIO_NOPULL;            // 无内部上拉
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    
    // 延时，确保总线稳定
    HAL_Delay(10);
    
    // 初始化SCL为输出模式
    GPIO_Initure.Pin = GPIO_PIN_6;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;    // 开漏输出
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    
    // 初始化SDA为输出模式
    GPIO_Initure.Pin = GPIO_PIN_7;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;    // 开漏输出
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    
    // 总线恢复序列
    local_IIC_Stop();  // 发送停止条件，确保总线空闲
    HAL_Delay(1);
    
    local_IIC_SDA(1);
    local_IIC_SCL(1);
}

//产生IIC起始信号
static void local_IIC_Start(void)
{
	local_SDA_OUT();     //sda线输出
	local_IIC_SDA(1);	  	  
	local_IIC_SCL(1);
	delay_us(4);
 	local_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	local_IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
static void local_IIC_Stop(void)
{
	local_SDA_OUT();//sda线输出
	local_IIC_SCL(0);
	local_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	local_IIC_SCL(1); 
	local_IIC_SDA(1);//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
static u8 local_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	local_SDA_IN();      //SDA设置为输入  
	local_IIC_SDA(1);delay_us(1);	   
	local_IIC_SCL(1);delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			local_IIC_Stop();
			return 1;
		}
	}
	local_IIC_SCL(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
static void local_IIC_Ack(void)
{
	local_IIC_SCL(0);
	local_SDA_OUT();
	local_IIC_SDA(0);
	delay_us(2);
	local_IIC_SCL(1);
	delay_us(2);
	local_IIC_SCL(0);
}
//不产生ACK应答
static void local_IIC_NAck(void)
{
	local_IIC_SCL(0);
	local_SDA_OUT();
	local_IIC_SDA(1);
	delay_us(2);
	local_IIC_SCL(1);
	delay_us(2);
	local_IIC_SCL(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
static void local_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		local_SDA_OUT(); 	    
    local_IIC_SCL(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        local_IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		local_IIC_SCL(1);
		delay_us(2); 
		local_IIC_SCL(0);	
		delay_us(2);
    }	 
} 	    
// 读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
static u8 local_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    uint8_t bit_value;
    
    local_SDA_IN();  // SDA设置为输入
    
    // 确保SCL初始为低
    local_IIC_SCL(0);
    delay_us(4);
    
    for(i = 0; i < 8; i++)
    {
        local_IIC_SCL(0); 
        delay_us(4);
        
        local_IIC_SCL(1);   // 时钟上升沿读取数据
        delay_us(2);  // 等待数据稳定
        
        bit_value = READ_SDA;
        receive = (receive << 1) | bit_value;  // MSB first
        
        delay_us(2);
        local_IIC_SCL(0);
        delay_us(2);
    }
    
    if (!ack)
        local_IIC_NAck();  // 发送nACK
    else
        local_IIC_Ack();   // 发送ACK   
        
    return receive;
}

// SDA设置为输入模式
static void local_SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;        // 输入模式
    GPIO_InitStruct.Pull = GPIO_NOPULL;            // 无上拉下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// SDA设置为输出模式
static void local_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;    // 开漏输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;            // 无上拉下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

