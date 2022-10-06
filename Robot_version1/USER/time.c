#include "time.h"

volatile uint32_t Count = 0;

void TimeSystickInit(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);	
}

void SysTick_Handler(void) 
{
		Count ++;
}

uint32_t SystickMillis(void)
{
	return Count;
}
