#include "idp_iic.h"
#include "usart_lib.h"

uint16_t EEPROM_ADDRESS;
static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;   
static uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode);
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
	EEPROM_I2C_APBxClock_FUN ( EEPROM_I2C_CLK, ENABLE );
	EEPROM_I2C_GPIO_APBxClock_FUN ( EEPROM_I2C_GPIO_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	  
  GPIO_Init(EEPROM_I2C_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	    
  GPIO_Init(EEPROM_I2C_SDA_PORT, &GPIO_InitStructure);	
	
	
}


static void I2C_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  I2C_Init(XX_I2Cx, &I2C_InitStructure);
  I2C_Cmd(XX_I2Cx, ENABLE);   
}

void IDP_IIC_Init(void)
{

  I2C_GPIO_Config(); 
 
  I2C_Mode_Configu();
}

void I2C_EE_WaitEepromStandbyState(void)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    I2C_GenerateSTART(XX_I2Cx, ENABLE);
    SR1_Tmp = I2C_ReadRegister(XX_I2Cx, I2C_Register_SR1);
    I2C_Send7bitAddress(XX_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(XX_I2Cx, I2C_Register_SR1) & 0x0002));
  I2C_ClearFlag(XX_I2Cx, I2C_FLAG_AF);
    I2C_GenerateSTOP(XX_I2Cx, ENABLE); 
}


static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
  IDP_IIC__ERROR("I2C !errorCode = %d",errorCode);
  return 0;
}

uint32_t I2C_ByteWrite(u8 WriteAddr,u8 EquipAddr,u8 pBuffer) 
{
  I2C_GenerateSTART(XX_I2Cx, ENABLE);
  I2CTimeout = I2CT_FLAG_TIMEOUT;  
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))  
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
  } 
  I2C_Send7bitAddress(XX_I2Cx, EquipAddr, I2C_Direction_Transmitter);

	I2CTimeout = I2CT_FLAG_TIMEOUT;
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
  }  
  I2C_SendData(XX_I2Cx, WriteAddr);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
  } 
  I2C_SendData(XX_I2Cx, pBuffer);  
  I2CTimeout = I2CT_FLAG_TIMEOUT;  
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
  } 
  I2C_GenerateSTOP(XX_I2Cx, ENABLE);
  
  return 1;
}

uint32_t I2C_BufferRead(u8* pBuffer,u8 EquipAddr,u8 ReadAddr, u16 NumByteToRead)
{  
  
  I2CTimeout = I2CT_LONG_TIMEOUT;
  
  //*((u8 *)0x4001080c) |=0x80; 
  while(I2C_GetFlagStatus(XX_I2Cx, I2C_FLAG_BUSY))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
  }
  
  /* Send START condition */
  I2C_GenerateSTART(XX_I2Cx, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
  }
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(XX_I2Cx, EquipAddr, I2C_Direction_Transmitter);

  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
  }
    
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(XX_I2Cx, ENABLE);

  /* Send the EEPROM's internal address to write to */
  I2C_SendData(XX_I2Cx, ReadAddr);  

   
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(12);
   }
    
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(XX_I2Cx, ENABLE);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(13);
   }
    
  /* Send Equipment address for read */
  I2C_Send7bitAddress(XX_I2Cx, EquipAddr, I2C_Direction_Receiver);
  
  I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(14);
   }
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(XX_I2Cx, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(XX_I2Cx, ENABLE);
    }

    /* Test on EV7 and clear it */    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    
		while(I2C_CheckEvent(XX_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)  
		{
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
		} 
    {      
      /* Read a byte from the EEPROM */
      *pBuffer = I2C_ReceiveData(XX_I2Cx);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(XX_I2Cx, ENABLE);
  
  return 1;
}










