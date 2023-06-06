#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"



u8 rx_flag = 0;  //������ϱ�־
u8 rx_i, count = 0;
u8 buffer[32] = {0};
u8 rx_buffer[32] = {0};

void USART1_IRQHandler(void)
{
	//�жϱ�־�Ƿ���λ
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			
		//����1��������							
		buffer[count++] = USART_ReceiveData(USART1);	

		if(buffer[count-1] == ':')
		{
			//���˽�β��':'
			for(rx_i=0; rx_i< (count-1); rx_i++)
			{
				rx_buffer[rx_i] = buffer[rx_i];
			}
			
			//��һ֡���ݴ�buffer[0]��ʼ���ܡ�
			count = 0;
			
			//�������
			memset(buffer, 0, sizeof(buffer));
			
			//��ʾ���ݽ������
			rx_flag = 1;		
		
		}
//		printf("rx_buffer:%s\r\n", rx_buffer);
		

	}

}

//int check_fun(unsigned char *buf, int len)
//{
//    int i = 0;

//    unsigned char temp = 0;

//    for (i = 0; i < len; i++)
//    {
//        temp += buf[i];
//    }

//		if(buf[i] == temp)
//		{
//			return 0;
//		}
//		else
//		{
//			return -1;
//		}
//}

int check_fun(unsigned char *buf, int len)
{
    int i = 0;

    unsigned char temp = buf[0];

    for (i = 1; i < len; i++)
    {
        temp ^= buf[i];
    }

	if(buf[i] == temp)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


int main(void)
{	
	
	
	//����NVIC���� �ڶ��� ��ռ���ȼ���Χ��0~3 ��Ӧ���ȼ���Χ��0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Delay_Init();
	
	
	Led_Init();


	Usart1_Init(115200);
	
	while(1)
	{
		if(rx_flag == 1)
		{
			printf("rx_buffer:%s\r\n", rx_buffer);
			
			if(check_fun(rx_buffer, 5) == 0)
			{
				if(strncmp(rx_buffer, "HCL11", 5) == 0)
			  {
					LED1(1);//����
				}
				if(strncmp(rx_buffer, "HCL10", 5) == 0)
				{
					LED1(0);//���
				}	
			
				if(strncmp(rx_buffer, "HCL21", 5) == 0)
				{
					LED2(1);
				}	
				if(strncmp(rx_buffer, "HCL20", 5) == 0)
				{
					LED2(0);
				}	
			
				if(strncmp(rx_buffer, "HCL31", 5) == 0)
				{
					LED3(1);
				}		
				if(strncmp(rx_buffer, "HCL30", 5) == 0)
				{
					LED3(0);
				}	
			
				if(strncmp(rx_buffer, "HCL41", 5) == 0)
				{
					LED4(1);
				}	
				if(strncmp(rx_buffer, "HCL40", 5) == 0)
				{
					LED4(0);
				}	
			}
			
			memset(rx_buffer, 0, sizeof(rx_buffer));
			
			rx_flag = 0;
		}
		
		
		//delay_s(1);
	}
	


	return 0;
}