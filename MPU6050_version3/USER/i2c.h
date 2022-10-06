/*
  ******************************************************************************
  * @file		i2c.h                                                              *
  * @author	Luu Ngoc Anh                                                       *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __I2C__H
#define __I2C__H

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header

#define             XX_I2Cx                                		 I2C1
#define             EEPROM_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             EEPROM_I2C_CLK                             RCC_APB1Periph_I2C1
#define             EEPROM_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             EEPROM_I2C_GPIO_CLK                        RCC_APB2Periph_GPIOB     
#define             EEPROM_I2C_SCL_PORT                        GPIOB   
#define             EEPROM_I2C_SCL_PIN                         GPIO_Pin_6
#define             EEPROM_I2C_SDA_PORT                        GPIOB 
#define             EEPROM_I2C_SDA_PIN                         GPIO_Pin_7
#define I2C_Speed              100000
#define I2Cx_OWN_ADDRESS7      0X0A
#define I2C_PageSize           8
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define IDP_IIC_DEBUG_ON         0
#define IDP_IIC_INFO(fmt,arg...)           printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define IDP_IIC__ERROR(fmt,arg...)          printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define IDP_IIC__DEBUG(fmt,arg...)          do{\
                                          if(IDP_IIC_DEBUG_ON)\
                                          printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)
/////////////////////////////////////////////////////////////////////////////////
																					
static void I2C_GPIO_Config(void);																					
static void I2C_Mode_Configu(void);
void IDP_IIC_Init(void);																		
uint32_t I2C_MPU_ByteWrite(u8 WriteAddr,u8 pBuffer);
uint32_t I2C_MPU_BufferRead(u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);
uint32_t I2C_MPU_PageWrite(u8 pBuffer, u8 WriteAddr);
uint32_t I2C_BufferRead(u8* pBuffer,u8 EquipAddr,u8 ReadAddr, u16 NumByteToRead);
uint32_t I2C_ByteWrite(u8 WriteAddr,u8 EquipAddr,u8 pBuffer);
																					
//////////////////////////////////////////////////////////////////////////////////									
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/