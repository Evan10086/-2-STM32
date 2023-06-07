#include "sr04.h"
#include "sys.h"


/********************************

引脚说明
PA2做为普通输出
PA3做为普通输入

*********************************/
void Sr04_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	
	
	
	
	//使能GPIOF组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);
	//1、能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_6; 	//引脚6
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; //推挽输出
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;//速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_6; 	//引脚6
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;//输出模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; //推挽输出
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;//速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	

	
	TIM_TimeBaseInitStruct.TIM_Prescaler	= 84-1;  				// 84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period	= 50000-1;					TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;	// 向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;			// 分频因子
	//2、初始化定时器，配置ARR,PSC
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
			
	//5,不使能定时器
	   TIM_Cmd(TIM3, DISABLE);	

}

u16 Get_Sr04_Value(void)
{	
	uint32_t t=0;
	PBout(6)=1;
	delay_us(20);
	PBout(6)=0;
	
	//等待回响信号变为高电平
	while(PEin(6)==0)
	{
		t++;
		delay_us(1);
		
		//如果超时，就返回一个错误码
		if(t>=1000000)
			return 0xFFFFFFFF;
	}
	
	t=0;
	//测量高电平持续的时间
	while(PEin(6))
	{
	
		//延时8us,就是3mm的传输距离
		delay_us(8);
		
		t++;
	
	}
	
	//当前的传输距离
	return 3*(t/2);

}


