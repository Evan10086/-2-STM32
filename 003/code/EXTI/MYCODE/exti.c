#include "exti.h"

/********************************

KEY0 连接PA0，选择下降沿触发

*********************************/
void Exti_PA0_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Enable GPIOA clock */
	//使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable SYSCFG clock */
	//使能SYSCFG组时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //上拉
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;    //引脚0
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect EXTI Line0 to PA0 pin */
	//映射PA0到EXTI0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;			//中断线0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;	//中断线使能
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel 					 = EXTI0_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0x01;//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;//通道使能
	NVIC_Init(&NVIC_InitStructure);


}

/**************************************************
STM32中断服务函数注意要点
a.中断服务函数不能处理时间过长。
b.中断服务函数名是不能随意写的，只能在startup_stm32f40_41xxx.s
中查找
c.STM32中断服务函数固定格式void 中断服务函数名(void)
d.中断服务函数是不需要在程序当中调用的，当中断条件满足，CPU自动
执行的函数。


***************************************************/

void EXTI0_IRQHandler(void)
{
	//判断中断标志位是否置1
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
		
		//清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line0);	
	}
	
	
	
}






