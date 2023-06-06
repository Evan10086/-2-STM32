#include "tim.h"

/**************************************
定时器频率

TIM3 -- APB1
TIM3频率：84MHZ
TIM3为16位定时器

**************************************/
void Tim3_Init(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	
	//1、能定时器时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,  ENABLE);
	
//	TIM_TimeBaseInitStruct.TIM_Prescaler	= 83;			//84分频 84MHZ/84 = 1MHZ 计一个数用1us
//	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);		//在1MHZ下，请1000个数，用时1ms
//	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//向上计数
//	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;		 //分频因子
//	//2、初始化定时器，配置ARR,PSC。
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	TIM_TimeBaseInitStruct.TIM_Prescaler	= 8399;			//8400分频 84MHZ/8400 = 10000HZ 每秒可计10000个数
	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);	//10000HZ，请10000个数，用时1s
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;		 //分频因子
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn;  //中断通道，可在stm32f4xx.h文件当中查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;		//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x02;		//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;		//通道使能
	//3、启定时器中断，配置NVIC。
	NVIC_Init(&NVIC_InitStructure);	
	

	//4、设置 TIM3_DIER  允许更新中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	
	//5、使能定时器。
	TIM_Cmd(TIM3, ENABLE);
	
}





