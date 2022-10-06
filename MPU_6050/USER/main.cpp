#include "stm_mpu6050.h"
#include "usart_lib.h"

SMPU6050 mpu6050;

int main()
{
	UsartLib_Init(9600);
	mpu6050.init(0x68);
	UsartLib_SendString("Ngoc Anh\n");
	while(1)
	{
//	float AngleY = mpu6050.getYAngle();
//	UsartLib_SendFloat(AngleY);
//	UsartLib_SendString("\n");
	}
}