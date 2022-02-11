#include <Arduino.h>
#include <Ina219.h>

bool Ina219::init() {
    if (!begin()) {
        Log::printErrln("INA219", "Failed to initialize");
        return false;
    } else {
        Log::printSysln("INA219", "Success");
        return true;
    }
}

bool Ina219::update() {
    lastIna.m_busVoltage = curIna.m_busVoltage;
    lastIna.m_shuntVoltage = curIna.m_shuntVoltage;
    lastIna.m_loadVoltage = curIna.m_loadVoltage;
    lastIna.m_current = curIna.m_current;
    lastIna.m_power = curIna.m_power;
    
    curIna.m_busVoltage = getBusVoltage_V();
    curIna.m_shuntVoltage = getShuntVoltage_mV();
    curIna.m_loadVoltage = curIna.m_busVoltage + (curIna.m_shuntVoltage / 1000);
    curIna.m_current = getCurrent_mA();
    curIna.m_power = getPower_mW();

    return true;
}

float Ina219::getBusVoltage() {
    return curIna.m_busVoltage;
}

float Ina219::getShuntVoltage() {
    return curIna.m_shuntVoltage;
}

float Ina219::getLoadVoltage() {
    return curIna.m_loadVoltage;
}

float Ina219::getCurrent() {
    return curIna.m_current;
}

float Ina219::getPower() {
    return curIna.m_power;
}

void Ina219::checkVoltage() {
    if (curIna.m_loadVoltage <= LOW_BATTERY) {
        if (curIna.m_loadVoltage < CRITICAL_BATTERY) {
            Log::printWarln("INA219", "CRITICAL BATTERY");
        } else {
            Log::printWarln("INA219", "LOW BATTERY");
        }
    }
}

void Ina219::checkPower() {
    if (curIna.m_power >= HIGH_POWER) {
        if (curIna.m_power >= CRITICAL_POWER) {
            Log::printWarln("INA219", "CRITICAL POWER CONSUMPTION");
        } else {
            Log::printWarln("INA219", "HIGH POWER CONSUMPTION");
        }
    }
}

void Ina219::validate() {
    checkVoltage();
    checkPower();
}

void Ina219::printValues() {
    Serial.println("Bus Voltage: " + String(getBusVoltage()) + " V");
    Serial.println("Shunt Voltage: " + String(getShuntVoltage()) + " mV");
    Serial.println("Load Voltage: " + String(getLoadVoltage()) + " V");
    Serial.println("Current: " + String(getCurrent()) + " mA");
    Serial.println("Power: " + String(getPower()) + " mW");
}

void Ina219::mockData(float vtg_V, float crt_mA, float pwr_mW) {
    curIna.m_loadVoltage = vtg_V;
    curIna.m_current = crt_mA;
    curIna.m_power = pwr_mW;
}

bool Ina219::isCharging() {
    if (compareToLastReading()) {
        storeLastVoltages();
        if (checkIfVoltageIncreased()){
            return true;
        } else {
            return false;
        }    
    } else {
        return false;
    }
}   

bool Ina219::compareToLastReading() {
    if ((curIna.m_busVoltage - lastIna.m_busVoltage) >= CHARGING_VOLTAGE) {
        return true;
    } else {
        return false;
    }
}

void Ina219::storeLastVoltages() {
    lastVoltage[readCounter] = curIna.m_loadVoltage;
    readCounter++;
}

bool Ina219::checkIfVoltageIncreased() {
    if (getWasCharging()) {
        if (readCounter == MAX_INA_VALUES) {
            readCounter = 0;
        }

        if (curIna.m_loadVoltage >= CHARGING_VOLTAGE) {
            return true;
        } else {
            setWasCharging(false);
            return false;
        }
    }

    if (readCounter == MAX_INA_VALUES) {
        readCounter = 0;
        for (byte i = 1; i < MAX_INA_VALUES; i++) {
            float difference = lastVoltage[i] - lastVoltage[i-1];
            if (difference >= MINIMUM_INCREASED_VOLTAGE_FOR_CHARGING
                && compareToPreviousReadings(difference, i)
                && compareToNextReadings(difference, i)) {
                    return true;
                }
            } 
        }

    return false;
}

bool Ina219::compareToPreviousReadings(float diff, byte i) {
    byte count = 0;
    for (byte j = i; j > 0; j--) {
        if (lastVoltage[i] - lastVoltage[j-1] > MINIMUM_INCREASED_VOLTAGE_FOR_CHARGING) {
            count++;
        }
    }
    if (count >= 0) {
        return true;
    } else {
        return false;
    }
}

bool Ina219::compareToNextReadings(float diff, byte i) {
    byte count = 0;
    for (byte j = i + 1; j < MAX_INA_VALUES; j++) {
        if (lastVoltage[i] - lastVoltage[j+1] <= 0) {
            count++;
        }
    }
    if (count >= 0) {
        return true;
    } else {
        return false;
    }
}

void Ina219::setWasCharging(bool prevState) {
    wasCharging = prevState;
}

bool Ina219::getWasCharging() {
    return wasCharging;
}