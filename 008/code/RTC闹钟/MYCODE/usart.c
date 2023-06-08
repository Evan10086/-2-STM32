#include "usart.h"


#include "stdio.h"

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数   printf 是一个宏
int fputc(int ch, FILE *f)
{ 	
	USART_SendData(USART1,ch);  //通过串口发送数据
	//等待数据发送完毕
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);      
	return ch;
}







/*************************************
引脚说明

PA9  ---- USART1_TX(发送端)
PA10 ---- USART1_RX(接收端)
**************************************/


void Usart1_Init(int myBaudRate)
{
	GPIO_InitTypeDef  	GPIO_InitStruct;
	USART_InitTypeDef	USART_InitStruct;
	NVIC_InitTypeDef    NVIC_InitStructure;

	
	
	//2、 串口时钟使能，GPIO 时钟使能。
	//使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	
	//3、设置引脚复用器映射：调用 GPIO_PinAFConfig 函数。
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 	
	
	//4、GPIO 初始化设置：要设置模式为复用功能。
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9|GPIO_Pin_10; 		//引脚9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF; 	//复用模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; 	//推挽输出
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;	//速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);		
	
	
	
	USART_InitStruct.USART_BaudRate	= myBaudRate;  //波特率
	USART_InitStruct.USART_Mode		= USART_Mode_Rx|USART_Mode_Tx;//全双工
	USART_InitStruct.USART_Parity	= USART_Parity_No; //无奇偶校验位
	USART_InitStruct.USART_StopBits	= USART_StopBits_1;//1位停止位
	USART_InitStruct.USART_WordLength= USART_WordLength_8b; //字长 8位
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件控制流
	//5、串口参数初始化：设置波特率，字长，奇偶校验等参数。
	USART_Init(USART1, &USART_InitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = USART1_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	NVIC_Init(&NVIC_InitStructure);	
	
	//6、开启中断并且初始化 NVIC，使能中断（如果需要开启串口中断才需要这个步骤）。
	//7、配置为接收中断（表示有数据过来，CPU要中断进行接收）
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	

	//8、使能串口。
	USART_Cmd(USART1, ENABLE);

}