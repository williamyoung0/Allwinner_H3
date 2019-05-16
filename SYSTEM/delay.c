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
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL=0x01 ;      				//开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;      	 			//关闭计数器
	SysTick->VAL =0X00;       				//清空计数器 
}



void Delay_xms(u16 nms)
{	 	
	u32 temp;		
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick_LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL=0x01 ;          			//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;       				//关闭计数器
	SysTick->VAL =0X00;     		  		//清空计数器	  	    
} 



//延时nms 
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
