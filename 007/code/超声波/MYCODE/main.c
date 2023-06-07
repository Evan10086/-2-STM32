#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"
#include "sr04.h"
#include "sys.h"

GPIO_InitTypeDef   GPIO_InitStructure;

u32 time_count = 0;

u8 buffer[16] = {0};
u8 rx_buffer[16] = {0};
u8 rx_i, count = 0;
u8 rx_flag = 0;




void USART1_IRQHandler(void)
{
	//�ж��жϱ�־λ�Ƿ���1
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		
		//��������
		buffer[count++] = USART_ReceiveData(USART1);
		//�жϽ��ܵ��ַ��Ƿ�Ϊ������
		if(buffer[count-1] == ':')
		{
			//���˽�����
			for(rx_i=0; rx_i<(count-1); rx_i++)
			{
				rx_buffer[rx_i] = buffer[rx_i]; 
			}
			
			memset(buffer, 0, sizeof(buffer));
			
			//��һ֡���ݴ�buffer[0]��ʼ�洢
			count = 0;
			rx_flag = 1; //һ֡���ݽ������
		}	
	}
}





int main(void)
{
	
	uint32_t distance=0;
	uint32_t duty=10;
	uint32_t distance_safe=1;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF, ENABLE);

	/* Configure PF9 PF10 in output pushpull mode������PF9 PF10����Ϊ���ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;		//��9����10������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				//�������ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//����ģʽ��������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//����IO���ٶ�Ϊ100MHz��Ƶ��Խ������Խ�ã�Ƶ��Խ�ͣ�����Խ��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//����Ҫ��������
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	
	/* Configure PE13 PE14 in output pushpull mode������PE13 PE14����Ϊ���ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;		//��13����14������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				//�������ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//����ģʽ��������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//����IO���ٶ�Ϊ100MHz��Ƶ��Խ������Խ�ã�Ƶ��Խ�ͣ�����Խ��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;			//����Ҫ��������
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	


	//�����ж����ȼ��ķ���
	//����֧��4����ռ���ȼ���֧��4����Ӧ���ȼ�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	

	PFout(9)=1;
	PFout(10)=1;	
	PEout(13)=1;
	PEout(14)=1;
	
	//����1��ʼ����������115200bps
	usart1_init(115200);

	//������ģ���ʼ��
	sr04_init();
	
	//��ӷ�������ʼ��
	beep_init();
	
	
	//�����ĳ�ʼ��
	key_init();
	
	while(1)
	{
		distance=sr04_get_distance();
		
		if(distance==0xFFFFFFFF)
		{
			//ģ���п���û�����Ӻã����Ӵ����Ż�Ű����ɶ�
			printf("sr04 is error\r\n");
		}
		else if(distance>=20 && distance<=4000)
		{
			//��������ȷ��
			printf("distance=%dmm\r\n",distance);		
		
			if(distance>=200)
			{
				PFout(9)=1;
				PFout(10)=1;
				PEout(13)=1;
				PEout(14)=1;	
				
				distance_safe=1;
			}
			else if(distance>=150 && distance<200)
			{
				PFout(9)=0;
				PFout(10)=1;
				PEout(13)=1;
				PEout(14)=1;	

				
				distance_safe=1;
			}	
			else if(distance>=100 && distance<150)
			{
				PFout(9)=0;
				PFout(10)=0;
				PEout(13)=1;
				PEout(14)=1;	
				
				distance_safe=0;
				
				tim13_set_freq(2);

			}				
			else if(distance>=50 && distance<100)
			{
				PFout(9)=0;
				PFout(10)=0;
				PEout(13)=0;
				PEout(14)=1;	
				
				distance_safe=0;
				
				tim13_set_freq(4);

			}	

			else if(distance<50)
			{
				PFout(9)=0;
				PFout(10)=0;
				PEout(13)=0;
				PEout(14)=0;	
				
				tim13_set_freq(10);
				
				distance_safe=0;
			}	

			//���ǰ�ȫ���룬�����������
			if(distance_safe)
				tim13_set_duty(0);
			//�����ǰ�ȫ���룬����������ݶ�Ӧ��ռ�ձȽ�������
			else
				tim13_set_duty(duty);
				
		}
		else
		{
			//�������쳣��
			printf("sr04 get distance is error\r\n");			
		
		}
		
		//��Ӱ���������
		if(PAin(0)==0)
		{
			//ռ�ձȼ�1��������С
			if(duty>0)
			{
				duty-=1;
				
				tim13_set_duty(duty);
			
			}
				
		
		}
		
		if(PEin(2)==0)
		{
			//ռ�ձȼ�1���������
			if(duty<30)
			{
				duty+=1;
				
				tim13_set_duty(duty);
			
			}		
		}
		
		//��ʱ500ms
		delay_ms(500);
	}
	
	return 0;
}




