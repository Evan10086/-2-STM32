#include "led.h"


/*************************************
����˵��
LED0������PF9
PF9����͵�ƽ��0����������PF9����ߵ�ƽ��1��������

**************************************/
void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//ʹ��GPIOF��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9; 	//����9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; //�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	

	
}
