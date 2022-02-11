#ifndef Mpu9250_h
#define Mpu9250_h
#include <Arduino.h>
#include <MPU9250.h>
#include <SensorInterface.h>
#include <Wire.h>
#include <Log.h>

class Mpu9250: public SensorInterface, MPU9250 {
private:
    struct Accel {
        double m_accelX;
        double m_accelY;
        double m_accelZ;
    };
    struct Gyro {
        double m_gyroX;
        double m_gyroY;
        double m_gyroZ;
    };
    struct Mag {
        double m_magX;
        double m_magY;
        double m_magZ;
    };
    struct data {
        Accel accel;
        Gyro  gyro;
        Mag   mag;
        double m_temperature;
    };
    data mpu9250;

public:
    unsigned long previousTime = 0;
    Mpu9250();
    bool init();
    bool update();

    void printValues();
    void mockData(
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
    );
    
    double getTemperature();
    Accel getAccel();
    Gyro getGyro();
    Mag getMag();
    data getData();
};

#endif