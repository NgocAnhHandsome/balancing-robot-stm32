/*
  ******************************************************************************
  * @file		usart_lib.h                                                        *
  * @author	Luu Ngoc Anh                                                       *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __USART__
#define __USART__

#ifdef __cplusplus
 extern "C" {
#endif
void UsartLib_Init(unsigned int BaudRates); // khoi tao toc do truyen
void UsartLib_SendChar(char _varChar); 			// ham truyen mot ky tu
void UsartLib_SendString(char *_varString); // ham truyen mot chuoi
void UsartLib_SendNumber(int _varNumber); 	// Ham truyen mot so
int UsartLib_flag(void); 										// ham co check
void UsartLib_Putchar_RRX(void); 						// ham in chuoi nhan duoc
unsigned char UsartLib_CompareStr(char *S1); 					// ham so sanh chuoi
void delay(unsigned int time);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
