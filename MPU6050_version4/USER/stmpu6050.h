
/*
  ******************************************************************************
  * @file		stmpu6050.h                                                        *
  * @author	Luu Ngoc Anh                                                       *
  * @date		29/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __ABC__
#define __ABC__

#ifdef __cplusplus
 extern "C" {
#endif
#include "idp_iic.h"

void MPU_init(int address);
void calibrate(int times);
void readAngles();
double getYAngle();

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
