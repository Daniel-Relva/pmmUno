#ifndef BarometerInterface_h
#define BarometerInterface_h
#include <SensorInterface.h>

class BarometerInterface: private SensorInterface {
private:
public:
    virtual void setSampling() = 0;
    virtual double getTemperature() = 0;
    virtual double getPressure() = 0;
    virtual double getAltitude() = 0;
};

#endif