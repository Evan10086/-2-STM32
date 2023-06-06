#include "pwm.h"

/********************************************
引脚说明
电机正端连接在PA2
TIM9_CH1(TIM9 -- APB2 16位  168MHZ)
*******************************************/
void PWM_TIM9_CH1_PA2_Init(void)
{
	GPIO_InitTypeDef 		GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;
	
	//使能定时器9
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	//打开GPIOA的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_2;		//引脚
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF; 	//复用功能
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;	//输出推挽
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ中速
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化引脚配置	
	
	//映射为定时器功能  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler 	= 167;		//168分频  1MHZ
	TIM_TimeBaseStructure.TIM_Period 		= 999;		//PWM周期为1ms
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//分频因子
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;			//PWM1模#式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使用通道使能
	TIM_OCInitStructure.TIM_Pulse 		= 500;						//设置比较寄存器的值为500
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;  		//极性电平为高电平
	//OC1 -->通道1
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);
	
	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	
	//使能自动重装载的预装载寄存器允许位
	TIM_ARRPreloadConfig(TIM9, ENABLE);

	//使能定时器
	TIM_Cmd(TIM9, ENABLE);
}
/********************************************
引脚说明
电机负端连接在PA3
TIM9_CH2(TIM9 -- APB2 16位  168MHZ)
*******************************************/
void PWM_TIM9_CH2_PA3_Init(void)
{
	GPIO_InitTypeDef 		GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef		TIM_OCInitStructure;

	//使能定时器9
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	//打开GPIOA的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin 	= GPIO_Pin_3;		//引脚3
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF; 	//复用功能
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;	//输出推挽
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_25MHz;	//25MHZ中速
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化引脚配置	
	
	//映射为定时器功能  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM9);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler 	= 167;		//168分频  1MHZ
	TIM_TimeBaseStructure.TIM_Period 		= 999;		//PWM周期为1ms
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//分频因子
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;			//PWM1模#式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使用通道使能
	TIM_OCInitStructure.TIM_Pulse 		= 500;						//设置比较寄存器的值为500
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;  		//极性电平为高电平
	//OC1 -->通道1
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);
	
	//使能预装载寄存器
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);
	
	//使能自动重装载的预装载寄存器允许位
	TIM_ARRPreloadConfig(TIM9, ENABLE);

	//使能定时器
	TIM_Cmd(TIM9, ENABLE);
}
