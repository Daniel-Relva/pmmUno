#ifndef Bmp388_h
#define Bmp388_h
#include <Arduino.h>
#include <Adafruit_BMP3XX.h>
#include <BarometerInterface.h>
#include <Wire.h>
#include <Log.h>

class Bmp388: public BarometerInterface, Adafruit_BMP3XX {
private:
    struct data {
        double m_temperature;
        double m_pressure;
        double m_altitude;
    };
    data bmp388;
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
};

#endif