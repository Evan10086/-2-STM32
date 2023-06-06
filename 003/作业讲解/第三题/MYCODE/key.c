#include "key.h"


/********************************
KEY0������PA0
����δ���£�PA0Ϊ�ߵ�ƽ(1)
���� ���£�PA0Ϊ�͵�ƽ(0)

KEY1������PE2
����δ���£�PE2Ϊ�ߵ�ƽ(1)
���� ���£�PE2Ϊ�͵�ƽ(0)

KEY2������PE3
����δ���£�PE3Ϊ�ߵ�ƽ(1)
���� ���£�PE3Ϊ�͵�ƽ(0)

KEY3����PE4
����δ���£�PE4Ϊ�ߵ�ƽ(1)
���� ���£�PE4Ϊ�͵�ƽ(0)
*********************************/
void Key_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//ʹ��GPIOE��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_0; 	//����0
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_2; 	//����2
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_3; 	//����3
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOE, &GPIO_InitStruct);	

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_4; 	//����4
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}