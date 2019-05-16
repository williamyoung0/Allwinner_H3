#include "timer.h"
#include "sys.h"
#include "stm32f4.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR |= 1<<0;			//ʹ��TIM1ʱ��
	RCC->AHB1ENR |= 1<<4;			//ʹ��GPIOEʱ��
	GPIO_Set(GPIOE,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);		//PWM������ų�ʼ��
	GPIO_AF_Set(GPIOE,9,1);
	TIM1->ARR = arr;					//�����Զ�����ֵ
	TIM1->PSC = psc;
	TIM1->CCR1 = arr/2;
	TIM1->CCMR1 |= 1<<3;			//CH1Ԥװ��ʹ��
	TIM1->CCMR1 |=7<<4;				//PWMģʽ2
	TIM1->CCER |= 1<<0;				//OC1���ʹ��
	TIM1->CCER &= ~(1<<1);			//�������ѡ��
	TIM1->CR1 &= ~(1<<4);			//��������ģʽ
	TIM1->CR1 |= 1<<7;				//ARPE����
	TIM1->BDTR |= 1<<15;			//MOE�����ʹ��
	TIM1->CR1 |= 1<<0; 				//������ʱ��
}

void TIM2_ETR_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1<<0;			//ʹ��TIM2ʱ��
	RCC->AHB1ENR |= 1<<0;			//ʹ��GPIOAʱ��
	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);		//�ⲿ�������ų�ʼ��
	GPIO_AF_Set(GPIOA,5,1);
	GPIO_Set(GPIOA,PIN1,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);		//PWM������ų�ʼ��
	GPIO_AF_Set(GPIOA,1,1);
	TIM2->SMCR &= ~(15<<8);			//���˲���
	TIM2->SMCR &= ~(7<<12);			//�ⲿ����Ԥ��Ƶ���ر�
//	TIM2->SMCR |= 1<<12;
	TIM2->SMCR |= 0<<15;			//������
	TIM2->SMCR |= 1<<14;			//�ⲿʱ��ģʽ2
	TIM2->ARR = arr;				//�����Զ�����ֵ
	TIM2->PSC = psc;				//���÷�Ƶϵ��
	TIM2->CCR2 = arr/2;				//����ռ�ձ�50%
	TIM2->CCMR1 |= 1<<11;  			//CH2Ԥװ��ʹ��
	TIM2->CCMR1 |= 7<<12;  			//PWMģʽ2
	TIM2->CCER |= 1<<4;   			//OC2���ʹ��
	TIM2->CCER &= ~(1<<5);   		//�������ѡ��
	TIM2->CR1 &= ~(1<<4);			//��������
	TIM2->CR1 |= 1<<7;    			//ARPE����
	TIM2->CR1 |= 1<<0;				//������ʱ��
}



