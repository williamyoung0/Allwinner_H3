#ifndef __STM32F4_H_
#define __STM32F4_H_

#include "sys.h"



//-----------------------------各个寄存器基地址------------------------------------------
#define GPIOA    ((GPIO_TpyeDef  *)0x40020000)
#define GPIOE    ((GPIO_TpyeDef  *)0x40021000)
#define GPIOF    ((GPIO_TpyeDef  *)0x40021400)
#define RCC      ((RCC_TypeDef   *)0x40023800)
#define SysTick  ((SysTick_Type  *)0xE000E010)
#define PWR      ((PWR_TypeDef   *)0x40007000)
#define FLASH    ((FLASH_TypeDef *)0x40023C00)
#define EXTI     ((EXTI_TypeDef  *)0x40013C00)
#define SYSCFG	 ((SYSCFG_TypeDef*)0x40013800)
#define SCB      ((SCB_Type      *)0xE000ED00)
#define NVIC     ((NVIC_Type     *)0xE000E100)
#define TIM1     ((TIM_TypeDef   *)0x40010000)
#define TIM2     ((TIM_TypeDef   *)0x40000000)
#define TIM3     ((TIM_TypeDef   *)0x40000400)
#define TIM14    ((TIM_TypeDef   *)0x40002000)
#define USART1   ((USART_TypeDef* )0x40011000)
//------------------------------------GPIO-----------------------------------------------
typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u16 BSRRL;
	volatile u16 BSRRH;
	volatile u32 LCKR;
	volatile u32 AFR[2];
}GPIO_TpyeDef;
//------------------------------------RCC-----------------------------------------------
typedef struct
{
  volatile u32 CR;            
  volatile u32 PLLCFGR;       
  volatile u32 CFGR;          
  volatile u32 CIR;           
  volatile u32 AHB1RSTR;     
  volatile u32 AHB2RSTR;      
  volatile u32 AHB3RSTR;     
  u32      RESERVED0;                                                          
  volatile u32 APB1RSTR;     
  volatile u32 APB2RSTR;
  u32      RESERVED1[2];                                                            
  volatile u32 AHB1ENR;       
  volatile u32 AHB2ENR;      
  volatile u32 AHB3ENR;      
  u32      RESERVED2;    
  volatile u32 APB1ENR;      
  volatile u32 APB2ENR;      
  u32      RESERVED3[2]; 
  volatile u32 AHB1LPENR;    
  volatile u32 AHB2LPENR;    
  volatile u32 AHB3LPENR;    
  u32      RESERVED4;                                                                        
  volatile u32 APB1LPENR;    
  volatile u32 APB2LPENR;    
  u32      RESERVED5[2];                                                          
  volatile u32 BDCR;          
  volatile u32 CSR;          
  u32      RESERVED6[2];                                                           
  volatile u32 SSCGR;        
  volatile u32 PLLI2SCFGR;   
  volatile u32 PLLSAICFGR;    
  volatile u32 DCKCFGR;       
}RCC_TypeDef;
//------------------------------------SYSTICK-----------------------------------------------
typedef struct
{
  volatile u32 CTRL;                   
  volatile u32 LOAD;                   
  volatile u32 VAL;                     
} SysTick_Type;

typedef struct
{
  volatile u32 CR;   
  volatile u32 CSR;  
} PWR_TypeDef;
//------------------------------------FLASH-----------------------------------------------
typedef struct
{
  volatile u32 ACR;      
  volatile u32 KEYR;     
  volatile u32 OPTKEYR;  
  volatile u32 SR;       
  volatile u32 CR;       
  volatile u32 OPTCR;    
  volatile u32 OPTCR1;   
} FLASH_TypeDef;

//-----------------------------------
typedef struct
{
  volatile u32 IMR;    /*!< EXTI Interrupt mask register,            Address offset: 0x00 */
  volatile u32 EMR;    /*!< EXTI Event mask register,                Address offset: 0x04 */
  volatile u32 RTSR;   /*!< EXTI Rising trigger selection register,  Address offset: 0x08 */
  volatile u32 FTSR;   /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
  volatile u32 SWIER;  /*!< EXTI Software interrupt event register,  Address offset: 0x10 */
  volatile u32 PR;     /*!< EXTI Pending register,                   Address offset: 0x14 */
} EXTI_TypeDef;


