#ifndef __DELAY_H
#define __DELAY_H
#include "sys.h"

void Delay_init(u8 SYSCLK);	//初始化滴答定时器时钟
void Delay_us(u32 nus);			//us级延时
void Delay_xms(u16 nms);
void Delay_ms(u16 nms);			//ms级延时

#endif
