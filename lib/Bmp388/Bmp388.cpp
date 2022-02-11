#include <Arduino.h>
#include <Bmp388.h>

bool Bmp388::init() {
    if (!begin_I2C(BMP388_ADDR)) {
        Log::printErrln("BMP388", "Failed to initialize");
        return false;
    } else {
        Log::printSysln("BMP388", "Success");
        setSampling();
        return true;
    }
}

void Bmp388::setSampling() {
    setTemperatureOversampling(BMP388_TEMP_OVERSAMP);
    setPressureOversampling(BMP388_PRES_OVERSAMP);
    setIIRFilterCoeff(BMP388_FILTERING);
    setOutputDataRate(BMP388_DATARATE);
}

bool Bmp388::update() {
    if (!performReading()) {
        Log::printSysln("BMP388", "Failed to perform reading");
        return false;
    }

    bmp388.m_temperature = temperature;
    bmp388.m_pressure = pressure/100;
    bmp388.m_altitude = readAltitude(SEA_LEVEL_PRESSURE_HPA); 
    
    return true;
}

double Bmp388::getTemperature() {
    return bmp388.m_temperature;
}

double Bmp388::getPressure() {
    return bmp388.m_pressure;
}

double Bmp388::getAltitude() {
    return bmp388.m_altitude;
}

void Bmp388::printValues() {
    Serial.println("Temperature: " + String(getTemperature()) + " C");
    Serial.println("Pressure: " + String(getPressure()) + " hPa");
    Serial.println("Altitude: " + String(getAltitude()) + " m");
}

void Bmp388::mockData(float tmp, float prs, float alt) {
    bmp388.m_temperature = tmp;
    bmp388.m_pressure = prs;
    bmp388.m_altitude = alt;
}