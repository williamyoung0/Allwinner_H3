#ifndef __RGB_WS2812B_H_
#define __RGB_WS2812B_H_

#include "sys.h"

void RGB_WS2812B_GPIO_Config(void);
void Set_RGB_Colour(uint8_t red, uint8_t green, uint8_t blue);
void RGB_DMA_Transmission(void);
void RGB_TIM3OC3_PWM(void);
void TIM3_PWM_Init(void);
void RGB_WS2812B_Init(void);

#endif
