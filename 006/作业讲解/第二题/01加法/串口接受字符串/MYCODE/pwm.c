#include "pwm.h"


/****************************************
引脚说明

LED0连接在PF9,低电平灯亮；高电平，灯灭
TIM14_CH1(TIM14 -- APB1 16位  84MHZ)

*****************************************/

void Pwm_PF9_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef			TIM_OCInitStruct;
	
	
	
	/* TIM10 clock enable */
	//使能定时器14时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	/* GPIOF clock enable */
	//使能GPIOF时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	/* GPIOF Configuration: TIM10 CH1 (PF6) */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9 ;		//引脚9
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;		//复用模式
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;	//复用推挽
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ;	//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure); 

	/* Connect TIM pins to AF3 */
	//定时器映射到PF9  选定作用
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);
	
	
	//设置PWM周期
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1);  //84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1);//计1000个数 ，在1MHZ, 用时1ms PWM周期1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //分频因子
	//2、初始化定时器，配置ARR,PSC。
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);
	

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStruct.TIM_OCMode 		= TIM_OCMode_PWM1;		//PWM1模式
	TIM_OCInitStruct.TIM_OCPolarity 	= TIM_OCPolarity_Low;	//输出极性电平，这里选择低电平
	TIM_OCInitStruct.TIM_OutputState 	= TIM_OutputState_Enable;//输出使能
	TIM_OCInitStruct.TIM_Pulse 			= 0x00;	//设置比较寄存器CCR1值
	
	//OC1初始化  OC1表示通道1
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);


	//使能通道1重载寄存器。
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);

	//使能重载寄存器ARR
	TIM_ARRPreloadConfig(TIM14, ENABLE);

	//使能定时器
	TIM_Cmd(TIM14, ENABLE);


}