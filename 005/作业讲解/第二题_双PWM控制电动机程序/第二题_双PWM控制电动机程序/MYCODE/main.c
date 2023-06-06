#include "stm32f4xx.h"
#include "exti.h"
#include "delay.h"
#include "pwm.h"

/*************************************
S1----��ת/��ת
S2----��ͣ/��������ͣ����������ʧ�ܣ�
S3----�ٶ�+
S4----�ٶ�-
������ʼ״̬Ϊ��ͣ����Ҫ��S2���У�������������������
****************************************************/
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	Exti_Init();
	PWM_TIM9_CH1_PA2_Init();
	PWM_TIM9_CH2_PA3_Init();
	while(1)
	{
		delay_s(1);
	}
}
