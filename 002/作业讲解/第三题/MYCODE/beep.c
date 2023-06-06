#include "beep.h"

/*
����˵��
������������PF8
PF8����͵�ƽ��0�������������죻PF8����ߵ�ƽ��1�����������죻
*/

void Beep_Init()
{
	//��GPIOF��ʱ��(PF8����GPIOF��ʱ��)
	RCC_AHB1ENR |= (0x01<<5);
	
	//����Ϊͨ�����ģʽ 
	GPIOF_MODER &= ~(0x01<<17);  	//17λ��0
	GPIOF_MODER |= (0x01<<16);  	//16λ��1
	
	//�������
	GPIOF_OTYPER &= ~(0x01<<8);
	
	//�ٶ� 25MHZ
	GPIOF_OSPEEDR &= ~(0x01<<17);  	//17λ��0
	GPIOF_OSPEEDR |= (0x01<<16);  	//16λ��1
	
	
	//����
	GPIOF_PUPDR &= ~(0x01<<17);  	//17λ��0
	GPIOF_PUPDR |= (0x01<<16);  	//16λ��1		

}