#include "beep.h"
#include "tim.h"


void beep_init(void)
{
	tim13_init();
	
	
	//����������
	tim13_set_duty(0);
}