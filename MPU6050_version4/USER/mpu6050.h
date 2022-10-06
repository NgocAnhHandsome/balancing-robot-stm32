#ifndef _MPU_6050
#define _MPU_6050
#include <stm32f10x.h>

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


uint8_t MPU_Init(void);
short MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);



#endif



