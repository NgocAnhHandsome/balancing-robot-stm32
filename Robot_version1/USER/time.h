/*
  ******************************************************************************
  * @file		time.h                                                             *
  * @author	Luu Ngoc Anh                                                       *
  * @date		28/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __TIME__H
#define __TIME__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stdint.h"
void TimeSystickInit(void);
uint32_t SystickMillis(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
