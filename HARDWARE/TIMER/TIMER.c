#include "timer.h"
#include "sys.h"
#include "stm32f4.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR |= 1<<0;			//使能TIM1时钟
	RCC->AHB1ENR |= 1<<4;			//使能GPIOE时钟
	GPIO_Set(GPIOE,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);		//PWM输出引脚初始化
	GPIO_AF_Set(GPIOE,9,1);
	TIM1->ARR = arr;					//设置自动重载值
	TIM1->PSC = psc;
	TIM1->CCR1 = arr/2;
	TIM1->CCMR1 |= 1<<3;			//CH1预装载使能
	TIM1->CCMR1 |=7<<4;				//PWM模式2
	TIM1->CCER |= 1<<0;				//OC1输出使能
	TIM1->CCER &= ~(1<<1);			//输出极性选择
	TIM1->CR1 &= ~(1<<4);			//递增计数模式
	TIM1->CR1 |= 1<<7;				//ARPE缓冲
	TIM1->BDTR |= 1<<15;			//MOE主输出使能
	TIM1->CR1 |= 1<<0; 				//启动定时器
}

void TIM2_ETR_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1<<0;			//使能TIM2时钟
	RCC->AHB1ENR |= 1<<0;			//使能GPIOA时钟
	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);		//外部输入引脚初始化
	GPIO_AF_Set(GPIOA,5,1);
	GPIO_Set(GPIOA,PIN1,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);		//PWM输出引脚初始化
	GPIO_AF_Set(GPIOA,1,1);
	TIM2->SMCR &= ~(15<<8);			//无滤波器
	TIM2->SMCR &= ~(7<<12);			//外部触发预分频器关闭
//	TIM2->SMCR |= 1<<12;
	TIM2->SMCR |= 0<<15;			//上升沿
	TIM2->SMCR |= 1<<14;			//外部时钟模式2
	TIM2->ARR = arr;				//设置自动重载值
	TIM2->PSC = psc;				//设置分频系数
	TIM2->CCR2 = arr/2;				//设置占空比50%
	TIM2->CCMR1 |= 1<<11;  			//CH2预装载使能
	TIM2->CCMR1 |= 7<<12;  			//PWM模式2
	TIM2->CCER |= 1<<4;   			//OC2输出使能
	TIM2->CCER &= ~(1<<5);   		//输出极性选择
	TIM2->CR1 &= ~(1<<4);			//递增计数
	TIM2->CR1 |= 1<<7;    			//ARPE缓冲
	TIM2->CR1 |= 1<<0;				//启动定时器
}



