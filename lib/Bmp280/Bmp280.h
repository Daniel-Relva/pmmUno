#ifndef Bmp280_h
#define Bmp280_h
#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <BarometerInterface.h>
#include <Wire.h>
#include <Log.h>

class Bmp280: public BarometerInterface, Adafruit_BMP280 {
private:
    struct data {
        double m_temperature;
        double m_pressure;
        double m_altitude;
    };
    data bmp280;
    void setSampling();
public:
    unsigned long previousTime = 0;
    bool init();
    bool update();
    double getTemperature();
    double getPressure();
    double getAltitude();
    void printValues();
    void mockData(float tmp, float prs, float alt);
    void reset();
};

#endif