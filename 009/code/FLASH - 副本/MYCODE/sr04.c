#include "sr04.h"


/********************************

����˵��
PA2��Ϊ��ͨ���
PA3��Ϊ��ͨ����

*********************************/
void Sr04_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	
	
	
	
	//ʹ��GPIOF��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//1���ܶ�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_2; 	//����9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; //�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_3; 	//����0
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	

	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= 84-1;  				// 84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period	= 50000-1;					TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;	// ���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;			// ��Ƶ����
	//2����ʼ����ʱ��������ARR,PSC
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
			
	//5,��ʹ�ܶ�ʱ��
	   TIM_Cmd(TIM3, DISABLE);	

}

#if 0
u16 Get_Sr04_Value(void)
{	
	u16 temp, dis;
	//�����ź�
	//PA2����͵�ƽ
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	delay_us(8);
	//PA2����ߵ�ƽ���ߵ�ƽ����ʱ������10us
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	delay_us(20);
	//PA2����͵�ƽ
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	
	

	//���ö�ʱ����CNTΪ0  
	TIM3->CNT = 0;

	//PA3�ȴ��ߵ�ƽ�������ο������ɿ����� 
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0);

	//ʹ�ܶ�ʱ����ʼ����
	TIM_Cmd(TIM3, ENABLE);	
	
	//PA3�ȴ��͵�ƽ������while( ����ƽ  );
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 1);

	//��ȡ��ʱ��CNTֵ���Ӷ��õ��ߵ�ƽ����ʱ��    
	temp = TIM3->CNT;

	//�رն�ʱ��
	TIM_Cmd(TIM3, DISABLE);	
	
	//ͨ����ʽ�������������������
	dis = temp/58;
	
	return dis;

}

#else

u16 Get_Sr04_Value(void)
{	
	u16 temp, dis, t = 0;
	//�����ź�
	//PA2����͵�ƽ
	PAout(2) = 0;
	delay_us(8);
	//PA2����ߵ�ƽ���ߵ�ƽ����ʱ������10us
	PAout(2) = 1;
	delay_us(20);
	//PA2����͵�ƽ
	PAout(2) = 0;
	
	

	//���ö�ʱ����CNTΪ0  
	TIM3->CNT = 0;

	t = 0;
	//PA3�ȴ��ߵ�ƽ�������ο������ɿ����� 
	while(PAin(3) == 0)
	{
		t++;
		delay_us(5);
		
		if(t == 200) //�ȴ��ߵ�ƽʱ��Ϊ1ms
			return 0;
	}

	//ʹ�ܶ�ʱ����ʼ����
	TIM_Cmd(TIM3, ENABLE);	
	
	t = 0;
	//PA3�ȴ��͵�ƽ������while( ����ƽ  );
	while(PAin(3) == 1)
	{
		t++;
		delay_us(5);
		
		if(t == 5800) //�ȴ�29000us 
			return 0;	
	}

	//��ȡ��ʱ��CNTֵ���Ӷ��õ��ߵ�ƽ����ʱ��    
	temp = TIM3->CNT;

	//�رն�ʱ��
	TIM_Cmd(TIM3, DISABLE);	
	
	//ͨ����ʽ�������������������
	dis = temp/58;
	
	return dis;

}


#endif
