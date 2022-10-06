/*
  ******************************************************************************
  * @file		motor.h                                                              *
  * @author	Luu Ngoc Anh                                                       *
  * @date		26/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __MOTOR__H
#define __MOTOR__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header
#define PERIOD 				100000
#define PRESCALER 		72
void MotorInit(void);
void MotorLeft(int16_t speed); //-100000 100000
void MotorRight(int16_t speed);//-100000 100000
void MotorStop();

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/