//----------------------------------------
typedef struct
{
  volatile u32 MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
  volatile u32 PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
  volatile u32 EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
  u32      RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */ 
  volatile u32 CMPCR;        /*!< SYSCFG Compensation cell control register,         Address offset: 0x20      */
} SYSCFG_TypeDef;


//------------------------------------------------
typedef struct
{
  volatile u32 CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
  volatile u32 ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
  volatile u32 VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
  volatile u32 AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
  volatile u32 SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
  volatile u32 CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
  volatile const  u8  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile u32 SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
  volatile u32 CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
  volatile u32 HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
  volatile u32 DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
  volatile u32 MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
  volatile u32 BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
  volatile u32 AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
  volatile const  u32 PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
  volatile const  u32 DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
  volatile const  u32 ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
  volatile const  u32 MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
  volatile const  u32 ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
  u32 RESERVED0[5];
  volatile u32 CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
} SCB_Type;

//----------------------------------------------------
typedef struct
{
  volatile u32 ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       u32 RESERVED0[24];
  volatile u32 ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
       u32 RSERVED1[24];
  volatile u32 ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
       u32 RESERVED2[24];
  volatile u32 ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
       u32 RESERVED3[24];
  volatile u32 IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
       u32 RESERVED4[56];
  volatile u8  IP[240];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       u32 RESERVED5[644];
  volatile const u32 STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
}  NVIC_Type;

//----------------------------TIMER3


typedef struct
{
  volatile u16 CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
  u16      RESERVED0;   /*!< Reserved, 0x02                                            */
  volatile u16 CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
  u16      RESERVED1;   /*!< Reserved, 0x06                                            */
  volatile u16 SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
  u16      RESERVED2;   /*!< Reserved, 0x0A                                            */
  volatile u16 DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
  u16      RESERVED3;   /*!< Reserved, 0x0E                                            */
  volatile u16 SR;          /*!< TIM status register,                 Address offset: 0x10 */
  u16      RESERVED4;   /*!< Reserved, 0x12                                            */
  volatile u16 EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
  u16      RESERVED5;   /*!< Reserved, 0x16                                            */
  volatile u16 CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
  u16      RESERVED6;   /*!< Reserved, 0x1A                                            */
  volatile u16 CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
  u16      RESERVED7;   /*!< Reserved, 0x1E                                            */
  volatile u16 CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
  u16      RESERVED8;   /*!< Reserved, 0x22                                            */
  volatile u32 CNT;         /*!< TIM counter register,                Address offset: 0x24 */
  volatile u16 PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
  u16      RESERVED9;   /*!< Reserved, 0x2A                                            */
  volatile u32 ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
  volatile u16 RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
  u16      RESERVED10;  /*!< Reserved, 0x32                                            */
  volatile u32 CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
  volatile u32 CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
  volatile u32 CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
  volatile u32 CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
  volatile u16 BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
  u16      RESERVED11;  /*!< Reserved, 0x46                                            */
  volatile u16 DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
  u16      RESERVED12;  /*!< Reserved, 0x4A                                            */
  volatile u16 DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
  u16      RESERVED13;  /*!< Reserved, 0x4E                                            */
  volatile u16 OR;          /*!< TIM option register,                 Address offset: 0x50 */
  u16      RESERVED14;  /*!< Reserved, 0x52                                            */
} TIM_TypeDef;
//-----------------------------USART-----------------------------------

typedef struct
{
  volatile u16 SR;         /*!< USART Status register,                   Address offset: 0x00 */
  u16      RESERVED0;  /*!< Reserved, 0x02                                                */
  volatile u16 DR;         /*!< USART Data register,                     Address offset: 0x04 */
  u16      RESERVED1;  /*!< Reserved, 0x06                                                */
  volatile u16 BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  u16      RESERVED2;  /*!< Reserved, 0x0A                                                */
  volatile u16 CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  u16      RESERVED3;  /*!< Reserved, 0x0E                                                */
  volatile u16 CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  u16      RESERVED4;  /*!< Reserved, 0x12                                                */
  volatile u16 CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  u16      RESERVED5;  /*!< Reserved, 0x16                                                */
  volatile u16 GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
  u16      RESERVED6;  /*!< Reserved, 0x1A                                                */
} USART_TypeDef;

#endif
