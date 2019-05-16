#include "delay.h"
#include "sys.h"
#include "stm32f4.h"

static u8  fac_us=0;							   
static u16 fac_ms=0;						
		

void Delay_init(u8 SYSCLK)
{
	SysTick->CTRL &= ~(1<<2);
	fac_us=SYSCLK/8;						
	fac_ms=(u16)fac_us*1000;	
}



void Delay_us(u32 nus)
{		
	u32 temp;  	 
	SysTick->LOAD=nus*fac_us; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL=0x01 ;      				//��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;      	 			//�رռ�����
	SysTick->VAL =0X00;       				//��ռ����� 
}



void Delay_xms(u16 nms)
{	 	
	u32 temp;		
	SysTick->LOAD=(u32)nms*fac_ms;			//ʱ�����(SysTick_LOADΪ24bit)
	SysTick->VAL =0x00;           			//��ռ�����
	SysTick->CTRL=0x01 ;          			//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       				//�رռ�����
	SysTick->VAL =0X00;     		  		//��ռ�����	  	    
} 



//��ʱnms 
//nms:0~65535
void Delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;						
	u16 remain=nms%540;
	while(repeat)
	{
		Delay_xms(540);
		repeat--;
	}
	if(remain)Delay_xms(remain);
} 
