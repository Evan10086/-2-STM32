#include "tim.h"

GPIO_InitTypeDef   GPIO_InitStructure;

EXTI_InitTypeDef   EXTI_InitStructure;


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

uint32_t tim13_cnt=0;

void tim13_init(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* 定时器13的时钟使能*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	

	/*定时器的基本配置，用于配置定时器的输出脉冲的频率为100Hz */
	TIM_TimeBaseStructure.TIM_Period = (40000/100)-1;					//设置定时脉冲的频率
	TIM_TimeBaseStructure.TIM_Prescaler = 2100-1;						//第一次分频，简称为预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				//第二次分频,当前实现1分频，也就是不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	tim13_cnt=TIM_TimeBaseStructure.TIM_Period;
	
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);

	/* 配置PF8 引脚为复用模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;					//第8根引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//设置复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽模式，增加驱动电流
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//设置IO的速度为100MHz，频率越高性能越好，频率越低，功耗越低
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//不需要上拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);
	
	
	/* 让定时器14 PWM 的通道 1 工作在模式 1*/
	 //PWM 模式 1， 在递增模式下， 只要TIMx_CNT < TIMx_CCR1， 通道 1 便为有效状态（高电平）， 否则为无效状态（低电平）。
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //允许输出
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//有效的时候， 输出高电平
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);
	
	/*  使能定时器 13 工作 */
	TIM_Cmd(TIM13, ENABLE);
}

//设置定时器13的PWM频率
void tim13_set_freq(uint32_t freq)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/*定时器的基本配置，用于配置定时器的输出脉冲的频率为freq Hz */
	TIM_TimeBaseStructure.TIM_Period = (40000/freq)-1;					//设置定时脉冲的频率
	TIM_TimeBaseStructure.TIM_Prescaler = 2100-1;						//第一次分频，简称为预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;				//第二次分频,当前实现1分频，也就是不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	tim13_cnt= TIM_TimeBaseStructure.TIM_Period;
	
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);

}

//设置定时器13的PWM占空比0%~100%
void tim13_set_duty(uint32_t duty)
{
	uint32_t cmp=0;
	
	cmp = (tim13_cnt+1) * duty/100;

	TIM_SetCompare1(TIM13,cmp);
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



