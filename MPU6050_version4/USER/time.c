#include "time.h"
#include "stm32f10x.h"                  // Device header

volatile uint32_t Count = 0;

void TimeSystickInit(void)
{
	SystemInit();
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// configure a tick to be 1 us
	SysTick_Config(SystemCoreClock / 1000);	
}

void SysTick_Handler(void) // Function SysTick_Handler will be called every 1 us
{
		Count ++;
}

uint32_t SystickMillis(void)
{
	return Count;
}

