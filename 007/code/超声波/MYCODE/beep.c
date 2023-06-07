#include "beep.h"
#include "tim.h"


void beep_init(void)
{
	tim13_init();
	
	
	//·äÃùÆ÷½ûÃù
	tim13_set_duty(0);
}