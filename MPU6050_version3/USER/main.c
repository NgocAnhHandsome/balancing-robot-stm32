#include "stm32f10x.h"                  // Device header
#include "usart_lib.h"
#include "mpu6050.h"

MPU6050_t mpu;
int main()
{
	UsartLib_Init(9600);
	MPU6050_Init();
	printf("CONNECTED MPU6050\n");
	while(1)
	{
		MPU6050_Read_All(&mpu);
		printf("%lf\n", mpu.Gx);
		delay(100);
	}
}

