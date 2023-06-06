#include "tim.h"


/********************************
定时器说明

TIM1挂在APB2

TIM1 16位定时器

TIM1 频率：168MHZ

*********************************/


void Tim1_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1、能定时器时钟。
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (16800-1); //168分频 168MHZ/16800 = 0.01MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);//计10000个数，在0.01MHZ下，用时1s
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
	
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM1_UP_TIM10_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	//3、启定时器中断，配置NVIC。
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4、设置 TIM1_DIER  允许更新中断
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	
	//5、使能定时器。
	TIM_Cmd(TIM1, ENABLE);

}


void  TIM1_UP_TIM10_IRQHandler(void)
{
	//判断中断标志位是否置1
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
		
		//清除中断标志位
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	
	}

}



