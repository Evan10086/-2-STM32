#include "tim.h"

/********************************
��ʱ��˵��

TIM2����APB1

TIM2 32λ��ʱ��

TIM2 Ƶ�ʣ�84MHZ

*********************************/

void Tim2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef        NVIC_InitStructure;

    //1��ʹ�ܶ�ʱ��ʱ�ӡ�
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

//    TIM_TimeBaseInitStruct.TIM_Prescaler         = (420 - 1); //��ʱ����Ƶ��84MHZ/420=200KHZ
//    TIM_TimeBaseInitStruct.TIM_Period            = (40000 - 1); //��ʱʱ��200ms��4000/200KHZ
//    TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up; //���ϼ���
//    TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1; //��Ƶ����
	
	
    TIM_TimeBaseInitStruct.TIM_Prescaler         = (84 - 1); 	//
    TIM_TimeBaseInitStruct.TIM_Period            = (200000 - 1); //
    TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up; //���ϼ���
    TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1; //��Ƶ����

    //2����ʼ����ʱ��������ARR,PSC��
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    NVIC_InitStructure.NVIC_IRQChannel                      = TIM2_IRQn; //ѡ���ж�ͨ��,�ж�ͨ����stm32f4xx.h����
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0x01; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0x01; //��Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE; //ͨ��ʹ��

    //3�����ö�ʱ���жϣ�����NVIC��
    NVIC_Init(&NVIC_InitStructure);

    //4������TIM2_DIER��������ж�
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    //5��ʹ�ܶ�ʱ����
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    //�ж��жϱ�־λ�Ƿ���1
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        //��תPF9�����ƽ��LEDָʾ�Ʊ仯��
        GPIO_ToggleBits(GPIOF, GPIO_Pin_9);

        //����жϱ�־λ
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
