#include "stm32f4xx.h"
#include "led.h"
#include "key.h"



//����ʱ
void delay(int n)
{
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<30000; j++);

}


int main(void)
{
	
	int count = 0;

	Led_Init();
	Key_Init();
	
	
	while(1)
	{
		/*
		//���ó���1 ͨ������ʱ��������ͬ�¼�
		//�жϰ����Ƿ���
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
		{
			delay(20); //15ms��ʱ��������
			//�жϰ����Ƿ���
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
			{
				//��������
				
				//�����״̬
				//GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
				count++;
			
			}			
			
		}
		//4s�����¼�1
		if(count == 200)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);	
		}
		
		//8s�����¼�2
		if(count == 400)
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_13);	
		}		
		*/
		
		//�жϰ����Ƿ���
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
		{
			delay(15); //15ms��ʱ��������
			//�жϰ����Ƿ���
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET)
			{
				//�ȴ������ɿ�
				while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET);
				
				//�����״̬
				GPIO_ToggleBits(GPIOF, GPIO_Pin_9);	
			
				
			
			}			
			
		}		
	
	}
	
	return 0;
}
