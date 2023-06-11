#include "iic.h"

/****************************************
����˵��
SCL -- PB8
SDA -- PB9

*****************************************/

void Iic_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//��GPIOB��ʱ�� 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9|GPIO_Pin_8;		//����8
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;				//���ģʽ
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;				//��©���
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;					//����
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;				//�ٶ�
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	//����״̬
	SCL = 1;
	SDA_OUT = 1;
}

//����ģʽ���--SDA
void Iic_Sda_Mode(GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;				//��9������
	GPIO_InitStructure.GPIO_Mode  = mode;					//����/���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�����������ǿ�������������ŵ������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//���ŵ��ٶ����Ϊ100MHz
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;			//û��ʹ���ڲ���������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

//�����ź�
void Iic_start(void)
{
	//���ģʽ
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	SCL = 1;
	SDA_OUT = 1;	

	delay_us(5);
	SDA_OUT = 0;
	delay_us(5);	
	SCL = 0;

}

//ֹͣ�ź�
void Iic_stop(void)
{
	//���ģʽ
	Iic_Sda_Mode(GPIO_Mode_OUT);
	SCL = 0;
	SDA_OUT = 0;
	delay_us(5);
	
	SCL = 1;
	delay_us(5);
	SDA_OUT = 1;

}

//����һλ����
void Iic_Send_Ack(u8 ack)
{
	//���ģʽ
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	
	SCL = 0;
	//׼������
	if(ack == 1)
	{
		SDA_OUT = 1;//�������1
	}
	if(ack == 0)
	{
		SDA_OUT = 0;//�������0
	}

	delay_us(5);
	SCL = 1;
	delay_us(5);
	SCL = 0;
	
}

//����һ���ֽ�����
void Iic_Send_Byte(u8 tx_data) //�ȴ���λ 0x87(1000 0111)
{

	u8 i;
	
	//���ģʽ
	Iic_Sda_Mode(GPIO_Mode_OUT);
	

	SCL = 0;
	for(i=0; i<8; i++)  //��1����׼��tx_data��7λ���� ��1����׼��tx_data��6λ����
	{
		//׼������
		if(tx_data & (0x1<<(7-i)))
		{
			SDA_OUT = 1;//�������1
		}
		else
		{
			SDA_OUT = 0;//�������0
		}
		
		
		delay_us(5);
		SCL = 1;
		delay_us(5);
		SCL = 0;	

	}
	
}

//STM32����һλ���� 
u8 Iic_Recv_Ack(void)
{
	u8 rx_data = 0;
	

	//����ģʽ
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


//STM32����һ���ֽ����� 
u8 Iic_Recv_Byte(void)
{
	u8 i,rx_data = 0x00; //�����յ���������0x87 (1000 0111)
	

	//����ģʽ
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
	
	//�����ź�
	Iic_start();

	//�����豸��ַ��ִ��д����
	Iic_Send_Byte(0xA0); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}
	
	//����д������ʼ��ַ
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
		//��������
		Iic_Send_Byte(*write_buff); 	
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure\r\n");
			return;
		}
		//��ַ++��ָ��������һ�����ݿռ�
		write_buff++;
		
	}
	*/
	
	
	
	for(i=0; i<len; i++)
	{
		//��������
		Iic_Send_Byte(*(write_buff+i)); 	
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure\r\n");
			return;
		}	
	}
	
	//ֹͣ�ź�
	Iic_stop();	
	
	printf("write finish\r\n");
}


//֧�ֿ�ҳд������д���ݹ涨��ÿҳ��ͷд
void AT24c02_Write_Data(u8 addr, u8 *write_buff, u8 len)
{
	u8 page, other;
	u8 i=0, ack = 0;
	
	
	//����ҳ   12
	page = len/8;
	//����ҳ�ֽ�
	other = len%8;
	
	for(i=0; i<page; i++)
	{
		//дһҳ
		AT24c02_Write_Byte(addr, write_buff, 8);
		//AT24C02���ָ����һҳ
		addr+=8;
		//������ʼ��ַ��8
		write_buff+=8;
		
		delay_ms(5);
	
	}
	
	//д����ҳ�ֽڵ�AT24C02
	AT24c02_Write_Byte(addr, write_buff, other);	
	

}





void AT24c02_Read_Byte(u8 addr, u8 *read_buff, u8 len)
{

	u8 i=0, ack = 0;
	
	//�����ź�
	Iic_start();

	//�����豸��ַ��ִ��д����
	Iic_Send_Byte(0xA0); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}
	
	//���Ͷ����ݵ���ʼ��ַ
	Iic_Send_Byte(addr); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}

	
	//�����ź�
	Iic_start();

	//�����豸��ַ��ִ�ж�����
	Iic_Send_Byte(0xA1); 	
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure\r\n");
		return;
	}	
	
	
	
	for(i=0; i<len; i++)
	{
		//�����ֽڴ�������鵱��
		read_buff[i] = Iic_Recv_Byte();
		if(i < (len-1)) 
			Iic_Send_Ack(0);
	}
	
	
	Iic_Send_Ack(1);
	
	//ֹͣ�ź�
	Iic_stop();		
	
	

}







