#include "stm32f10x.h"                  // Device header
#include "motor.h"


void delay(uint16_t Time)
{
	while(Time--)
	{
		for(uint16_t i = 0; i < 0x2aff; i++);
	}
}

int main()
{
	Motor_Init();
	while(1)
	{
		Speed_L(50);
		Speed_R(50);
		delay(1000);
		Speed_L(100);
		Speed_R(100);
		delay(1000);
		Speed_L(200);
		Speed_R(200);
		delay(1000);
		Speed_L(100);
		Speed_R(100);
		delay(1000);
	}
}
