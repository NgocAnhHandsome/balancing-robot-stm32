/*
  ******************************************************************************
  * @file		button.h                                                              *
  * @author 	Nguyen Van An                                               *
  * @date		23/04/2022                                                      *
  ******************************************************************************
*/
	
#ifndef __GPIO_SEG7__
#define __GPIO_SEG7__

#ifdef __cplusplus
 extern "C" {
#endif

#define BUTTON_1 GPIO_Pin_13
#define BUTTON_2 GPIO_Pin_14
#define BUTTON_3 GPIO_Pin_15

void Button_Control(void);
void delay(unsigned int time);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

