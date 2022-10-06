/*
  ******************************************************************************
  * @file		system.h                                                           *
  * @author	Luu Ngoc Anh                                                       *
  * @date		29/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __SYSTEM__H
#define __SYSTEM__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header
#include "i2c.h"
#include "motor.h"
#include "mpu6050.h"
#include "usart_lib.h"
#include "time.h"
#include "stdio.h"
#include "math.h"

void SysInit(void);
void SysRun(void);


#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
