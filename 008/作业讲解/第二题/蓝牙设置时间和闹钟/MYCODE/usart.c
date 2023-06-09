#include "usart.h"


#include "stdio.h"

#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����   printf ��һ����
int fputc(int ch, FILE *f)
{ 	
	USART_SendData(USART2,ch);  //ͨ�����ڷ�������
	//�ȴ����ݷ������
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);      
	return ch;
}


/**********************************
����˵��

PA9  ---- USART1_TX(���Ͷ�)
PA10 ---- USART1_RX(���ն�)

**********************************/

void Usart1_Init(int myBaudRate)
{

	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	//2�� ����ʱ��ʹ�ܣ�GPIO ʱ��ʹ�ܡ�
	//��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//3���������Ÿ�����ӳ�䣺���� GPIO_PinAFConfig ������
	//��ʱ��ӳ�䵽PA9  ѡ������
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	
	
	//4��GPIO ��ʼ�����ã�Ҫ����ģʽΪ���ù��ܡ�
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9 | GPIO_Pin_10;		//����9 10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;	//��������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ;	//����
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	
	USART_InitStruct.USART_BaudRate		= myBaudRate;//������	
	USART_InitStruct.USART_Mode			= USART_Mode_Tx|USART_Mode_Rx;//�շ�ģʽ
	USART_InitStruct.USART_WordLength	= USART_WordLength_8b;	//�ֳ� 8λ
	USART_InitStruct.USART_StopBits		= USART_StopBits_1;		//ֹͣλ1λ
	USART_InitStruct.USART_Parity		= USART_Parity_No;		//����żУ��λ
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	//5�����ڲ�����ʼ�������ò����ʣ��ֳ�����żУ��Ȳ�����
	USART_Init(USART1, &USART_InitStruct);
	
	
	
	
	//3������ʱ���жϣ�����NVIC��
	 NVIC_InitStructure.NVIC_IRQChannel 				  = USART1_IRQn;				//�ж�ͨ����ֻ����stm32f4xx.h�в���
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//��Ӧ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //ͨ��ʹ��
	 //6�������жϲ��ҳ�ʼ�� NVIC��ʹ���жϣ������Ҫ���������жϲ���Ҫ������裩��
	 NVIC_Init(&NVIC_InitStructure);	
	
	
	//7������Ϊ�����жϣ���ʾ�����ݹ�����CPUҪ�жϽ��н��գ�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	//8��ʹ�ܴ��ڡ�
	
	USART_Cmd(USART1, ENABLE);
}

void Usart2_Init(int myBaudRate)
{

	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	//2�� ����ʱ��ʹ�ܣ�GPIO ʱ��ʹ�ܡ�
	//��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//3���������Ÿ�����ӳ�䣺���� GPIO_PinAFConfig ������
	//��ʱ��ӳ�䵽PA9  ѡ������
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);	
	
	//4��GPIO ��ʼ�����ã�Ҫ����ģʽΪ���ù��ܡ�
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2 | GPIO_Pin_3;		//����9 10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;		//����ģʽ
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;	//��������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ;	//����
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	
	USART_InitStruct.USART_BaudRate		= myBaudRate;//������	
	USART_InitStruct.USART_Mode			= USART_Mode_Tx|USART_Mode_Rx;//�շ�ģʽ
	USART_InitStruct.USART_WordLength	= USART_WordLength_8b;	//�ֳ� 8λ
	USART_InitStruct.USART_StopBits		= USART_StopBits_1;		//ֹͣλ1λ
	USART_InitStruct.USART_Parity		= USART_Parity_No;		//����żУ��λ
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	//5�����ڲ�����ʼ�������ò����ʣ��ֳ�����żУ��Ȳ�����
	USART_Init(USART2, &USART_InitStruct);
	
	
	
	
	//3������ʱ���жϣ�����NVIC��
	 NVIC_InitStructure.NVIC_IRQChannel 				  = USART2_IRQn;				//�ж�ͨ����ֻ����stm32f4xx.h�в���
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//��Ӧ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //ͨ��ʹ��
	 //6�������жϲ��ҳ�ʼ�� NVIC��ʹ���жϣ������Ҫ���������жϲ���Ҫ������裩��
	 NVIC_Init(&NVIC_InitStructure);	
	
	
	//7������Ϊ�����жϣ���ʾ�����ݹ�����CPUҪ�жϽ��н��գ�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
	//8��ʹ�ܴ��ڡ�
	
	USART_Cmd(USART2, ENABLE);
}