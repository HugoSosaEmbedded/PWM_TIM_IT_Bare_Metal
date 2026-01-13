#include "main.h"

void GPIO_TIM2_PWM_Init(void)
{
	RCC->AHB1ENR |= (1<<0); // Enable GPIOA clock
	GPIOA->MODER &= ~((3<<0) | (3<<2));
	GPIOA->MODER |= ((2<<0) | (2<<2)); // PA0 and PA1 as ALtarnate Function
	GPIOA->AFR[0] &= ~((0xF<<0) | (0xF<<4));
	GPIOA->AFR[0] |= ((1<<0) | (1<<4)); // Set up AF1 to TIM2_CH1

}

void TIM2_PWM_Init(void)
{

	RCC->APB1ENR |= (1<<0); // TIM2 clock enabled
	TIM2->PSC = 15;
	TIM2->ARR = 1000 - 1;

	TIM2->CCMR1 &= ~(7<<4);
	TIM2->CCMR1 |= (6<<4);  // The PWM mode can be selected by writing 110 PWM mode 1 or 111 PWM mode
	TIM2->CCMR1 |= (1<<3); // Enable the corresponding preload register

	TIM2->CCMR1 &= ~(7<<12);
	TIM2->CCMR1 |= (6<<12); // PWM mode 1 - In upcounting, channel 2 is active as long as TIM2_CNT < TIM2_CCR!
	TIM2->CCMR1 |= (1<<11); // Preload register on TIM2_CCR2 enabled

	TIM2->CCER &= ~(1<<1); // OC1 polarity CH1
	TIM2->CCER |= (1<<0) ; // OC1 output enable CH1

	TIM2->CCER &= ~(1<<5); // OC2 polarity active high CH2
	TIM2->CCER |= (1<<4); // OC2 signal is output on CH2

	TIM2->CR1 |= (1<<7); // auto-reload preload register enable

	//TIM2->CCR1 = ((TIM2->ARR + 1) * 50) / 100;

}

