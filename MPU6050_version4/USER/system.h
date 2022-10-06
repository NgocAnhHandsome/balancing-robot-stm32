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
#include "idp_iic.h"
#include "usart_lib.h"
#include "time.h"
#include "motor.h"
#include "stmpu6050.h"
#include "math.h"
#include "stdio.h"

void System_Init(void);
void System_Run(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/