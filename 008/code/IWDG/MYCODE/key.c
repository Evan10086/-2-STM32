#include "key.h"


/********************************
KEY0������PA0
����δ���£�PA0Ϊ�ߵ�ƽ(1)
���� ���£�PA0Ϊ�͵�ƽ(0)

*********************************/
void Key_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_0; 	//����0
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//���ģʽ
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}