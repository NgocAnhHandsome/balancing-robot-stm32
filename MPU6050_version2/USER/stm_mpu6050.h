//#ifndef _SAIGONTECH_MPU6050_H_
//#define _SAIGONTECH_MPU6050_H_

//#include "i2c.h"
//#include "time.h"
//#include "usart_lib.h"
//#include "math.h"

//#define   RAD2DEG   57.295779
//#define MPU_6050_ADDR 0xD0 
//#define MPU_PWRMGMT1_REG 0x6B 
//#define MPU_GYR_REG 0x1B
//#define MPU_AC_REG 0x1c 
//#define MPU_FIFO_REG 0x23 
//#define MPU_SAMPLERATE_REG 0x19 
//#define MPU_CONFIG_REG 0x1A 
//#define MPU_PWRMGM2_REG 0x6C 
//#define MPU_ACCOUT_REG 0x3B 
//#define MPU_SAMPLEOUT_REG 0x43 
//#define MPU_TMEOUT_REG 0x41
//#define MPU_INT_REG 0X38 
//#define MPU_USERCTL_REG 0x6A 
//#define MPU_INTPBCFG_REG 0x37 
//#define MPU_WHOAMI_REG 0x75 
//#define MPU_IDNUMBER 0x68 

//class SMPU6050 {
//  public:
//    SMPU6050() {
//    };

//    void init() {
//      this->gyroXOffset = 0;
//      this->gyroYOffset = 0;
//      this->gyroZOffset = 0;

//      this->xAngle = 0;
//      this->yAngle = 0;
//      this->zAngle = 0;


//      this->accX = 0;
//      this->accY = 0;

//      this->prevMillis = SystickMillis();

//     
//			uint8_t res[3]={0}; uint32_t timeout = I2CT_LONG_TIMEOUT;
//			IDP_IIC_Init();
//			I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x80);
//			delay(1000);
//			I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x00);
//			I2C_ByteWrite(MPU_GYR_REG,MPU_6050_ADDR,0x00);
//			I2C_ByteWrite(MPU_CONFIG_REG,MPU_6050_ADDR,0x02);
//			I2C_ByteWrite(MPU_AC_REG,MPU_6050_ADDR,0x00);
//			I2C_ByteWrite(MPU_SAMPLERATE_REG,MPU_6050_ADDR,0x07);
//			I2C_ByteWrite(MPU_INT_REG,MPU_6050_ADDR,0x00);
//			I2C_ByteWrite(MPU_USERCTL_REG,MPU_6050_ADDR,0x00);
//			I2C_ByteWrite(MPU_FIFO_REG,MPU_6050_ADDR,0x00);
//			I2C_ByteWrite(MPU_INTPBCFG_REG,MPU_6050_ADDR,0x80);
//			I2C_BufferRead(res,MPU_6050_ADDR,MPU_WHOAMI_REG,1);
//			if(res[0]==MPU_IDNUMBER)//??ID??	
//			{	//printf("MPU6050?:%d",res[0]);
//				I2C_BufferRead(res,MPU_6050_ADDR,MPU_PWRMGMT1_REG,1); //MPU_PWRMGMT1_REG = 0x6B
//				I2C_BufferRead(res,MPU_6050_ADDR,MPU_GYR_REG,1); //MPU_GYR_REG = 0x1B
//				I2C_BufferRead(res,MPU_6050_ADDR,MPU_SAMPLEOUT_REG,1); // MPU_SAMPLEOUT_REG 0x43
//				I2C_ByteWrite(MPU_PWRMGMT1_REG,MPU_6050_ADDR,0x01);	//??CLKSEL,PLL X???? MPU_PWRMGMT1_REG = 0x6B
//				I2C_ByteWrite(MPU_PWRMGM2_REG,MPU_6050_ADDR,0x00);	//?????????? //MPU_PWRMGM2_REG 0x6C
//				I2C_ByteWrite(MPU_SAMPLERATE_REG,MPU_6050_ADDR,19);//MPU_Set_Rate(50);		MPU_SAMPLERATE_REG 0x19	//??????50Hz
//			}
//    }
//    void calibrate(int times) {
//      long gyroXTotal = 0, gyroYTotal = 0, gyroZTotal = 0;
//      int count = 0;
//      int gyroRawX, gyroRawY, gyroRawZ;
//      for (int i = 0; i < times; i++) {
////        Wire.beginTransmission(this->i2cAddress);
////        Wire.write(0x43); //3thanh ghi 16 bit từ (0x43-0x48) GYRO_XOUT  GYRO_YOUT  GYRO_ZOUT Những thanh ghi này lưu trữ các phép đo con quay gần đây nhất
////        Wire.endTransmission(false);
////        Wire.requestFrom(this->i2cAddress, 6, true);

