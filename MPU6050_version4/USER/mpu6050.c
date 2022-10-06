#include "mpu6050.h"
#include <stm32f10x.h>
#include "idp_iic.h"
#include <stdio.h>

/* MPU��ַ�����ڲ��Ĵ�����ַ */
#define MPU_6050_ADDR 0xD0 //MPU6050��IIC��ַ
#define MPU_PWRMGMT1_REG 0x6B //(��Դ����Ĵ���1)��ַ
#define MPU_GYR_REG 0x1B //���������üĴ���
#define MPU_AC_REG 0x1c //���ٶ������üĴ���
#define MPU_FIFO_REG 0x23 //FIFOʹ�ܼĴ���
#define MPU_SAMPLERATE_REG 0x19 //�����ǲ�����Ƶ�Ĵ���
#define MPU_CONFIG_REG 0x1A //���üĴ���
#define MPU_PWRMGM2_REG 0x6C //��Դ����Ĵ���2
#define MPU_ACCOUT_REG 0x3B //���ٶȴ���������Ĵ�����ʼ��ַ ��6*8bit ʮ��λ���� ��[x-z]h,[x-z]����
#define MPU_SAMPLEOUT_REG 0x43 //��������������Ĵ��� ��6*8bit ʮ��λ���� ��[x-z]h,[x-z]����
#define MPU_TMEOUT_REG 0x41 //�¶ȴ�������������Ĵ�����16λ���ݣ� temp = 36.53+regvl/340
#define MPU_INT_REG 0X38 //�ж�ʹ�ܼĴ���
#define MPU_USERCTL_REG 0x6A //�û����ƼĴ���
#define MPU_INTPBCFG_REG 0x37 //�ж�������Ч��ƽ���üĴ���
#define MPU_WHOAMI_REG 0x75 //WHO AM I�Ĵ���
#define MPU_IDNUMBER 0x68 //MPU6050��ʶ��

void delayms(int i)
{
	unsigned char a,b;
	for(;i>0;i--)
	        for(b=4;b>0;b--)
	            for(a=113;a>0;a--);	
}

/**
  * @brief  ��ʼ��I2C�ϵ�mpu6050
  * @param   
  *		@arg  
  *		@arg  
  * @retval  ��
  */
uint8_t MPU_Init(void)
{ 
	uint8_t res[3]={0}; uint32_t timeout = I2CT_LONG_TIMEOUT;
	IDP_IIC_Init();//IIC_Init();//��ʼ��IIC����
	I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x80);	//��λMPU6050
 
	delayms(1000);
	I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x00);	//����MPU6050 
	I2C_ByteWrite(MPU_GYR_REG,MPU_6050_ADDR,0x00);//MPU_Set_Gyro_Fsr(3);	//�����Ǵ�����,��2000dps
	I2C_ByteWrite(MPU_CONFIG_REG,MPU_6050_ADDR,0x02);//���õ�ͨ�˲���
	I2C_ByteWrite(MPU_AC_REG,MPU_6050_ADDR,0x00);//MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	I2C_ByteWrite(MPU_SAMPLERATE_REG,MPU_6050_ADDR,0x07);//MPU_Set_Rate(50);						//���ò�����50Hz
	I2C_ByteWrite(MPU_INT_REG,MPU_6050_ADDR,0x00);	//�ر������ж�
	I2C_ByteWrite(MPU_USERCTL_REG,MPU_6050_ADDR,0x00);	//I2C��ģʽ�ر�
	I2C_ByteWrite(MPU_FIFO_REG,MPU_6050_ADDR,0x00);	//�ر�FIFO
	I2C_ByteWrite(MPU_INTPBCFG_REG,MPU_6050_ADDR,0x80);	//INT���ŵ͵�ƽ��Ч
	I2C_BufferRead(res,MPU_6050_ADDR,MPU_WHOAMI_REG,1);
	
	
	if(res[0]==MPU_IDNUMBER)//����ID��ȷ	
	{	//printf("MPU6050���ǵ�ѽ��%d",res[0]);
		I2C_BufferRead(res,MPU_6050_ADDR,MPU_PWRMGMT1_REG,1);
		printf("#%d#",res[0]);
		I2C_BufferRead(res,MPU_6050_ADDR,MPU_GYR_REG,1);
		printf("#%d#",res[0]);
		I2C_BufferRead(res,MPU_6050_ADDR,MPU_SAMPLEOUT_REG,1);
		printf("#%d#",res[0]);
		I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x01);	//����CLKSEL,PLL X��Ϊ�ο�
		I2C_ByteWrite(MPU_PWRMGM2_REG,MPU_6050_ADDR,0x00);	//���ٶ��������Ƕ�����
		I2C_ByteWrite(MPU_SAMPLERATE_REG,MPU_6050_ADDR,19);//MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	return 0;
}

/**
  * @brief  ��mpu��ȡ�¶�ֵ
  * @param   
  *		@arg 
  *		@arg  
  * @retval  �¶�*100
  */
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw=0;
		float temp=0;
		I2C_BufferRead(buf,MPU_6050_ADDR,MPU_TMEOUT_REG,2);
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}

/**
  * @brief  ��mpu��ȡ������ֵ
  * @param   
  *		@arg gx,x��
  *		@arg gy,y��
	*   @arg gz,z��
  * @retval  1��success��else�� false
  */
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
  u8 buf[6],res;  
	res=I2C_BufferRead(buf,MPU_6050_ADDR,MPU_SAMPLEOUT_REG,6);
	//if(res)
	//{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	printf("gx��%d",*gx);
	//} 	
  return res;;
}


/**
  * @brief  ��mpu��ȡ���ٶȼ�ֵ
  * @param   
  *		@arg gx,x��
  *		@arg gy,y��
	*   @arg gz,z��
  * @retval  1��success��else�� false
  */
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
  u8 buf[6],res;  
	res=I2C_BufferRead(buf,MPU_6050_ADDR,MPU_ACCOUT_REG,6);
	//if(res)
	//{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	//printf("ax��%lf\n",(*ax)/16384.0);
	//} 	
    return res;;
}

