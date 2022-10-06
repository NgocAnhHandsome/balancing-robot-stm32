/*
  ******************************************************************************
  * @file		i2c.h                                                              *
  * @author	Luu Ngoc Anh                                                       *
  * @date		29/09/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __I2C__H
#define __I2C__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  
#include "usart_lib.h"

#define I2C_Speed              						400000 
#define I2Cx_OWN_ADDRESS7      						0X0A   
#define I2C_PageSize          						8
#define I2CT_FLAG_TIMEOUT         				((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         				((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define IDP_IIC_DEBUG_ON         					0

#define IDP_IIC_INFO(fmt,arg...)          printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define IDP_IIC__ERROR(fmt,arg...)        printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define IDP_IIC__DEBUG(fmt,arg...)         do{\
																					if(IDP_IIC_DEBUG_ON)\
																					printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
																					}while(0)


void 			I2C1_Init(void);
uint32_t  I2C_ByteWrite(u8 EquipAddr,u8 WriteAddr,u8 pBuffer);
uint32_t  I2C_BufferRead(u8 EquipAddr, u8 ReadAddr, u8* pBuffer, u16 NumByteToRead);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
																					