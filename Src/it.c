#include "main.h"
#include "stm32f4xx_it.h"

volatile uint32_t contador_1 = 0, contador_2 = 0;

void TIM5_IRQHandler(void)
{
	if(TIM5->SR & (1<<0))
	{
		contador_1++;
		contador_2++;
	}

	TIM5->SR &= ~(1<<0);
}
