#include "main.h"

void TIM5_Init(void)
{
	RCC->APB1ENR |= (1<<3); //Enable TIM5 clock
	TIM5->PSC = 15;
	TIM5->ARR = 1000 - 1;
	TIM5->CR1 &= ~(1<<1);

	NVIC_EnableIRQ(TIM5_IRQn);
	NVIC_SetPriority(TIM5_IRQn, 0);
	TIM5->DIER |= (1<<0); // Enable interrupt
}

