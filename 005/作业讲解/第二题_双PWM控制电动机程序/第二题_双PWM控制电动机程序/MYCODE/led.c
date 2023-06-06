#include "led.h"

/********************************************
����˵��

LED0������PF9
LED1������PF10
LED2������PE13
LED3������PE14
PF9����͵�ƽ��0����������PF9����ߵ�ƽ��1��������
PF10����͵�ƽ��0����������PF10����ߵ�ƽ��1��������
PE13����͵�ƽ��0����������PE13����ߵ�ƽ��1��������
PE14����͵�ƽ��0����������PE14����ߵ�ƽ��1��������

*******************************************/
void Led_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;//�������ýṹ��
	
	//1.��GPIOF��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	//1.��GPIOE��ʱ��RCC_AHB1Periph_GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//1.��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_9 | GPIO_Pin_10;//����
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;//�������
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;//25MHZ����
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF,&GPIO_InitStruct);//��ʼ����������
	
	
	//2.��������13��14
	//GPIO_InitTypeDef GPIO_InitStruct;//�������ýṹ��
	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14;//����
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;//�������
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;//25MHZ����
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;//����

	GPIO_Init(GPIOE,&GPIO_InitStruct);//��ʼ����������	
	
	//2.��������PA2
	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_2 | GPIO_Pin_3;//����
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;//�������
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;//25MHZ����

	GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ����������		
	//�Ȱ�ȫ��������
	GPIO_SetBits(GPIOF,GPIO_Pin_9);
	GPIO_SetBits(GPIOF,GPIO_Pin_10);
	GPIO_SetBits(GPIOE,GPIO_Pin_13);
	GPIO_SetBits(GPIOE,GPIO_Pin_14);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2 | GPIO_Pin_3);//�綯������ֹͣ
	

	
}
