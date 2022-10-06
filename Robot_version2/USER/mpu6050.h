/*
  ******************************************************************************
  * @file		mpu6050.h                                                          *
  * @author	Luu Ngoc Anh                                                       *
  * @date		29/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __MPU6050__H
#define __MPU6050__H

#ifdef __cplusplus
 extern "C" {
#endif

#include "i2c.h"
void Mpu6050_Init(int Address);
void Mpu6050_Calibrate(int Times);
void Mpu6050_ReadAngles();
double Mpu6050_GetYAngle();

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

