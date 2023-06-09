#include "tim.h"


/****************************************
定时器说明

TIM3--APB1-->定时器频率：84MHZ

TIM3是16位定时器(最大值65535)

*****************************************/
void Tim3_Init(void)
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	
	//1、能定时器时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
//	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1);  //84分频 84MHZ/84 = 1MHZ
//	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数 ，在1MHZ, 用时1ms
//	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//向上计数
//	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //分频因子
//	//2、初始化定时器，配置ARR,PSC。
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (8400-1);  	//8400分频 84MHZ/8400 = 10000HZ
	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);	//计10000个数 ，在10000HZ, 用时1s
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //分频因子
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);	
	
	//3、启定时器中断，配置NVIC。
	 NVIC_InitStructure.NVIC_IRQChannel 				  = TIM3_IRQn;				//中断通道，只能在stm32f4xx.h中查找
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//响应优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //通道使能
	 NVIC_Init(&NVIC_InitStructure);
	
	
	
	//4、设置 TIM3_DIER  允许更新中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//5、使能定时器。
	TIM_Cmd(TIM3, ENABLE);


}


/****************************************
定时器说明

TIM4--APB1-->定时器频率：84MHZ

TIM4是16位定时器(最大值65535)

*****************************************/
void Tim4_Init(void)
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	
	//1、能定时器时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	

	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (8400-1);  	//8400分频 84MHZ/8400 = 10000HZ
	TIM_TimeBaseInitStruct.TIM_Period		= (20000-1);	//计20000个数 ，在10000HZ, 用时2s
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //分频因子
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);	
	
	//3、启定时器中断，配置NVIC。
	 NVIC_InitStructure.NVIC_IRQChannel 				  = TIM4_IRQn;				//中断通道，只能在stm32f4xx.h中查找
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//响应优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //通道使能
	 NVIC_Init(&NVIC_InitStructure);
	
	
	
	//4、设置 TIM3_DIER  允许更新中断
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//5、使能定时器。
	TIM_Cmd(TIM4, ENABLE);


}


void TIM4_IRQHandler(void)
{

	//判断标志是否置位
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		

		//按键下，处理相就事情
		//1-->0-->1-->0
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);		
									
						
			
		//清除中断标志位
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);	
	}

}


