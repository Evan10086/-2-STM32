#include "tim.h"

int flag1 = 0;
int flag2 = 0;
int time = 0;
unsigned int temp = 1;

u16 count = -1;
int count1 = -1;
int count2 = -1;
int count3 = -1;

/********************************
定时器说明

TIM3挂在APB1

TIM3 16位定时器

TIM3 频率：84MHZ

*********************************/

void Tim3_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1、能定时器时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数，在1MHZ下，用时1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子

//	TIM_TimeBaseInitStruct.TIM_Prescaler	= (8400-1); //84分频 84MHZ/84 = 1MHZ
//	TIM_TimeBaseInitStruct.TIM_Period		= (10000-1);//计1000个数，在1MHZ下，用时1ms
//	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
//	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
	
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



void Tim2_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1、能定时器时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数，在1MHZ下，用时1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
	
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	//3、启定时器中断，配置NVIC。
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4、设置 TIM2_DIER  允许更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	
	//5、使能定时器。TIM2
	TIM_Cmd(TIM2, ENABLE);

}

void Tim1_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1、能定时器时钟。
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (168-1); //168分频 168MHZ/168 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数，在1MHZ下，用时1ms
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
	
	
	//5、使能定时器。TIM1
	TIM_Cmd(TIM1, ENABLE);

}

void Tim4_Init(void)
{

	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	
	//1、能定时器时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数，在1MHZ下，用时1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
	
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM4_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	//3、启定时器中断，配置NVIC。
	NVIC_Init(&NVIC_InitStructure);
	
	
	//4、设置 TIM3_DIER  允许更新中断
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	
	//5、使能定时器。
	TIM_Cmd(TIM4, ENABLE);

}

char bug_count = 0;
char test = 0;

void  TIM3_IRQHandler(void)//延时看效果
{
	//判断中断标志位是否置1
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
//		if(++count%2 == 0) //亮一，灭一
//		{
//			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
//			
//		}
//		else
//		{
//			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
//			
//		}
		
		if(++count%3 == 0) //亮一，灭二
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
			bug_count++;
			test = 0;
		}
		else
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
			bug_count++;
			test = 0;
			
		}
		
//		if(++count%5 == 0) //亮一，灭四
//		{
//			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
//		}
//		else
//		{
//			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
//		
//		}		
//		
//		
//		if(++count%9 == 0) //亮一，灭八
//		{
//			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
//		}
//		else
//		{
//			GPIO_SetBits(GPIOF, GPIO_Pin_9);	
//		
//		}		
//			

		
			
		
		
		//清除中断标志位
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	
	}
}
	
	
	
		

void  TIM2_IRQHandler(void)
{
		
		//判断中断标志位是否置1
		if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
		{
				
				
//	    if(++count1%2 == 0&&flag1 == 1) //亮一，灭一
//		{
//			flag1 = 0;
//		}
		if(++count1%3 == 0&&flag1 == 1) //亮一，灭二
		{
			flag1 = 0;
		}
//		if(++count1%5 == 0&&flag1 == 1) //亮一，灭四
//		{
//			flag1 = 0;
//		}
//		if(++count1%9 == 0&&flag1 == 1) //亮一，灭八
//		{
//			flag1 = 0;
//		}
			
			
		if(flag1 == 0)
		{			
		    flag1 = 1;
			GPIO_ResetBits(GPIOF, GPIO_Pin_10);	
		}
		else if(flag1 == 1)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_10);	
		}
			
				
			
			
			//清除中断标志位
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
		}
}

void  TIM1_UP_TIM10_IRQHandler(void)
{
		
		//判断中断标志位是否置1
		if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
		{
				
				
//		if(++count2%2 == 0&&flag1 == 1) //亮一，灭一
//		{
//			flag1 = 0;
//		}
//		if(++count2%3 == 0&&flag1 == 1) //亮一，灭二
//		{
//			flag1 = 0;
//		}
		if(++count2%5 == 0&&flag1 == 1) //亮一，灭四
		{
			flag1 = 0;
		}
//		if(++count2%9 == 0&&flag1 == 1) //亮一，灭八
//		{
//			flag1 = 0;
//		}
			
			
		if(flag1 == 0)
		{			
		    flag1 = 1;
			GPIO_ResetBits(GPIOE, GPIO_Pin_13);	
		}
		else if(flag1 == 1)
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_13);	
		}
			
				
			
			
			//清除中断标志位
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);	
		}
}

void  TIM4_IRQHandler(void)
{
		
		//判断中断标志位是否置1
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
		{
				
				
//	    if(++count3%2 == 0&&flag1 == 1) //亮一，灭一
//		{
//			flag1 = 0;
//		}
//		if(++count3%3 == 0&&flag1 == 1) //亮一，灭二
//		{
//			flag1 = 0;
//		}
//		if(++count3%5 == 0&&flag1 == 1) //亮一，灭四
//		{
//			flag1 = 0;
//		}
		if(++count3%9 == 0&&flag1 == 1) //亮一，灭八
		{
			flag1 = 0;
		}
			
			
		if(flag1 == 0)
		{			
		    flag1 = 1;
			GPIO_ResetBits(GPIOE, GPIO_Pin_14);	
		}
		else if(flag1 == 1)
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_14);	
		}
			
				
			
			
			//清除中断标志位
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);	
		}
}


