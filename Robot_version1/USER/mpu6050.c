#include "mpu6050.h"
#include "time.h"
#include "math.h"

#define RAD2DEG 57.295779513082320876798154814105

int i2cAddress;
double accX, accY, gyroX, gyroY, gyroZ;
double gyroXOffset, gyroYOffset, gyroZOffset;
double xAngle, yAngle, zAngle;
int16_t temp;
unsigned long prevMillis;


void Mpu6050_Init(int Address)
{
	TimeSystickInit();
	I2C1_Init();
	i2cAddress = Address;
	gyroXOffset = 0;
	gyroYOffset = 0;
	gyroZOffset = 0;
	xAngle      = 0;
	yAngle      = 0;
	zAngle      = 0;
	accX        = 0;
	accY        = 0;	
	prevMillis = SystickMillis();
	I2C_ByteWrite(i2cAddress,0x6B ,0);
	I2C_ByteWrite(i2cAddress,0x19 ,0);
	I2C_ByteWrite(i2cAddress,0x1B ,0);
	I2C_ByteWrite(i2cAddress,0x1C ,0);	
}
void Mpu6050_Calibrate(int Times)
{
		long gyroXTotal = 0, gyroYTotal = 0, gyroZTotal = 0;
		int count = 0;
		short gyroRawX, gyroRawY, gyroRawZ;	
		for (int i = 0; i < Times; i++) {
			u8 buf[6],res;  
			res=I2C_BufferRead(i2cAddress,0x43, buf, 6);				
			gyroRawX = ((u16)buf[0]<<8)|buf[1];
			gyroRawY = ((u16)buf[2]<<8)|buf[3];  
			gyroRawZ = ((u16)buf[4]<<8)|buf[5];

			gyroXTotal += gyroRawX;
			gyroYTotal += gyroRawY;
			gyroZTotal += gyroRawZ;
			count += 1;
		}	
      gyroXOffset = -gyroXTotal * 1.0 / count;
      gyroYOffset = -gyroYTotal * 1.0 / count;
      gyroZOffset = -gyroZTotal * 1.0 / count;
}
void Mpu6050_ReadAngles()
{
		if (SystickMillis() - prevMillis < 3)
		return;
		int accRawX, accRawY, accRawZ, gyroRawX, gyroRawY, gyroRawZ;
		u8 Rec_Data[14],res;
		res=I2C_BufferRead(i2cAddress,0x3B,Rec_Data, 14);
    accRawX = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    accRawY = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    accRawZ = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
    temp = (int16_t)(Rec_Data[6] << 8 | Rec_Data[7]);
    gyroRawX = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
    gyroRawY = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
    gyroRawZ = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);
		accX = atan((accRawY / 16384.0) / sqrt(pow((accRawX / 16384.0), 2) + pow((accRawZ / 16384.0), 2))) * RAD2DEG;
		accY = atan(-1 * (accRawX / 16384.0) / sqrt(pow((accRawY / 16384.0), 2) + pow((accRawZ / 16384.0), 2))) * RAD2DEG;

		gyroX = (gyroRawX + gyroXOffset) / 131.0;
		gyroY = (gyroRawY + gyroYOffset) / 131.0;
		gyroZ = (gyroRawZ + gyroZOffset) / 131.0;

		unsigned long curMillis = SystickMillis();
		double duration = (curMillis - prevMillis) * 1e-3;
		prevMillis = curMillis;

		xAngle = 0.98 * (xAngle + gyroX * duration) + 0.02 * accX;
		yAngle = 0.98 * (yAngle + gyroY * duration) + 0.02 * accY;
		zAngle = zAngle + gyroZ * duration;			
}
double Mpu6050_GetYAngle()
{
	Mpu6050_ReadAngles();
	return yAngle;	
}
