#include "stm32f10x.h"                  // Device header
#include "mpu6050.h"
#include "usart_lib.h"
#include "stdio.h"
#include "time.h"

MPU6050_t mpu;

int main()
{
	TimeSystickInit();
	UsartLib_Init(9600);
	MPU6050_Init();
	printf("CONNECTED\n");
	printf("%d\n", SystickMillis());
	while(1)
	{
		MPU6050_Read_All(&mpu);
		printf("gy: %lf\n", mpu.Temperature);
		delay(10);
	}
}