#include "iic.h"

/****************************************
引脚说明
SCL -- PB8
SDA -- PB9

*****************************************/

void Iic_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//打开GPIOB组时钟 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9|GPIO_Pin_8;		//引脚8
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;				//输出模式
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;				//开漏输出
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;					//上拉
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;				//速度
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	//空闲状态
	SCL = 1;
	SDA_OUT = 1;
}

//引脚模式变更--SDA
void Iic_Sda_Mode(GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;				//第9号引脚
	GPIO_InitStructure.GPIO_Mode  = mode;					//输入/输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽输出，增强驱动能力，引脚的输出电流更大
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//引脚的速度最大为100MHz
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;			//没有使用内部上拉电阻
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

//启动信号
void Iic_start(void)
{
	//输出模式
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	SCL = 1;
	SDA_OUT = 1;	

	delay_us(5);
	SDA_OUT = 0;
	delay_us(5);	
	SCL = 0;

}

//停止信号
void Iic_stop(void)
{
	//输出模式
	Iic_Sda_Mode(GPIO_Mode_OUT);
	SCL = 0;
	SDA_OUT = 0;
	delay_us(5);
	
	SCL = 1;
	delay_us(5);
	SDA_OUT = 1;

}

//发送一位数据
void Iic_Send_Ack(u8 ack)
{
	//输出模式
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	
	SCL = 0;
	//准备数据
	if(ack == 1)
	{
		SDA_OUT = 1;//引脚输出1
	}
	if(ack == 0)
	{
		SDA_OUT = 0;//引脚输出0
	}

	delay_us(5);
	SCL = 1;
	delay_us(5);
	SCL = 0;
	
}

//发送一个字节数据
void Iic_Send_Byte(u8 tx_data) //先传高位 0x87(1000 0111)
{

	u8 i;
	
	//输出模式
	Iic_Sda_Mode(GPIO_Mode_OUT);
	

	SCL = 0;
	for(i=0; i<8; i++)  //第1脉冲准备tx_data第7位数据 第1脉冲准备tx_data第6位数据
	{
		//准备数据
		if(tx_data & (0x1<<(7-i)))
		{
			SDA_OUT = 1;//引脚输出1
		}
		else
		{
			SDA_OUT = 0;//引脚输出0
		}
		
		
		delay_us(5);
		SCL = 1;
		delay_us(5);
		SCL = 0;	

	}
	
}

//STM32接受一位数据 
u8 Iic_Recv_Ack(void)
{
	u8 rx_data = 0;
	

	//输入模式
	Iic_Sda_Mode(GPIO_Mode_IN);

	SCL = 0;
	
	delay_us(5);
	SCL = 1;
	delay_us(5);
	if(SDA_IN == 1)
	{
		rx_data = 1;
	}
	if(SDA_IN == 0)
	{
		rx_data = 0;
	}		
	SCL = 0;
	

	return rx_data;
}


//STM32接受一个字节数据 
u8 Iic_Recv_Byte(void)
{
	u8 i,rx_data = 0x00; //假设收到的数据是0x87 (1000 0111)
	

	//输入模式
	Iic_Sda_Mode(GPIO_Mode_IN);

	SCL = 0;
	for(i=0; i<8; i++)  
	{

		delay_us(5);
		SCL = 1;
		
		delay_us(5);
		
		if(SDA_IN == 1)
		{
			rx_data |= (0x01<<(7-i));
		}	
		SCL = 0;	

	}	

	return rx_data;
}


void AT24c02_Write_Byte(u8 addr, u8 *write_buff, u8 len)
{
	u8 i=0, ack = 0;
	
	//启动信号
	Iic_start();

	//发送设备地址，执行写操作
	Iic_Send_Byte(0xA0); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}
	
	//发送写数据起始地址
	Iic_Send_Byte(addr); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}
/*
	while(len--)
	{
		//发送数据
		Iic_Send_Byte(*write_buff); 	
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure\r\n");
			return;
		}
		//地址++，指向数据下一个数据空间
		write_buff++;
		
	}
	*/
	
	
	
	for(i=0; i<len; i++)
	{
		//发送数据
		Iic_Send_Byte(*(write_buff+i)); 	
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure\r\n");
			return;
		}	
	}
	
	//停止信号
	Iic_stop();	
	
	printf("write finish\r\n");
}


//支持跨页写，不过写数据规定在每页开头写
void AT24c02_Write_Data(u8 addr, u8 *write_buff, u8 len)
{
	u8 page, other;
	u8 i=0, ack = 0;
	
	
	//计算页   12
	page = len/8;
	//不满页字节
	other = len%8;
	
	for(i=0; i<page; i++)
	{
		//写一页
		AT24c02_Write_Byte(addr, write_buff, 8);
		//AT24C02光标指向下一页
		addr+=8;
		//数组起始地址加8
		write_buff+=8;
		
		delay_ms(5);
	
	}
	
	//写不满页字节到AT24C02
	AT24c02_Write_Byte(addr, write_buff, other);	
	

}





void AT24c02_Read_Byte(u8 addr, u8 *read_buff, u8 len)
{

	u8 i=0, ack = 0;
	
	//启动信号
	Iic_start();

	//发送设备地址，执行写操作
	Iic_Send_Byte(0xA0); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}
	
	//发送读数据的起始地址
	Iic_Send_Byte(addr); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}

	
	//启动信号
	Iic_start();

	//发送设备地址，执行读操作
	Iic_Send_Byte(0xA1); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}	
	
	
	
	for(i=0; i<len; i++)
	{
		//接受字节存放在数组当中
		read_buff[i] = Iic_Recv_Byte();
		if(i < (len-1)) 
			Iic_Send_Ack(0);
	}
	
	
	Iic_Send_Ack(1);
	
	//停止信号
	Iic_stop();		
	
	

}







