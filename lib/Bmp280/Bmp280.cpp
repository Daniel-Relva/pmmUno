#include <Arduino.h>
#include <Bmp280.h>

bool Bmp280::init() {
    if (!begin(BMP280_ADDR)) {
        Log::printErrln("BMP388", "Failed to initialize");
        return false;
    } else {
        Log::printSysln("BMP388", "Success");
        Bmp280::setSampling();
        return true;
    }
}

void Bmp280::setSampling() {
    Adafruit_BMP280::setSampling(BMP280_OPMODE,     /* Operating Mode. */
                BMP280_TEMP_OVERSAMP,               /* Temp. oversampling */
                BMP280_PRES_OVERSAMP,               /* Pressure oversampling */
                BMP280_FILTERING,                   /* Filtering. */
                BMP280_STANDBY);                    /* Standby time. */
}

bool Bmp280::update() {
    bmp280.m_temperature = readTemperature();
    bmp280.m_pressure = readPressure();
    bmp280.m_altitude = readAltitude();
}

double Bmp280::getTemperature() {
    return bmp280.m_temperature;
}

double Bmp280::getPressure() {
    return bmp280.m_pressure;
}

double Bmp280::getAltitude() {
    return bmp280.m_altitude;
}

void Bmp280::printValues() {
    Serial.println("Temperature: " + String(getTemperature()) + " C");
    Serial.println("Pressure: " + String(getPressure()) + " hPa");
    Serial.println("Altitude: " + String(getAltitude()) + " m");
}

void Bmp280::mockData(float tmp, float prs, float alt) {
    bmp280.m_temperature = tmp;
    bmp280.m_pressure = prs;
    bmp280.m_altitude = alt;
}

void Bmp280::reset() {
    Adafruit_BMP280::reset();
}