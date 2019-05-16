#ifndef __SYS_H_
#define __SYS_H_

	#define  u8  unsigned char
	#define  u16 unsigned short int
	#define  u32 unsigned int
		
	
	
	#include "stm32f4.h"
	
	
	
//------------------------------位带操作--------------------------------------------	
	#define  BITBAND(addr,bitnum)	((addr&0xf0000000)+0x2000000+((addr&0xfffff)<<5)+(bitnum<<2))
	#define  MEM_ADDR(addr)   *((volatile unsigned long *)addr)
  #define  BIT_ADDR(addr,bitnum)  MEM_ADDR(BITBAND(addr,bitnum))

	
	#define  GPIOA_IDR  		0x40020010
	#define  GPIOE_IDR  		0x40021010
	#define  GPIOF_ODR  		0x40021414
	
	#define PFx_OUT(n)	BIT_ADDR(GPIOF_ODR,n)
	#define PEx_IN(n)   BIT_ADDR(GPIOE_IDR,n)
	#define PAx_IN(n)   BIT_ADDR(GPIOA_IDR,n)


	
	

	//GPIO设置专用宏定义
	#define GPIO_MODE_IN    	0		//普通输入模式
	#define GPIO_MODE_OUT		1		//普通输出模式
	#define GPIO_MODE_AF		2		//AF功能模式
	#define GPIO_MODE_AIN		3		//模拟输入模式

	#define GPIO_SPEED_2M		0		//GPIO速度2Mhz
	#define GPIO_SPEED_25M		1		//GPIO速度25Mhz
	#define GPIO_SPEED_50M		2		//GPIO速度50Mhz
	#define GPIO_SPEED_100M		3		//GPIO速度100Mhz

	#define GPIO_PUPD_NONE		0		//不带上下拉
	#define GPIO_PUPD_PU		1		//上拉
	#define GPIO_PUPD_PD		2		//下拉
	#define GPIO_PUPD_RES		3		//保留 

	#define GPIO_OTYPE_PP		0		//推挽输出
	#define GPIO_OTYPE_OD		1		//开漏输出 
	
	
	#define PIN0				1<<0
	#define PIN1				1<<1
	#define PIN2				1<<2
	#define PIN3				1<<3
	#define PIN4				1<<4
	#define PIN5				1<<5
	#define PIN6				1<<6
	#define PIN7				1<<7
	#define PIN8				1<<8
	#define PIN9				1<<9
	#define PIN10				1<<10
	#define PIN11				1<<11
	#define PIN12				1<<12
	#define PIN13				1<<13
	#define PIN14				1<<14
	#define PIN15				1<<15 
	
	#define GPIO_A 				0
	#define GPIO_B 				1
	#define GPIO_C				2
	#define GPIO_D 				3
	#define GPIO_E 				4
	#define GPIO_F 				5
	#define GPIO_G 				6 
	#define GPIO_H 				7 
	#define GPIO_I 				8 
		
	#define FTIR   				1  		//下降沿触发
	#define RTIR   				2  		//上升沿触发
	
  #define  EXTI0_IRQn           6      /*!< EXTI Line0 Interrupt                                              */
  #define  EXTI1_IRQn           7      /*!< EXTI Line1 Interrupt                                              */
  #define  EXTI2_IRQn           8      /*!< EXTI Line2 Interrupt                                              */
  #define  EXTI3_IRQn           9      /*!< EXTI Line3 Interrupt                                              */
  #define  EXTI4_IRQn           10     /*!< EXTI Line4 Interrupt                                              */
  #define  TIM3_IRQn            29
//-----------------------------函数声明----------------------------------------------
	void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq);
	void GPIO_Set(GPIO_TpyeDef * GPIOx,u32 PINx,u8 mode,u8 otype,u8 speed,u8 pupd);
	void NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);
	void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);
	void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);
	void GPIO_AF_Set(GPIO_TpyeDef* GPIOx,u8 BITx,u8 AFx);
#endif
