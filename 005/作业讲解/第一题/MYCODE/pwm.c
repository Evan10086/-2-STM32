#include "pwm.h"

/*************************************
引脚说明
LED0连接在PF9,低电平灯亮；高电平，灯灭
TIM14_CH1(TIM14 -- APB1 16位  84MHZ)


//   beep     PF8/TIM13_CH1/FSMC_NIOWR/ADC3_IN6 
**************************************/
void Pwm_PF9_Init(void)
{
	GPIO_InitTypeDef  			GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef 			TIM_OCInitStruct;
	
	//（2）使能定时器14和相关IO口时钟。
	//使能定时器14时钟：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	//使能GPIOF时钟：
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	
	//（3）初始化IO口为复用功能输出。
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9; 		//引脚9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF; 	//复用模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; 	//推挽输出
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;	//速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOF, &GPIO_InitStruct);	
	

	//（4）GPIOF9复用映射到定时器14
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14); 
	
	
	
	//（5）初始化定时器：ARR,PSC等：
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数，在1MHZ下，用时1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
	
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);


	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM1;  //PWM1模式
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;//输出通道使能
	TIM_OCInitStruct.TIM_Pulse		= 0; //灯灭
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; //极性电平 这里选择低电平
	//（6）初始化输出比较参数:
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);
	
	
	
	//（7）使能预装载寄存器： 
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable); 
	//（8）使能自动重装载的预装载寄存器允许位	
	TIM_ARRPreloadConfig(TIM14,ENABLE);
	//（9）使能定时器。
	TIM_Cmd(TIM14, ENABLE);


}

//   beep     PF8/TIM13_CH1/FSMC_NIOWR/ADC3_IN6  高电平有效
void Pwm_PF8_Init(void)
{
	GPIO_InitTypeDef  			GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef 			TIM_OCInitStruct;
	
	//（2）使能定时器14和相关IO口时钟。
	//使能定时器14时钟：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	//使能GPIOF时钟：
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	
	//（3）初始化IO口为复用功能输出。
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_8; 		//引脚9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AF; 	//复用模式
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP; 	//推挽输出
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;	//速度
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOF, &GPIO_InitStruct);	
	

	//（4）GPIOF8复用映射到定时器13
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_TIM13); 
	
	
	
	//（5）初始化定时器：ARR,PSC等：
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); //84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数，在1MHZ下，用时1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;//分频因子
	
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseInitStruct);


	TIM_OCInitStruct.TIM_OCMode		= TIM_OCMode_PWM1;  //PWM1模式
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;//输出通道使能
	TIM_OCInitStruct.TIM_Pulse		= 0; //灯灭
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //极性电平 这里选择高电平
	//（6）初始化输出比较参数:
	TIM_OC1Init(TIM13, &TIM_OCInitStruct);
	
	
	
	//（7）使能预装载寄存器： 
	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable); 
	//（8）使能自动重装载的预装载寄存器允许位	
	TIM_ARRPreloadConfig(TIM13,ENABLE);
	//（9）使能定时器。
	TIM_Cmd(TIM13, ENABLE);


}
