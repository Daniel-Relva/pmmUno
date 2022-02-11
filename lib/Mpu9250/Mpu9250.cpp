#include <Arduino.h>
#include <Mpu9250.h>

Mpu9250::Mpu9250() : MPU9250(Wire, MPU9250_ADDR) {
}

bool Mpu9250::init() {
    if (!begin()) {
        Log::printErrln("MPU9250", "Failed to initialize");
        return false;
    } else {
        Log::printSysln("MPU9250", "Success");
        return true;
    }
}

bool Mpu9250::update() {
    if (!readSensor()) {
        Log::printSysln("MPU9250", "Failed to perform reading");
        return false;
    }
    
    mpu9250.m_temperature = getTemperature_C();
    
    mpu9250.accel.m_accelX = getAccelX_mss();
    mpu9250.accel.m_accelY = getAccelY_mss();
    mpu9250.accel.m_accelZ = getAccelZ_mss();
    
    mpu9250.gyro.m_gyroX = getGyroX_rads();
    mpu9250.gyro.m_gyroY = getGyroY_rads();
    mpu9250.gyro.m_gyroZ = getGyroZ_rads();
    
    mpu9250.mag.m_magX = getMagX_uT();
    mpu9250.mag.m_magY = getMagY_uT();
    mpu9250.mag.m_magZ = getMagZ_uT();
    
    return true;
}

double Mpu9250::getTemperature() {
    return mpu9250.m_temperature;
}

Mpu9250::Accel Mpu9250::getAccel() {
    return mpu9250.accel;
}

Mpu9250::Gyro Mpu9250::getGyro() {
    return mpu9250.gyro;
}

Mpu9250::Mag Mpu9250::getMag() {
    return mpu9250.mag;
}

Mpu9250::data Mpu9250::getData() {
    return mpu9250;
}

void Mpu9250::printValues() {

    Serial.println("AccelX: " + String(getAccel().m_accelX) + " m/s^2");
    Serial.println("AccelY: " + String(getAccel().m_accelY) + " m/s^2");
    Serial.println("AccelZ: " + String(getAccel().m_accelZ) + " m/s^2");

    Serial.println("GyroX: " + String(getGyro().m_gyroX) + " rad");
    Serial.println("GyroY: " + String(getGyro().m_gyroX) + " rad");
    Serial.println("GyroZ: " + String(getGyro().m_gyroX) + " rad");

    Serial.println("MagX: " + String(getMag().m_magX) + " uT");
    Serial.println("MagY: " + String(getMag().m_magY) + " uT");
    Serial.println("MagZ: " + String(getMag().m_magZ) + " uT");

    Serial.println("Temperature: " + String(getData().m_temperature) + " C");
    
}

void Mpu9250::mockData(
    float accelX,
    float accelY,
    float accelZ,
    float gyroX,
    float gyroY,
    float gyroZ,
    float magX,
    float magY,
    float magZ,
    float temp
) {
    mpu9250.accel.m_accelX = accelX;
    mpu9250.accel.m_accelY = accelY;
    mpu9250.accel.m_accelZ = accelZ;

    mpu9250.gyro.m_gyroX = gyroX;
    mpu9250.gyro.m_gyroY = gyroY;
    mpu9250.gyro.m_gyroZ = gyroZ;

    mpu9250.mag.m_magX = magX;
    mpu9250.mag.m_magY = magY;
    mpu9250.mag.m_magZ = magZ;

    mpu9250.m_temperature = temp;
}