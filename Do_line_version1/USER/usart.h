/*
  ******************************************************************************
  * @file		usart.h                                                              *
  * @author	    Nguyen Van An                                                *
  * @date		23/04/2022                                                      *
  ******************************************************************************
*/
	
#ifndef __USART__
#define __USART__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_usart.h"  
#include "stdio.h"

int USART_FlagDB(void);
int USART_Compare(char *vr_String);
void Delay_ms(unsigned int vr_Time);
void USART_SendChar(char vr_Char);
void USART_SendString(char *vr_Str);
void USART_SendNum(int vr_Num);
void USART_PutChar(void);
void USART_Config(unsigned int Baurates);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
