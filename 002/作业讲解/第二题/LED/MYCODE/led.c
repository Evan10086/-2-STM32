#include"led.h"
/*************************************
����˵��
LED0������PF9
PF9����͵�ƽ��0����������PF9����ߵ�ƽ��1��������

**************************************/
void Led_Init0(void)
{
	RCC_AHB1ENR |= (0x01<<5);
	//���ģʽ
	GPIOF_MODER &= ~(0x01<<19); //19λ��0
	GPIOF_MODER |= (0x01<<18);  //18λ��1
	
	//�������
	GPIOF_OTYPER &= ~(0x01<<9); //9λ��0
	
	// �ٶȣ�25MHZ��
	GPIOF_OSPEEDR &= ~(0x01<<19); //19λ��0
	GPIOF_OSPEEDR |= (0x01<<18);  //18λ��1
	
	
	//����
	GPIOF_PUPDR &= ~(0x01<<19); //19λ��0
	GPIOF_PUPDR |= (0x01<<18);  //18λ��1
	
	
}

void Led_Init1(void)
{
	RCC_AHB1ENR |= (0x01<<5);
	//���ģʽ
	GPIOF_MODER &= ~(0x01<<21);//21λ��0
	GPIOF_MODER |= (0x01<<20); //20λ��1
	
	GPIOF_OTYPER &= ~(0x01<<10);//10λ��0
	
	GPIOF_OSPEEDR &= ~(0x01<<21); //21λ��0
	GPIOF_OSPEEDR |= (0x01<<20);//20λ��1
	
	GPIOF_PUPDR &= ~(0x01<<21); //21λ��0
	GPIOF_PUPDR |= (0x01<<20);  //20λ��1
}
void Led_Init2(void)
{
	RCC_AHB1ENR |= (0x01<<4);
	//���ģʽ
	GPIOE_MODER &= ~(0x01<<27);//27λ��0
	GPIOE_MODER |= (0x01<<26); //26λ��1
	
	GPIOE_OTYPER &= ~(0x01<<13);//13λ��0
	
	GPIOE_OSPEEDR &= ~(0x01<<27); //27λ��0
	GPIOE_OSPEEDR |= (0x01<<26); //26λ��1
	
	GPIOE_PUPDR &= ~(0x01<<27); //27λ��0
	GPIOE_PUPDR |= (0x01<<26);  //26λ��1
}
void Led_Init3(void)
{
	RCC_AHB1ENR |= (0x01<<4);
	//���ģʽ
	GPIOE_MODER &= ~(0x01<<29);//29λ��0
	GPIOE_MODER |= (0x01<<28); //28λ��1
	
	GPIOE_OTYPER &= ~(0x01<<14);//14λ��0
	
	GPIOE_OSPEEDR &= ~(0x01<<29); //29λ��0
	GPIOE_OSPEEDR |= (0x01<<28);  //28λ��1
	
	GPIOE_PUPDR &= ~(0x01<<29); //29λ��0
	GPIOE_PUPDR |= (0x01<<28); //28λ��1
}  