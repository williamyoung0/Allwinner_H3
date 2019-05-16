#ifndef __TIMER_H_
#define __TIMER_H_

#include "sys.h"
#include "stm32f4.h"

void TIM2_ETR_Init(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);




#endif
