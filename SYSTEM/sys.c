#include "sys.h"
#include "stm32f4.h"
//�����ڲ�ʱ��
//��λCFGR
//��β��ʱ�ӡ���CSS����PLL
//��λPLLCFGR
//HSE����·
//��ʱ���ж�

u8 Sys_Clock_Set(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{ 
	u16 retry=0;
	u8 status=0;
	RCC->CR|=1<<16;				//HSE ���� 
	while(((RCC->CR&(1<<17))==0)&&(retry<0X1FFF))retry++;//�ȴ�HSE RDY
	if(retry==0X1FFF)status=1;	//HSE�޷�����
	else   
	{
		RCC->APB1ENR|=1<<28;	//��Դ�ӿ�ʱ��ʹ��
		PWR->CR|=3<<14; 		//������ģʽ,ʱ�ӿɵ�168Mhz
		RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);//HCLK ����Ƶ;APB1 4��Ƶ;APB2 2��Ƶ. 
		RCC->CR&=~(1<<24);	//�ر���PLL
		RCC->PLLCFGR=pllm|(plln<<6)|(((pllp>>1)-1)<<16)|(pllq<<24)|(1<<22);//������PLL,PLLʱ��Դ����HSE
		RCC->CR|=1<<24;			//����PLL
		while((RCC->CR&(1<<25))==0);//�ȴ�PLL׼���� 
		FLASH->ACR|=1<<8;		//ָ��Ԥȡʹ��.
		FLASH->ACR|=1<<9;		//ָ��cacheʹ��..
		FLASH->ACR|=5<<0;		//5��CPU�ȴ���
		FLASH->ACR|=1<<10;		//����cacheʹ����. 
		RCC->CFGR&=~(3<<0);		//����
		RCC->CFGR|=2<<0;		//ѡ����PLL��Ϊϵͳʱ��	 
		while((RCC->CFGR&(3<<2))!=(2<<2));//�ȴ���PLL��Ϊϵͳʱ�ӳɹ�. 
	} 
	return status;
}  

//ϵͳʱ�ӳ�ʼ������
//plln:��PLL��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:64~432.
//pllm:��PLL����ƵPLL��Ƶϵ��(PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
//pllp:ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2,4,6,8.(������4��ֵ!)
//pllq:USB/SDIO/������������ȵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2~15.
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
{  
	RCC->CR|=0x00000001;		//����HISON,�����ڲ�����RC��
	RCC->CFGR=0x00000000;		//CFGR���� 
	RCC->CR&=0xFEF6FFFF;		//HSEON,CSSON,PLLON���� 
	RCC->PLLCFGR=0x24003010;	//PLLCFGR�ָ���λֵ 
	RCC->CR&=~(1<<18);			//HSEBYP����,�ⲿ������·
	RCC->CIR=0x00000000;		//��ֹRCCʱ���ж� 
	Sys_Clock_Set(plln,pllm,pllp,pllq);//����ʱ�� 
}		   
 

//GPIO���ú���
void GPIO_Set(GPIO_TpyeDef * GPIOx,u32 PINx,u8 mode,u8 otype,u8 speed,u8 pupd)
{
	u8 i;
	for(i=0;i<16;i++)
	{
		if((1<<i)&PINx)
		{
			GPIOx->MODER &= ~(3<<i*2);
			GPIOx->MODER |= (mode<<i*2);
			if((mode==0x01)||(mode==0x02))
			{
				GPIOx->OTYPER &= ~(1<<i);
				GPIOx->OTYPER |=  (otype<<i);
				GPIOx->OSPEEDR &= ~(3<<i*2);
				GPIOx->OSPEEDR |= (speed<<i*2);
			}
			GPIOx->PUPDR &=~(3<<i*2);
			GPIOx->PUPDR |= (pupd<<i*2);
		}
	}
}

void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//ȡ����λ
	temp1<<=8;
	temp=SCB->AIRCR;  //��ȡ��ǰ������
	temp&=0X0000F8FF; //�����ǰ����
	temp|=0X05FA0000; //д��Կ��
	temp|=temp1;	   
	SCB->AIRCR=temp;  //���÷���	    	  				   
}

void NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM) 
{ 
	u8 EXTOFFSET=(BITx%4)*4;  
	RCC->APB2ENR|=1<<14;  						//ʹ��SYSCFGʱ��  
	SYSCFG->EXTICR[BITx/4]&=~(0x000F<<EXTOFFSET);//���ԭ�����ã�����
	SYSCFG->EXTICR[BITx/4]|=GPIOx<<EXTOFFSET;	//EXTI.BITxӳ�䵽GPIOx.BITx 
	//�Զ�����
	EXTI->IMR|=1<<BITx;					//����line BITx�ϵ��ж�(���Ҫ��ֹ�жϣ��򷴲�������)
	if(TRIM&0x01)EXTI->FTSR|=1<<BITx;	//line BITx���¼��½��ش���
	if(TRIM&0x02)EXTI->RTSR|=1<<BITx;	//line BITx���¼��������ش���
} 


void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	  
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//���÷���
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;								//ȡ����λ
	NVIC->ISER[NVIC_Channel/32]|=1<<NVIC_Channel%32;//ʹ���ж�λ(Ҫ����Ļ�,����ICER��ӦλΪ1����)
	NVIC->IP[NVIC_Channel]|=temp<<4;				//������Ӧ���ȼ����������ȼ�   	    	  				   
} 


//GPIO���ú���
//AF0:MCO/SWD/SWCLK/RTC   AF1:TIM1/TIM2;            AF2:TIM3~5;               AF3:TIM8~11
//AF4:I2C1~I2C3;          AF5:SPI1/SPI2;            AF6:SPI3;                 AF7:USART1~3;
//AF8:USART4~6;           AF9;CAN1/CAN2/TIM12~14    AF10:USB_OTG/USB_HS       AF11:ETH
//AF12:FSMC/SDIO/OTG/HS   AF13:DCIM                 AF14:                     AF15:EVENTOUT
void GPIO_AF_Set(GPIO_TpyeDef* GPIOx,u8 BITx,u8 AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}   


