#include "tim.h"

/********************************
定时器说明

TIM2挂在APB1

TIM2 32位定时器

TIM2 频率：84MHZ

*********************************/

void Tim2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef        NVIC_InitStructure;

    //1、使能定时器时钟。
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

//    TIM_TimeBaseInitStruct.TIM_Prescaler         = (420 - 1); //定时器分频，84MHZ/420=200KHZ
//    TIM_TimeBaseInitStruct.TIM_Period            = (40000 - 1); //定时时间200ms，4000/200KHZ
//    TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up; //向上计数
//    TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1; //分频因子
	
	
    TIM_TimeBaseInitStruct.TIM_Prescaler         = (84 - 1); 	//
    TIM_TimeBaseInitStruct.TIM_Period            = (200000 - 1); //
    TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up; //向上计数
    TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1; //分频因子

    //2、初始化定时器，配置ARR,PSC。
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    NVIC_InitStructure.NVIC_IRQChannel                      = TIM2_IRQn; //选择中断通道,中断通道在stm32f4xx.h查找
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0x01; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0x01; //响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE; //通道使能

    //3、启用定时器中断，配置NVIC。
    NVIC_Init(&NVIC_InitStructure);

    //4、设置TIM2_DIER允许更新中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    //5、使能定时器。
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    //判断中断标志位是否置1
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        //反转PF9输出电平，LED指示灯变化。
        GPIO_ToggleBits(GPIOF, GPIO_Pin_9);

        //清除中断标志位
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
