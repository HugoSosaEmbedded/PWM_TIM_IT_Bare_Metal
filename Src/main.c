#include "main.h"

extern volatile uint32_t contador_1, contador_2;

int main()
{
	uint32_t duty_cycle = 0, duty_cycle_1 = 0, direccion = 1, direccion_1 = 1;
	uint32_t time_1 = 50, time_2 = 200;

	GPIO_TIM2_PWM_Init();
	TIM2_PWM_Init();
	TIM5_Init();

	TIM2->EGR |= (1<<0) ; // Initializing all register
	TIM2->CR1 |= (1<<0);// Enable CNT TIM2
	TIM5->CR1 |= (1<<0);

	while(1)
	{
		TIM2->CCR1 = ((TIM2->ARR ) * duty_cycle) / 100;
		TIM2->CCR2 = ((TIM2->ARR ) * duty_cycle_1) / 100;

		if(contador_1 >= time_1)
		{
			duty_cycle += 10 * direccion;
			contador_1 = 0;
		}

		if(contador_2 >= time_2)
		{
			duty_cycle_1 += 100 * direccion_1;
			contador_2 = 0;
		}

		if(duty_cycle >= 100) { duty_cycle = 100; direccion = -1; }
		else if(duty_cycle <= 0) { duty_cycle = 0; direccion = 1; }

		if(duty_cycle_1 >= 100) { duty_cycle_1 = 100; direccion_1 = -1; }
		else if(duty_cycle_1 <= 0) { duty_cycle_1 = 0; direccion_1 = 1; }


	}

	return 0;

}
