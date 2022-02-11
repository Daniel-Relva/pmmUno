#ifndef Manager_h
#define Manager_h
#include <Arduino.h>
#include <Bmp388.h>
#include <Ina219.h>
#include <Mpu9250.h>
#include <Led.h>
#include <AdafruitSd.h>
#include <Constants.h>
#include <string.h>

class Manager {
private:
    static int addressesFound[sizeof(I2C_ADDRESSES)/sizeof(int)];
    bool initI2c();
    bool checkI2cBus();
    void identifyI2cError();
    static unsigned long currentTime;
protected:
    float status;
    Led led;
    Bmp388 bmp388;
    Ina219 ina219;
    Mpu9250 mpu9250;
public:
    void startStateMachine();
    static int getState();
    static void setState(StateMachine st);
    void startSerial();
    bool init();
    void sensorsTest();
    void detectI2c();
    void startCountingTime();
    static unsigned long getCurrentTime();
    void readSensors();
    void handleIna219();
    void handleBmp388();
    void handleMpu9250();
};

#endif