#ifndef __DELAY_H
#define __DELAY_H
#include "sys.h"

void Delay_init(u8 SYSCLK);	//��ʼ���δ�ʱ��ʱ��
void Delay_us(u32 nus);			//us����ʱ
void Delay_xms(u16 nms);
void Delay_ms(u16 nms);			//ms����ʱ

#endif