////        gyroRawX = Wire.read() << 8 | Wire.read();
////        gyroRawY = Wire.read() << 8 | Wire.read();
////        gyroRawZ = Wire.read() << 8 | Wire.read();
//					u8 buf[6],res;  
//					res=I2C_BufferRead(buf,MPU_6050_ADDR,MPU_SAMPLEOUT_REG,6); //MPU_SAMPLEOUT_REG 0x43				
//					gyroRawX = 	((u16)buf[0]<<8)|buf[1];
//					gyroRawY = 	((u16)buf[2]<<8)|buf[3]; 
//					gyroRawZ = 	((u16)buf[4]<<8)|buf[5];
//					gyroXTotal += gyroRawX;
//					gyroYTotal += gyroRawY;
//					gyroZTotal += gyroRawZ;
//        count += 1;
//      }
//      gyroXOffset = -gyroXTotal * 1.0 / count;
//      gyroYOffset = -gyroYTotal * 1.0 / count;
//      gyroZOffset = -gyroZTotal * 1.0 / count;
//    }

//    double getXAngle() {
//      this->readAngles();
//      return this->xAngle;
//    };

//    double getYAngle() {
//      this->readAngles();
//      return this->yAngle;
//    };

//    double getZAngle() {
//      this->readAngles();
//      return this->zAngle;
//    };





//    double getXAcc() {
//      this->readAngles();
//      return this->accX;
//    };

//    double getYAcc() {
//      this->readAngles();
//      return this->accY;
//    };










//    void getXYZAngles(double &x, double &y, double &z) {
//      this->readAngles();
//      x = xAngle;
//      y = yAngle;
//      z = zAngle;
//    }

//  private:
//    int i2cAddress;
//    double accX, accY, gyroX, gyroY, gyroZ;
//    double gyroXOffset, gyroYOffset, gyroZOffset;
//    double xAngle, yAngle, zAngle;
//    unsigned long prevMillis;

//    void readAngles() {
//      if (SystickMillis() - this->prevMillis < 3)
//        return;

//      int accRawX, accRawY, accRawZ, gyroRawX, gyroRawY, gyroRawZ;


////      Wire.beginTransmission(this->i2cAddress);
////      Wire.write(0x3B);
////      Wire.endTransmission(false);
////      Wire.requestFrom(this->i2cAddress, 14, true);

//			u8 Rec_Data[14],res;  
//			int16_t temp;
//			res=I2C_BufferRead(Rec_Data,MPU_6050_ADDR,MPU_ACCOUT_REG,14);
////      accRawX = Wire.read() << 8 | Wire.read();
////      accRawY = Wire.read() << 8 | Wire.read();
////      accRawZ = Wire.read() << 8 | Wire.read();
////      Wire.read(); Wire.read();
////      gyroRawX = Wire.read() << 8 | Wire.read();
////      gyroRawY = Wire.read() << 8 | Wire.read();
////      gyroRawZ = Wire.read() << 8 | Wire.read();
//				accRawX = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
//				accRawY = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
//				accRawZ = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
//				temp = (int16_t)(Rec_Data[6] << 8 | Rec_Data[7]);
//				gyroRawX = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
//				gyroRawY = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
//				accRawZ = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);

//      accX = atan((accRawY / 16384.0) / sqrt(pow((accRawX / 16384.0), 2) + pow((accRawZ / 16384.0), 2))) * RAD2DEG;
//      accY = atan(-1 * (accRawX / 16384.0) / sqrt(pow((accRawY / 16384.0), 2) + pow((accRawZ / 16384.0), 2))) * RAD2DEG;

//      gyroX = (gyroRawX + gyroXOffset) / 131.0;
//      gyroY = (gyroRawY + gyroYOffset) / 131.0;
//      gyroZ = (gyroRawZ + gyroZOffset) / 131.0;

//      unsigned long curMillis = SystickMillis();
//      double duration = (curMillis - prevMillis) * 1e-3;
//      prevMillis = curMillis;

//      xAngle = 0.98 * (xAngle + gyroX * duration) + 0.02 * accX;
//      yAngle = 0.98 * (yAngle + gyroY * duration) + 0.02 * accY;
//      zAngle = zAngle + gyroZ * duration;
//    }
//};



//void mpu6050Calibrate(SMPU6050 &smpu, int times) {
//  smpu.calibrate(times);
//}

//double mpu6050GetXAngle(SMPU6050 &smpu) {
//  return smpu.getXAngle();
//}

//double mpu6050GetYAngle(SMPU6050 &smpu) {
//  return smpu.getYAngle();
//}

//double mpu6050GetZAngle(SMPU6050 &smpu) {
//  return smpu.getZAngle();
//}

//void mpu6050GetXYZAngles(SMPU6050 &smpu, double &xAngle, double &yAngle, double &zAngle) {
//  smpu.getXYZAngles(xAngle, yAngle, zAngle);
//}

//#endif  /*_SAIGONTECH_MPU6050_H_*/