#include "timer.h"
#include "sys.h"
#include "delay.h"

int main()
{
	Stm32_Clock_Init(336,8,2,7);
	TIM1_PWM_Init(1000,8399);
	TIM2_ETR_Init(10,0);
	while(1);
}
