/*
  ******************************************************************************
  * @file		motor.h                                                              *
  * @author	Luu Ngoc Anh                                                       *
  * @date		24/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __MOTOR__H
#define __MOTOR__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"     

# define  Enable       GPIO_Pin_0     	// PA0               
# define  Step_L       GPIO_Pin_1       // PA1                 
# define  Step_R       GPIO_Pin_2       // PA2                                    
# define  Dir_L        GPIO_Pin_3       // PA3               
# define  Dir_R        GPIO_Pin_4       // PA4 
# define  PERIOD 			 1440
# define  PRESCALER 	 1


void MotorInit(void);
void Speed_L(int x);
void Speed_R(int x);
uint32_t SystickMillis();
																																			
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
