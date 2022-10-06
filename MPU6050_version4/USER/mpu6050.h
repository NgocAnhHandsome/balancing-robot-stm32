#ifndef _MPU_6050
#define _MPU_6050
#include <stm32f10x.h>

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


uint8_t MPU_Init(void);
short MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);



#endif



