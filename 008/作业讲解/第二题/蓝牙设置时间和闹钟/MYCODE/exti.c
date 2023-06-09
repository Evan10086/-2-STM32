#include "exti.h"

/**********************************

引脚说明

KEY0 连接PA0，选择下降沿触发
**********************************/
void Exti_PA0_Init(void)
{

	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	//使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//使能SYSCFG组时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	//输入模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;		//引脚0
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect EXTI Line0 to PA0 pin */
	//中断映射 PA0--EXTI0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	//配置中断控制器
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;			//中断线0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断级使能
	EXTI_Init(&EXTI_InitStructure);

	 /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	 NVIC_InitStructure.NVIC_IRQChannel 				  = EXTI0_IRQn;				//中断通道，只能在stm32f4xx.h中查找
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority 		  =	1;	//响应优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd 				  = ENABLE; //通道使能
	 NVIC_Init(&NVIC_InitStructure);

}


//编写中断服务函数。
/*********************************************************
a.中断服务函数名字不能随意取，只能在startup_stm32f40_41xxx.s中查找
b.中断函数命名规则： void 中断服务函数名(void)
c.中断服务函数是不需要进行调用，当条件满足后CPU自动执行的函数
d.中断一般不能执行过长时间

**********************************************************/


//粗延时
void delay(int n)
{
	int i,j;
	
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


void   EXTI0_IRQHandler(void)
{
	//判断标志是否置位
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		
			//15ms 作用过滤下降沿
			delay(15);
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
			{	
				*((unsigned int *)(0xC0000000)) = 0x88;
			}				
			
		//清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line0);	
	}

}
















