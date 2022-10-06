#ifndef _MPU6050_H_
#define _MPU6050_H_
#include <Arduino.h>
#include "Wire.h"

#define   RAD2DEG   57.295779

/*	SENSOR MPU6050
  	Author: Nguyen Nhat Minh
  	Date: 30/9/2022
  	Version: 1 
*/

class MPU6050 {
  public:
    MPU6050() {
    };

    void init(int address) {
      this->i2cAddress = address;

      this->gyroXOffset = 0;
      this->gyroYOffset = 0;
      this->gyroZOffset = 0;

      this->xAngle = 0;
      this->yAngle = 0;
      this->zAngle = 0;

      this->accX = 0;
      this->accY = 0;

      this->prevMillis = millis();

      Wire.begin();
      Wire.beginTransmission(this->i2cAddress);
      Wire.write(0x6B);
      Wire.write(0);   
      Wire.endTransmission(true);

      Wire.beginTransmission(this->i2cAddress);
    
      Wire.write(0x19); 
      Wire.write(0); 
      Wire.endTransmission(true);

      Wire.beginTransmission(this->i2cAddress);
      Wire.write(0x1B); 
      Wire.write(0); 

      Wire.beginTransmission(this->i2cAddress);
      Wire.write(0x1C); 
      Wire.write(0);
      Wire.endTransmission(true);
    }

    void calibrate(int times) {
      long gyroXTotal = 0, gyroYTotal = 0, gyroZTotal = 0;
      int count = 0;
      int gyroRawX, gyroRawY, gyroRawZ;
      for (int i = 0; i < times; i++) {
        Wire.beginTransmission(this->i2cAddress);
        Wire.write(0x43); 
        Wire.endTransmission(false);
        Wire.requestFrom(this->i2cAddress, 6, true);

        gyroRawX = Wire.read() << 8 | Wire.read();
        gyroRawY = Wire.read() << 8 | Wire.read();
        gyroRawZ = Wire.read() << 8 | Wire.read();

        gyroXTotal += gyroRawX;
        gyroYTotal += gyroRawY;
        gyroZTotal += gyroRawZ;
        count++;
      }
      gyroXOffset = -gyroXTotal * 1.0 / count;
      gyroYOffset = -gyroYTotal * 1.0 / count;
      gyroZOffset = -gyroZTotal * 1.0 / count;
    }

    double getXAngle() {
      this->readAngles();
      return this->xAngle;
    };
    
    double getYAngle() {
      this->readAngles();
      return this->yAngle;
    };

    double getZAngle() {
      this->readAngles();
      return this->zAngle;
    };

    double getXAcc() {
      this->readAngles();
      return this->accX;
    };

    double getYAcc() {
      this->readAngles();
      return this->accY;
    };

   void getXYZAngles(double &x, double &y, double &z) {
      this->readAngles();
      x = xAngle;
      y = yAngle;
      z = zAngle;
    }

  private:
    int i2cAddress;
    double accX, accY, gyroX, gyroY, gyroZ;
    double gyroXOffset, gyroYOffset, gyroZOffset;
    double xAngle, yAngle, zAngle;
    unsigned long prevMillis;

    void readAngles() {
      if (millis() - this->prevMillis < 3)
        return;

      int accRawX, accRawY, accRawZ, gyroRawX, gyroRawY, gyroRawZ;

      Wire.beginTransmission(this->i2cAddress);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(this->i2cAddress, 14, true);

      accRawX = Wire.read() << 8 | Wire.read();
      accRawY = Wire.read() << 8 | Wire.read();
      accRawZ = Wire.read() << 8 | Wire.read();
      Wire.read(); Wire.read();
      gyroRawX = Wire.read() << 8 | Wire.read();
      gyroRawY = Wire.read() << 8 | Wire.read();
      gyroRawZ = Wire.read() << 8 | Wire.read();

      accX = atan((accRawY / 16384.0) / sqrt(pow((accRawX / 16384.0), 2) + pow((accRawZ / 16384.0), 2))) * RAD2DEG;
      accY = atan(-1 * (accRawX / 16384.0) / sqrt(pow((accRawY / 16384.0), 2) + pow((accRawZ / 16384.0), 2))) * RAD2DEG;

      gyroX = (gyroRawX + gyroXOffset) / 131.0;
      gyroY = (gyroRawY + gyroYOffset) / 131.0;
      gyroZ = (gyroRawZ + gyroZOffset) / 131.0;

      unsigned long curMillis = millis();
      double duration = (curMillis - prevMillis) * 1e-3;
      prevMillis = curMillis;

      xAngle = 0.98 * (xAngle + gyroX * duration) + 0.02 * accX;
      yAngle = 0.98 * (yAngle + gyroY * duration) + 0.02 * accY;
      zAngle = zAngle + gyroZ * duration;
    }
};

void mpu6050Init(MPU6050 &mpu, int address) {
  mpu.init(address);
}

void mpu6050Calibrate(MPU6050 &mpu, int times) {
  mpu.calibrate(times);
}

double mpu6050GetXAngle(MPU6050 &mpu) {
  return mpu.getXAngle();
}

double mpu6050GetYAngle(MPU6050 &mpu) {
  return mpu.getYAngle();
}

double mpu6050GetZAngle(MPU6050 &mpu) {
  return mpu.getZAngle();
}

void mpu6050GetXYZAngles(MPU6050 &mpu, double &xAngle, double &yAngle, double &zAngle) {
  mpu.getXYZAngles(xAngle, yAngle, zAngle);
}

#endif  /*_MPU6050_H_*/
