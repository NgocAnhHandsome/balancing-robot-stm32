/*
  ******************************************************************************
  * @file		motor.h                                                            *
  * @author	Luu Ngoc Anh                                                       *
  * @date		30/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __MOTOR__H
#define __MOTOR__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header

#define Dir_R  GPIO_Pin_9 //PB9
#define Step_R GPIO_Pin_8 //PB8
#define Dir_L  GPIO_Pin_3 //PA3
#define Step_L GPIO_Pin_2 //PA2
#define ENA    GPIO_Pin_1 //PA1
#define PRESCALER	72
#define PERIOD	2000

void Motor_Init(void);
void Speed_L(int Speed);
void Speed_R(int Speed);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
