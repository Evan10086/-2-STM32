#include "tim.h"


/********************************
定时器说明

TIM3挂在APB1

TIM3 16位定时器（1~65535）

TIM3 频率：84MHZ

*********************************/


void Tim3_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1、能定时器时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
//	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84分频 84MHZ/84 = 1MHZ
//	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数，在1MHZ下，用时1ms
//	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
//	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
//	
//	//2、初始化定时器，配置ARR,PSC。
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	

	TIM_TimeBaseInitStruct.TIM_Prescaler	= (8400-1); //84分频 84MHZ/8400 = 10000HZ
	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);//计10000个数，在10000HZ下，用时1s
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);


	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	//3、启定时器中断，配置NVIC。
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4、设置 TIM3_DIER  允许更新中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	
	//5、使能定时器。
	TIM_Cmd(TIM3, ENABLE);

}


void  TIM3_IRQHandler(void)
{
	//判断中断标志位是否置1
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
		
		//清除中断标志位
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	
	}

}



