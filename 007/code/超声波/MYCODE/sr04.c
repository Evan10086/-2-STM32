#include "sr04.h"
#include "sys.h"


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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);
	//1���ܶ�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_6; 	//����6
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; //�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_6; 	//����6
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;//���ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; //�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	

	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= 84-1;  				// 84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period	= 50000-1;					TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;	// ���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;			// ��Ƶ����
	//2����ʼ����ʱ��������ARR,PSC
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
			
	//5,��ʹ�ܶ�ʱ��
	   TIM_Cmd(TIM3, DISABLE);	

}

u16 Get_Sr04_Value(void)
{	
	uint32_t t=0;
	PBout(6)=1;
	delay_us(20);
	PBout(6)=0;
	
	//�ȴ������źű�Ϊ�ߵ�ƽ
	while(PEin(6)==0)
	{
		t++;
		delay_us(1);
		
		//�����ʱ���ͷ���һ��������
		if(t>=1000000)
			return 0xFFFFFFFF;
	}
	
	t=0;
	//�����ߵ�ƽ������ʱ��
	while(PEin(6))
	{
	
		//��ʱ8us,����3mm�Ĵ������
		delay_us(8);
		
		t++;
	
	}
	
	//��ǰ�Ĵ������
	return 3*(t/2);

}


