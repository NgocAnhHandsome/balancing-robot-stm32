#include "mpu6050.h"
#include <stm32f10x.h>
#include "idp_iic.h"
#include <stdio.h>

/* MPU地址和其内部寄存器地址 */
#define MPU_6050_ADDR 0xD0 //MPU6050的IIC地址
#define MPU_PWRMGMT1_REG 0x6B //(电源管理寄存器1)地址
#define MPU_GYR_REG 0x1B //陀螺仪配置寄存器
#define MPU_AC_REG 0x1c //加速度仪配置寄存器
#define MPU_FIFO_REG 0x23 //FIFO使能寄存器
#define MPU_SAMPLERATE_REG 0x19 //陀螺仪采样分频寄存器
#define MPU_CONFIG_REG 0x1A //配置寄存器
#define MPU_PWRMGM2_REG 0x6C //电源管理寄存器2
#define MPU_ACCOUT_REG 0x3B //加速度传感器输出寄存器起始地址 （6*8bit 十六位数据 （[x-z]h,[x-z]））
#define MPU_SAMPLEOUT_REG 0x43 //陀螺仪数据输出寄存器 （6*8bit 十六位数据 （[x-z]h,[x-z]））
#define MPU_TMEOUT_REG 0x41 //温度传感器数据输出寄存器（16位数据） temp = 36.53+regvl/340
#define MPU_INT_REG 0X38 //中断使能寄存器
#define MPU_USERCTL_REG 0x6A //用户控制寄存器
#define MPU_INTPBCFG_REG 0x37 //中断引脚有效电平配置寄存器
#define MPU_WHOAMI_REG 0x75 //WHO AM I寄存器
#define MPU_IDNUMBER 0x68 //MPU6050标识码

void delayms(int i)
{
	unsigned char a,b;
	for(;i>0;i--)
	        for(b=4;b>0;b--)
	            for(a=113;a>0;a--);	
}

/**
  * @brief  初始化I2C上的mpu6050
  * @param   
  *		@arg  
  *		@arg  
  * @retval  无
  */
uint8_t MPU_Init(void)
{ 
	uint8_t res[3]={0}; uint32_t timeout = I2CT_LONG_TIMEOUT;
	IDP_IIC_Init();//IIC_Init();//初始化IIC总线
	I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x80);	//复位MPU6050
 
	delayms(1000);
	I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x00);	//唤醒MPU6050 
	I2C_ByteWrite(MPU_GYR_REG,MPU_6050_ADDR,0x00);//MPU_Set_Gyro_Fsr(3);	//陀螺仪传感器,±2000dps
	I2C_ByteWrite(MPU_CONFIG_REG,MPU_6050_ADDR,0x02);//配置低通滤波器
	I2C_ByteWrite(MPU_AC_REG,MPU_6050_ADDR,0x00);//MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
	I2C_ByteWrite(MPU_SAMPLERATE_REG,MPU_6050_ADDR,0x07);//MPU_Set_Rate(50);						//设置采样率50Hz
	I2C_ByteWrite(MPU_INT_REG,MPU_6050_ADDR,0x00);	//关闭所有中断
	I2C_ByteWrite(MPU_USERCTL_REG,MPU_6050_ADDR,0x00);	//I2C主模式关闭
	I2C_ByteWrite(MPU_FIFO_REG,MPU_6050_ADDR,0x00);	//关闭FIFO
	I2C_ByteWrite(MPU_INTPBCFG_REG,MPU_6050_ADDR,0x80);	//INT引脚低电平有效
	I2C_BufferRead(res,MPU_6050_ADDR,MPU_WHOAMI_REG,1);
	
	
	if(res[0]==MPU_IDNUMBER)//器件ID正确	
	{	//printf("MPU6050？是的呀：%d",res[0]);
		I2C_BufferRead(res,MPU_6050_ADDR,MPU_PWRMGMT1_REG,1);
		printf("#%d#",res[0]);
		I2C_BufferRead(res,MPU_6050_ADDR,MPU_GYR_REG,1);
		printf("#%d#",res[0]);
		I2C_BufferRead(res,MPU_6050_ADDR,MPU_SAMPLEOUT_REG,1);
		printf("#%d#",res[0]);
		I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x01);	//设置CLKSEL,PLL X轴为参考
		I2C_ByteWrite(MPU_PWRMGM2_REG,MPU_6050_ADDR,0x00);	//加速度与陀螺仪都工作
		I2C_ByteWrite(MPU_SAMPLERATE_REG,MPU_6050_ADDR,19);//MPU_Set_Rate(50);						//设置采样率为50Hz
 	}else return 1;
	return 0;
}

/**
  * @brief  从mpu获取温度值
  * @param   
  *		@arg 
  *		@arg  
  * @retval  温度*100
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
  * @brief  从mpu获取陀螺仪值
  * @param   
  *		@arg gx,x轴
  *		@arg gy,y轴
	*   @arg gz,z轴
  * @retval  1：success；else： false
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
	printf("gx：%d",*gx);
	//} 	
  return res;;
}


/**
  * @brief  从mpu获取加速度计值
  * @param   
  *		@arg gx,x轴
  *		@arg gy,y轴
	*   @arg gz,z轴
  * @retval  1：success；else： false
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
	//printf("ax：%lf\n",(*ax)/16384.0);
	//} 	
    return res;;
}

