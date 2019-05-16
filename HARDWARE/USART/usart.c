#include "usart.h"
#include "sys.h"
#include "stdio.h"


#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}


void USART1_Init(u32 fck,u32 bound)
{
	float temp;
	u16 Mantissa;
//	u16 Fraction;
	temp=(float)(fck*1000000)/(16*bound);
	Mantissa=temp;
//	Fraction=(temp-Mantissa)*16;        
//	Mantissa<<=4;                   
//	Mantissa+=Fraction;
	Mantissa=(Mantissa<<4)+((temp-Mantissa)*16);
	RCC->AHB1ENR |= 1<<0;
	RCC->APB2ENR |= 1<<4;
	GPIO_Set(GPIOA,PIN9|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
	GPIO_AF_Set(GPIOA,9,7);
	GPIO_AF_Set(GPIOA,10,7);
	USART1->BRR=Mantissa;
	USART1->CR1&=~(1<<15);
	USART1->CR1|=1<<3;
	USART1->CR1|=1<<2;
	USART1->CR1|=1<<13;
}


