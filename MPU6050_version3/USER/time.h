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
#include "stdint.h"
void TimeSystickInit(void);
uint32_t SystickMillis(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/