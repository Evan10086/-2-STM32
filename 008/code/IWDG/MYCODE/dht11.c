#include "dht11.h"


/**********************************
����˵����

DHT11 --- PG9
***********************************/

void Dht11_Init(void)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;				//��9������
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			//���ģʽ
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;			//�����������ǿ�������������ŵ������������
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;			//���ŵ��ٶ����Ϊ25MHz
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;			//û��ʹ���ڲ���������
	GPIO_Init(GPIOG, &GPIO_InitStructure);	
	
	//��ʪ��ģ�黹û�й�������ô���Ĵ��������Ǹߵ�ƽ
	PGout(9) = 1;
}

//����ģʽ���
void Dht11_Pin_Mode(GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;				//��9������
	GPIO_InitStructure.GPIO_Mode  = mode;					//����/���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�����������ǿ�������������ŵ������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;		//���ŵ��ٶ����Ϊ25MHz
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;		//û��ʹ���ڲ���������
	GPIO_Init(GPIOG, &GPIO_InitStructure);	
}

//����DHT11��������0
int  Dht11_Start(void)
{
	u16 t = 0;
	//������Ϊ���ģʽ
	Dht11_Pin_Mode(GPIO_Mode_OUT);
	
	//�����ź�
	PGout(9) = 1;
	delay_ms(2);
	PGout(9) = 0;
	delay_ms(20);
	PGout(9) = 1;
	delay_us(30);
	
	//������Ϊ����ģʽ
	Dht11_Pin_Mode(GPIO_Mode_IN);
	
	//�ȴ��͵�ƽ����
	while(PGin(9) == 1)
	{
		t++;
		delay_us(5);
		
		if(t == 200) //�ȴ�1ms
			return -1;	
	}		
	
	t = 0;
	//�ȴ��ߵ�ƽ���� ���˵͵�ƽ
	while(PGin(9) == 0)
	{
		t++;
		delay_us(5);
		
		if(t == 200) //�ȴ�1ms
			return -2;	
	}		
	
	t = 0;
	//�ȴ��͵�ƽ���� ���˸ߵ�ƽ
	while(PGin(9) == 1)
	{
		t++;
		delay_us(5);
		
		if(t == 200) //�ȴ�1ms
			return -3;	
	}		
		
	return 0;
	
	
}

uint8_t Dht11_Read_Byte(void)
{
	int i, t = 0;
	u8 data = 0x00; //1 0 0 0 0 0 0 0  
					//1 0 1 1 0 0 1 1 
	for(i=0; i<8; i++)
	{
		t = 0;
		//�ȴ��ߵ�ƽ���� ���˵͵�ƽ
		while(PGin(9) == 0)
		{
			t++;
			delay_us(2);
			
			if(t == 200) //�ȴ�400us
				return 0;	
		}		
			

		//��ʱ40us
		delay_us(40);
		
		//�ж������Ƿ�Ϊ�ߵ�ƽ
		if(PGin(9) == 1)
		{
			data |= (0x01<<(7-i));
			
			
			//���ܻ���30us�ߵ�ƽ
			
			t = 0;
			//�ȴ��͵�ƽ���� ���˸ߵ�ƽ
			while(PGin(9) == 1)
			{
				t++;
				delay_us(2);
				
				if(t == 200) //�ȴ�400us
					return 0;	
			}				
					
		}
		
	}
	
	return data;
}

//�ɼ�������ȷ������0
int  Dht11_Data(u8 *data)
{
	
	
	int i;
	for(i=0; i<5; i++)
	{
		data[i] = Dht11_Read_Byte();
	}
	
	if(data[4] == data[0]+data[1]+data[2]+data[3])
	{
		return 0;
	}
	else
	{
		return -1;
	}
		

}


