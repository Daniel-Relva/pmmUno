#ifndef Ina219_h
#define Ina219_h
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SensorInterface.h>
#include <Log.h>

class Ina219: private SensorInterface, Adafruit_INA219 {
private:
    struct data {
        float m_busVoltage;
        float m_shuntVoltage;
        float m_loadVoltage;
        float m_current;
        float m_power;
    };
    data curIna;
    data lastIna;
    
    // float smallerVoltage;
    float lastVoltage[MAX_INA_VALUES];
    byte readCounter = 0;
    bool wasCharging = false;
    
    bool compareToLastReading();
    void storeLastVoltages();
    bool checkIfVoltageIncreased();
    void setTemporaryLastVoltage();
    bool compareToPreviousReadings(float diff, byte index);
    bool compareToNextReadings(float diff, byte index);
    void setWasCharging(bool prevState);
    bool getWasCharging();
public:
    unsigned long previousTime = 0;
    bool init();
    bool update();
    float getBusVoltage();
    float getShuntVoltage();
    float getLoadVoltage();
    float getCurrent();
    float getPower();
    void checkVoltage();
    void checkPower();
    void validate();
    void printValues();
    void mockData(float vtg_mV, float crt_mA, float pwr_mW);
    bool isCharging();
};

#endif