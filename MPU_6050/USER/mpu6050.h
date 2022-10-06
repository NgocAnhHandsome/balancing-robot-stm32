/*
  ******************************************************************************
  * @file		mpu6050.h                                                          *
  * @author	Luu Ngoc Anh                                                       *
  * @date		27/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __MPU6050__H
#define __MPU6050__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header
#include <stdint.h>
#include "i2c.h"
#define MPU_6050_ADDR 0x68 << 1
#define MPU_PWRMGMT1_REG 0x6B 
#define MPU_GYR_REG 0x1B 
#define MPU_AC_REG 0x1c 
#define MPU_FIFO_REG 0x23
#define MPU_SAMPLERATE_REG 0x19 
#define MPU_CONFIG_REG 0x1A 
#define MPU_PWRMGM2_REG 0x6C 
#define MPU_ACCOUT_REG 0x3B 
#define MPU_SAMPLEOUT_REG 0x43
#define MPU_TMEOUT_REG 0x41
#define MPU_INT_REG 0X38 
#define MPU_USERCTL_REG 0x6A 
#define MPU_INTPBCFG_REG 0x37
#define MPU_WHOAMI_REG 0x75
#define MPU_IDNUMBER 0x68

// MPU6050 structure
typedef struct
{

    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;
    double Ax;
    double Ay;
    double Az;

    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;
    double Gx;
    double Gy;
    double Gz;

    float Temperature;

    double KalmanAngleX;
    double KalmanAngleY;
} MPU6050_t;

// Kalman structure
typedef struct
{
    double Q_angle;
    double Q_bias;
    double R_measure;
    double angle;
    double bias;
    double P[2][2];
} Kalman_t;

uint8_t MPU6050_Init();

void MPU6050_Read_Accel(MPU6050_t *DataStruct);

void MPU6050_Read_Gyro(MPU6050_t *DataStruct);

void MPU6050_Read_Temp(MPU6050_t *DataStruct);

void MPU6050_Read_All(MPU6050_t *DataStruct);

double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);
void delayms(int i);
double getYAngle(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/