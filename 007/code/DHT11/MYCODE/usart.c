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
	USART_SendData(USART1,ch);  //ͨ�����ڷ�������
	//�ȴ����ݷ������
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);      
	return ch;
}







/*************************************
����˵��

PA9  ---- USART1_TX(���Ͷ�)
PA10 ---- USART1_RX(���ն�)
**************************************/


void Usart1_Init(int myBaudRate)
{
	GPIO_InitTypeDef  	GPIO_InitStruct;
	USART_InitTypeDef	USART_InitStruct;
	NVIC_InitTypeDef    NVIC_InitStructure;

	
	
	//2�� ����ʱ��ʹ�ܣ�GPIO ʱ��ʹ�ܡ�
	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	
	//3���������Ÿ�����ӳ�䣺���� GPIO_PinAFConfig ������
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 	
	
	//4��GPIO ��ʼ�����ã�Ҫ����ģʽΪ���ù��ܡ�
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9|GPIO_Pin_10; 		//����9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF; 	//����ģʽ
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; 	//�������
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;	//�ٶ�
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);		
	
	
	
	USART_InitStruct.USART_BaudRate	= myBaudRate;  //������
	USART_InitStruct.USART_Mode		= USART_Mode_Rx|USART_Mode_Tx;//ȫ˫��
	USART_InitStruct.USART_Parity	= USART_Parity_No; //����żУ��λ
	USART_InitStruct.USART_StopBits	= USART_StopBits_1;//1λֹͣλ
	USART_InitStruct.USART_WordLength= USART_WordLength_8b; //�ֳ� 8λ
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	//5�����ڲ�����ʼ�������ò����ʣ��ֳ�����żУ��Ȳ�����
	USART_Init(USART1, &USART_InitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = USART1_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	
	//6�������жϲ��ҳ�ʼ�� NVIC��ʹ���жϣ������Ҫ���������жϲ���Ҫ������裩��
	//7������Ϊ�����жϣ���ʾ�����ݹ�����CPUҪ�жϽ��н��գ�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	

	//8��ʹ�ܴ��ڡ�
	USART_Cmd(USART1, ENABLE);

}